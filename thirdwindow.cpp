#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "secondwindow.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <algorithm>

thirdwindow::thirdwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::thirdwindow)
{
    ui->setupUi(this);

    // Setup combo box untuk pilihan sort
    ui->cbSort->addItems(QStringList() << "Nama" << "Kategori" << "Jumlah");

    // Setup tabel
    ui->tableInventaris->setColumnCount(3);
    ui->tableInventaris->setHorizontalHeaderLabels(QStringList() << "Nama Barang" << "Kategori" << "Jumlah");
    ui->tableInventaris->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableInventaris->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInventaris->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableInventaris->setAlternatingRowColors(true);
    ui->tableInventaris->setShowGrid(false);

    // Tampilkan data awal
    loadData();

    // Hubungkan tombol Urut ke fungsinya
    connect(ui->btnUrut, &QPushButton::clicked, this, &thirdwindow::on_btnUrut_clicked);
}

thirdwindow::~thirdwindow()
{
    delete ui;
}

void thirdwindow::loadData()
{
    ui->tableInventaris->setRowCount(SecondWindow::jumlahData);

    for (int i = 0; i < SecondWindow::jumlahData; ++i) {
        ui->tableInventaris->setItem(i, 0, new QTableWidgetItem(SecondWindow::dataInventaris[i].nama));
        ui->tableInventaris->setItem(i, 1, new QTableWidgetItem(SecondWindow::dataInventaris[i].kategori));
        ui->tableInventaris->setItem(i, 2, new QTableWidgetItem(QString::number(SecondWindow::dataInventaris[i].jumlah)));
    }
}

void thirdwindow::on_btnUrut_clicked()
{
    QString kriteria = ui->cbSort->currentText();
    sortData(kriteria);
    loadData();  // Perbarui tabel setelah diurutkan
}

void thirdwindow::sortData(const QString &kriteria)
{
    for (int i = 0; i < SecondWindow::jumlahData - 1; ++i) {
        for (int j = 0; j < SecondWindow::jumlahData - i - 1; ++j) {
            bool needSwap = false;

            if (kriteria == "Nama" && SecondWindow::dataInventaris[j].nama > SecondWindow::dataInventaris[j + 1].nama) {
                needSwap = true;
            } else if (kriteria == "Kategori" && SecondWindow::dataInventaris[j].kategori > SecondWindow::dataInventaris[j + 1].kategori) {
                needSwap = true;
            } else if (kriteria == "Jumlah" && SecondWindow::dataInventaris[j].jumlah > SecondWindow::dataInventaris[j + 1].jumlah) {
                needSwap = true;
            }

            if (needSwap) {
                std::swap(SecondWindow::dataInventaris[j], SecondWindow::dataInventaris[j + 1]);
            }
        }
    }
}
