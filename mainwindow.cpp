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
{
    ui->setupUi(this);
    refreshPorts();
    
    ui->lineStatus->setText("Порт закрыт");
    ui->lineStatus->setStyleSheet("color: red;");



    connect(ui->connectToPort, &QPushButton::clicked, this, &MainWindow::togglePort);
    connect(ui->DownloadBin, &QAction::triggered, this, &MainWindow::on_actionOpenBinaryFile_triggered);
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

   

}