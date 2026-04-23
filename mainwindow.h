#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStatusBar>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort* serial;
    bool isPortOpen;
    QByteArray m_loadedFileData;
    QString m_currentFileName;

    QByteArray m_sendBuffer;       
    qint64 m_bytesSent;            
    qint64 m_totalBytes;          
    bool m_isSending;  

private slots:
    void refreshPorts();
    void togglePort();
    void on_actionOpenBinaryFile_triggered();
    void buttonLoad();
    void startSendingFile();
    void buttonStart();
    void buttonEnd();
    void sendChunk();
    void onBytesWritten(qint64);
};
#endif // MAINWINDOW_H
