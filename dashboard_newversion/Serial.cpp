#include "mainwindow.h"
#include <QDebug>

UDPReceiver::UDPReceiver(QObject *parent) : QObject(parent) {
    // Cổng UDP 12345: Dùng để nhận dữ liệu chung
    m_udpSocket = new QUdpSocket(this);
    quint16 port = 12345;

    if (!m_udpSocket->bind(QHostAddress::Any, port)) {
        qWarning() << "Không thể mở cổng UDP 12345!";
    } else {
        connect(m_udpSocket, &QUdpSocket::readyRead, this, &UDPReceiver::readData);
        qDebug() << "Đang lắng nghe UDP trên cổng" << port;
    }

    // Cổng UDP 12346: Dùng để nhận tín hiệu
    m_udpSocket2 = new QUdpSocket(this);
    quint16 port2 = 12346;
    if (!m_udpSocket2->bind(QHostAddress::Any, port2)) {
        qWarning() << "Không thể mở cổng UDP 12346!";
    } else {
        connect(m_udpSocket2, &QUdpSocket::readyRead, this, &UDPReceiver::readSignalData);
        qDebug() << "Đang lắng nghe UDP trên cổng" << port2;
    }
}

void UDPReceiver::readData() {
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);// m_udpSocket là cổng 12345
            m_receivedData += buffer; // Tích lũy dữ liệu nhận được
            if (m_receivedData.endsWith('\n')) {
                m_dataQueue.enqueue(m_receivedData.trimmed()); // Đưa vào hàng đợi
                emit dataReceived(); // Phát tín hiệu khi có dữ liệu mới
                m_receivedData.clear(); // Xóa dữ liệu cũ
            }
    }
}
QString UDPReceiver::getReceivedData() {
    if (!m_dataQueue.isEmpty()) {
        return m_dataQueue.dequeue(); // Lấy và xóa dữ liệu đầu tiên trong hàng đợi
    }
    return QString(); // Trả về chuỗi rỗng nếu hàng đợi trống
}

void UDPReceiver::readSignalData() {
    while (m_udpSocket2->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(m_udpSocket2->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket2->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

        QString message = QString::fromUtf8(buffer).trimmed();

        emit signalReceived(message);  // Gửi nội dung chuỗi nhận được
    }
}

void MainWindow::sendUdpMessage(const QString &message) {
    QHostAddress receiverAddress = QHostAddress("127.0.0.1");  // Địa chỉ của Python
    quint16 receiverPort = 12347;  // Cổng Python đang lắng nghe

    QByteArray data = message.toUtf8();
    udpSender->writeDatagram(data, receiverAddress, receiverPort);
    qDebug() << "Đã gửi UDP:" << message;
}


