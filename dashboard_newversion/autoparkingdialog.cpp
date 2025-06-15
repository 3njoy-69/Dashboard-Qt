#include "autoparkingdialog.h"
#include "qpushbutton.h"
#include <QPixmap>

AutoParkingDialog::AutoParkingDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Automatic Parking Options");

    imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(":/map.png").scaled(800, 500, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);

    comboBox = new QComboBox(this);
    comboBox->addItems({"Zone 1", "Zone 2", "Zone 3"});
    comboBox->setFixedWidth(100);  // Gọn lại

    QPushButton *confirmButton = new QPushButton("Confirm");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    layout->addWidget(comboBox, 0, Qt::AlignHCenter);
    layout->addWidget(confirmButton, 0, Qt::AlignHCenter);

    setLayout(layout);
    resize(400, 350);

    // Kết nối
    connect(confirmButton, &QPushButton::clicked, this, &AutoParkingDialog::onConfirmClicked);
}

QString AutoParkingDialog::getSelectedZone() const {
    return comboBox->currentText();
}

void AutoParkingDialog::onConfirmClicked() {
    accept();  // Chỉ đóng dialog, không gửi ở đây
}
