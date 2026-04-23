#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QLabel>
#include <QButtonGroup> 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serial(new QSerialPort)
    , isPortOpen(false)
    , m_isSending(false)
{
    ui->setupUi(this);
    refreshPorts();
    
    ui->lineStatus->setText("Порт закрыт");
    ui->lineStatus->setStyleSheet("color: red;");

    ui->buttonLoad->setEnabled(true);
    ui->buttonStart->setEnabled(false);
    ui->buttonEnd->setEnabled(false);
    ui->lineIndicate->setText("IDLE");
    ui->progressBar->setVisible(false);
    ui->labelProgressBytes->setVisible(false);

    ui->lineEdit->setReadOnly(true);
    connect(ui->connectToPort, &QPushButton::clicked, this, &MainWindow::togglePort);
    connect(ui->DownloadBin, &QAction::triggered, this, &MainWindow::on_actionOpenBinaryFile_triggered);
    connect(ui->buttonStart, &QPushButton::clicked, this, &MainWindow::buttonStart);
    connect(ui->buttonLoad, &QPushButton::clicked, this, &MainWindow::buttonLoad);
    connect(ui->buttonEnd, &QPushButton::clicked, this, &MainWindow::buttonEnd);
    connect(serial, &QSerialPort::bytesWritten, this, &MainWindow::onBytesWritten);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPorts(){
    ui->comboBox->clear();
    QList<QSerialPortInfo> serialPort = QSerialPortInfo::availablePorts();
    if(serialPort.isEmpty()) ui->comboBox->addItem("Нет доступных портов");
    else{
        for(const QSerialPortInfo &port: serialPort){
            ui->comboBox->addItem(port.portName());
        }
    }
}

void MainWindow::togglePort(){

      if(!isPortOpen){
        if(ui->comboBox->currentText() == "Нет доступных портов"){
            QMessageBox::warning(this, "Ошибка", "Нет доступных портов");
            return;
        }
        serial->setPortName(ui->comboBox->currentText());
        serial->setBaudRate(921600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setStopBits(QSerialPort::StopBits::OneStop);
        serial->setParity(QSerialPort::NoParity);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if(serial -> open(QIODevice::ReadWrite)){
            isPortOpen = true;
            ui->connectToPort->setText("Закрыть порт");
            ui->comboBox->setEnabled(false);
            ui->lineStatus->setText("Порт открыт");
            ui->lineStatus->setStyleSheet("color: green;");
            ui->buttonStart->setEnabled(true);
            ui->buttonEnd->setEnabled(true);
        }
        else {
            QMessageBox::critical(this, "Ошибка", 
                "Не удалось открыть порт:\n" + serial->errorString());
        }
    }
    else{
        serial->close();
        isPortOpen = false;
        ui->connectToPort->setText("Открыть порт");
        ui->comboBox->setEnabled(true);
        ui->lineStatus->setText("Порт закрыт");
        ui->lineStatus->setStyleSheet("color: red;");
        ui->buttonStart->setEnabled(false);
        ui->buttonEnd->setEnabled(false);
    }


}


void MainWindow::on_actionOpenBinaryFile_triggered(){
     QString fileName = QFileDialog::getOpenFileName(
        this,
        "Выберите бинарный файл",
        QDir::homePath(),
        "Binary Files (*.bin);;All Files (*.*)"
    );

    if (fileName.isEmpty()) {
        statusBar()->showMessage("Загрузка отменена", 2000);
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Ошибка", 
            "Не удалось открыть файл:\n" + file.errorString());
        statusBar()->showMessage("Ошибка загрузки файла", 3000);
        return;
    }

    m_loadedFileData = file.readAll();
    file.close();

    if (m_loadedFileData.isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Файл пуст!");
        m_currentFileName = "Файл не выбран";
        statusBar()->showMessage("Файл пуст", 3000);
        return;
    }

    QFileInfo fileInfo(fileName);
    m_currentFileName = fileInfo.fileName();
    
    QString logMsg = QString("[OK] Загружен файл: %1, размер: %2 байт")
        .arg(m_currentFileName)
        .arg(m_loadedFileData.size());

    ui->textLogs->append(logMsg);
}

void MainWindow::buttonLoad(){


    if(m_isSending){
        ui->textLogs->append("[WARNING] Файл уже отправляется");
        return;
    }
    else{
        if(m_loadedFileData.isEmpty() ){
            ui->textLogs->append("[ERROR] Файл пуст или не загружен");
            return;
        }
        if(!isPortOpen){
            ui->textLogs->append("[ERROR], Требуется открытый COM-порт");
            return;
        }
    }

    QString logMsg= QString("[OK] Загрузка файла в устройство: %1, размер: %2 байт")
        .arg(m_currentFileName)
        .arg(m_loadedFileData.size());

    ui->textLogs->append(logMsg);

    startSendingFile();
}
void MainWindow::startSendingFile(){

    m_sendBuffer = m_loadedFileData;
    m_totalBytes = m_loadedFileData.size();
    m_bytesSent = 0;
    m_isSending = true;

    ui->progressBar->setVisible(true);
    ui->labelProgressBytes->setVisible(true);
    ui->progressBar->setRange(0, m_totalBytes);
    ui->progressBar->setValue(0);

    ui->buttonLoad->setEnabled(false);
    ui->buttonStart->setEnabled(false);
    ui->buttonEnd->setEnabled(false);

    ui->lineIndicate->setText("TX");
    ui->textLogs->append(QString("[INFO] Загрузка файла на устройство: %1 байт") .arg(m_totalBytes));

    sendChunk();



}

void MainWindow::sendChunk(){

    if(!m_isSending || m_sendBuffer.isEmpty()){
        m_isSending = false;
        ui->lineIndicate->setText("IDLE");
        ui->textLogs->append(QString("[OK] Отправка завершена: %1 байт")
            .arg(m_bytesSent));
        QTimer::singleShot(1000, this, [this]() {
            ui->progressBar->setVisible(false);
            ui->labelProgressBytes->setVisible(false);
        });

        ui->buttonLoad->setEnabled(true);
        ui->buttonStart->setEnabled(true);
        ui->buttonEnd->setEnabled(true);

        return;
    }

    const int CHUNK_SIZE = 256;
    QByteArray chunk = m_sendBuffer.left(CHUNK_SIZE);
    m_sendBuffer.remove(0, chunk.size());
    
    qint64 written = serial->write(chunk);
    
    if (written == -1) {
        ui->textLogs->append("[ERROR] Ошибка записи в порт");
        return;
    }


}

void MainWindow::onBytesWritten(qint64 bytes){


    if (!m_isSending) return;


    m_bytesSent += bytes;

    ui->progressBar->setValue(m_bytesSent);
    ui->labelProgressBytes->setText(QString("%1 / %2 байт")
        .arg(m_bytesSent)
        .arg(m_totalBytes));


    QTimer::singleShot(5, this, &MainWindow::sendChunk);

}


void MainWindow::buttonStart(){
    ui->lineIndicate->setText("TX");
    serial->write("start\n");
    ui->textLogs->append("[OK] Отправка команды: start");
    ui->lineIndicate->setText("IDLE");
}

void MainWindow::buttonEnd(){
    ui->lineIndicate->setText("TX");
    serial->write("end\n");
    ui->textLogs->append("[OK] Отправка команды: end");
    ui->lineIndicate->setText("IDLE");
}