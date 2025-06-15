    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QQueue>
#include <QString>
#include <QUdpSocket>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class UDPReceiver : public QObject {
    Q_OBJECT

public:
    explicit UDPReceiver(QObject *parent = nullptr);
    Q_INVOKABLE QString getReceivedData();

signals:
    void dataReceived();
    void signalReceived(const QString &data); // Phát tín hiệu khi có dữ liệu


private slots:
    void readData();
    void readSignalData();   // Slot để đọc tín hiệu từ cổng 12346


private:
    QUdpSocket *m_udpSocket;
    QUdpSocket *m_udpSocket2;
    QByteArray m_receivedData;
    QQueue<QString> m_dataQueue;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSignalReceived(const QString &data); // Slot để xử lý tín hiệu từ cổng 12346 và hiển thị MessageBox
    void sendUdpMessage(const QString &message);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    UDPReceiver *m_udpReceiver;
    UDPReceiver *udpReceiver;
    QUdpSocket *udpSender;  // Socket để gửi UDP

};
#endif // MAINWINDOW_H
