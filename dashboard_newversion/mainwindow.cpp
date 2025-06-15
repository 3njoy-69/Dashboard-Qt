#include "mainwindow.h"
#include "qqmlcontext.h"
#include "qqmlengine.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QQuickWidget>
#include "autoparkingdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSender = new QUdpSocket(this);

    udpReceiver = new UDPReceiver(this);

    connect(udpReceiver, &UDPReceiver::signalReceived, this, &MainWindow::onSignalReceived);

    // Nhúng QML vào UI
    QQuickWidget *qmlWidget = new QQuickWidget(this);
    // Truyền SerialReader vào QML
    qmlWidget->engine()->rootContext()->setContextProperty("udpReceiver", udpReceiver);

    qmlWidget->setSource(QUrl("qrc:/main.qml"));
    qmlWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);


    // Đưa vào layout của QWidget trong file .ui
    if (!ui->quickWidget->layout()) {
        ui->quickWidget->setLayout(new QVBoxLayout());
    }
    ui->quickWidget->layout()->addWidget(qmlWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug() << "udpReceiver pointer:" << udpReceiver;

}

void MainWindow::onSignalReceived(const QString &data)
{
    QString trimmedData = data.trimmed();

    if (trimmedData == "Done") {
        QMessageBox::information(this, "Success", "Parking complete!");
        qDebug() << "Received 'done' signal - parking completed.";
    } else {
        qDebug() << "Received signal:" << trimmedData << "but ignored.";
    }
}



void MainWindow::on_pushButton_clicked()
{
    qDebug() << "User wants to use automatic parking mode";

    AutoParkingDialog *dialog = new AutoParkingDialog(this);
    if (dialog->exec() == QDialog::Accepted)
    {
        QString selectedZone = dialog->getSelectedZone();

        QString zoneString;
        if (selectedZone == "Zone 1") zoneString = "1";
        else if (selectedZone == "Zone 2") zoneString = "2";
        else if (selectedZone == "Zone 3") zoneString = "3";

        sendUdpMessage(zoneString);
        qDebug() << "Sent zone string:" << zoneString;
    }
}

