
#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QSerialPort>
#include <QQueue>

class SerialReader : public QObject {
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);

    Q_INVOKABLE QString getReceivedData() ; // Thêm phương thức getter cho dữ liệu nhận

signals:
    void dataReceived(); // Phát tín hiệu khi nhận dữ liệu

private slots:
    void readData();

private:
    QSerialPort m_serial;
    QQueue<QString> m_dataQueue;
    QString m_receivedData; // Biến để lưu dữ liệu nhận
    bool check = false;
};

#endif // WINDOW_H
