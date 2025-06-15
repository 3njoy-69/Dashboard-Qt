#ifndef AUTOPARKINGDIALOG_H
#define AUTOPARKINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class AutoParkingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoParkingDialog(QWidget *parent = nullptr);
    QString getSelectedZone() const;

public slots:
    void onConfirmClicked();  // <-- Khai báo ở đây

private:
    QLabel *imageLabel;
    QComboBox *comboBox;
};

#endif // AUTOPARKINGDIALOG_H
