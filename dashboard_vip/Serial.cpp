#include "window.h"
#include <QDebug>

SerialReader::SerialReader(QObject *parent) : QObject(parent) {
    m_serial.setPortName("COM1");
    m_serial.setBaudRate(QSerialPort::Baud9600);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial.open(QIODevice::ReadOnly)) {
        connect(&m_serial, &QSerialPort::readyRead, this, &SerialReader::readData);
    } else {
        qWarning() << "Không mở được cổng Serial!";
    }
}

void SerialReader::readData() {
    if(m_serial.isOpen()) {
        while(m_serial.bytesAvailable()) {
            m_receivedData += m_serial.readAll(); // Tích lũy dữ liệu vào m_receivedData

            // Kiểm tra nếu ký tự cuối cùng là '\n'
            if(m_receivedData.endsWith('\n')) {
                check = true;
            }
        }

        // Nếu nhận được chuỗi hoàn chỉnh (có dấu xuống dòng)
        if(check) {
            m_dataQueue.enqueue(m_receivedData.trimmed()); // Thêm dữ liệu vào hàng đợi
            emit dataReceived(); // Phát tín hiệu khi nhận được dữ liệu hoàn chỉnh
            m_receivedData.clear(); // Xóa dữ liệu cũ sau khi phát tín hiệu
            check = false;          // Đặt lại check để chờ dữ liệu mới
        }
    }
}

QString SerialReader::getReceivedData() {
    if (!m_dataQueue.isEmpty()) {
        return m_dataQueue.dequeue(); // Lấy và xóa dữ liệu đầu tiên trong hàng đợi
    }
    return QString(); // Trả về chuỗi rỗng nếu hàng đợi trống
}

