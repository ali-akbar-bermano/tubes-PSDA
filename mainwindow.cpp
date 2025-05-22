#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "thirdwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sembunyikan karakter password saat diketik
    ui->lePasswordAdmin->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLoginAdmin_clicked()
{
    QString nama = ui->leNamaAdmin->text();
    QString password = ui->lePasswordAdmin->text();

    const QString namaBenar = "admin";
    const QString passwordBenar = "admin";

    if (nama == namaBenar && password == passwordBenar) {
        // Login berhasil, buka window admin
        SecondWindow *adminWindow = new SecondWindow(); // tanpa `this` sebagai parent
        adminWindow->setAttribute(Qt::WA_DeleteOnClose); // biar auto delete saat ditutup
        adminWindow->show();
        this->hide(); // sembunyikan MainWindow, bukan close

    }else {
        QMessageBox::warning(this, "Login Gagal", "Nama atau password salah!");
    }
}

void MainWindow::on_btnLoginUser_clicked()
{
    thirdwindow *adminWindow = new thirdwindow(); // tanpa `this` sebagai parent
    adminWindow->setAttribute(Qt::WA_DeleteOnClose); // biar auto delete saat ditutup
    adminWindow->show();
    this->hide();
}
