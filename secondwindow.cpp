#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "thirdwindow.h"
#include <QTableWidgetItem>
#include <QHeaderView>
using namespace std;

// Inisialisasi static members
Item SecondWindow::dataInventaris[SecondWindow::MAX_DATA];
int SecondWindow::jumlahData = 0;

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    ui->tableInventaris->setColumnCount(3);
    ui->tableInventaris->setHorizontalHeaderLabels(QStringList() << "Nama Barang" << "Kategori" << "Jumlah");
    ui->tableInventaris->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableInventaris->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInventaris->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableInventaris->setAlternatingRowColors(true);
    ui->tableInventaris->setShowGrid(false);

    ui->cbKategori->addItems(QStringList() << "Elektronik" << "Meubel" << "ATK" << "Lainnya");
    ui->cbSort->addItems(QStringList() << "Nama" << "Kategori" << "Jumlah");

    connect(ui->tableInventaris, &QTableWidget::cellClicked, this, &SecondWindow::on_tableInventaris_cellClicked);
    connect(ui->btnUrut, &QPushButton::clicked, this, &SecondWindow::on_btnUrut_clicked);
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::refreshTable()
{
    ui->tableInventaris->setRowCount(0);
    for (int i = 0; i < SecondWindow::jumlahData; ++i) {
        ui->tableInventaris->insertRow(i);

        QTableWidgetItem *itemNama = new QTableWidgetItem(SecondWindow::dataInventaris[i].nama);
        QTableWidgetItem *itemKategori = new QTableWidgetItem(SecondWindow::dataInventaris[i].kategori);
        QTableWidgetItem *itemJumlah = new QTableWidgetItem(QString::number(SecondWindow::dataInventaris[i].jumlah));

        itemNama->setTextAlignment(Qt::AlignCenter);
        itemKategori->setTextAlignment(Qt::AlignCenter);
        itemJumlah->setTextAlignment(Qt::AlignCenter);

        ui->tableInventaris->setItem(i, 0, itemNama);
        ui->tableInventaris->setItem(i, 1, itemKategori);
        ui->tableInventaris->setItem(i, 2, itemJumlah);
    }
}

void SecondWindow::on_btnTambah_clicked()
{
    if (SecondWindow::jumlahData >= SecondWindow::MAX_DATA) return; // Cegah overflow

    SecondWindow::dataInventaris[SecondWindow::jumlahData].nama = ui->leNamaBarang->text();
    SecondWindow::dataInventaris[SecondWindow::jumlahData].kategori = ui->cbKategori->currentText();
    SecondWindow::dataInventaris[SecondWindow::jumlahData].jumlah = ui->sbJumlah->value();
    SecondWindow::jumlahData++;

    refreshTable();

    ui->leNamaBarang->clear();
    ui->cbKategori->setCurrentIndex(0);
    ui->sbJumlah->setValue(0);
}

void SecondWindow::on_btnEdit_clicked()
{
    int row = ui->tableInventaris->currentRow();
    if (row >= 0 && row < SecondWindow::jumlahData) {
        SecondWindow::dataInventaris[row].nama = ui->leNamaBarang->text();
        SecondWindow::dataInventaris[row].kategori = ui->cbKategori->currentText();
        SecondWindow::dataInventaris[row].jumlah = ui->sbJumlah->value();
        refreshTable();
    }
}

void SecondWindow::on_btnHapus_clicked()
{
    int row = ui->tableInventaris->currentRow();
    if (row >= 0 && row < SecondWindow::jumlahData) {
        for (int i = row; i < SecondWindow::jumlahData - 1; ++i) {
            SecondWindow::dataInventaris[i] = SecondWindow::dataInventaris[i + 1];
        }
        SecondWindow::jumlahData--;
        refreshTable();
    }
}

void SecondWindow::on_tableInventaris_cellClicked(int row, int)
{
    if (row >= 0 && row < SecondWindow::jumlahData) {
        ui->leNamaBarang->setText(SecondWindow::dataInventaris[row].nama);
        ui->cbKategori->setCurrentText(SecondWindow::dataInventaris[row].kategori);
        ui->sbJumlah->setValue(SecondWindow::dataInventaris[row].jumlah);
    }
}

void SecondWindow::on_btnUser_clicked()
{
    thirdwindow *adminWindow = new thirdwindow(); // tanpa parent agar window bisa independent
    adminWindow->setAttribute(Qt::WA_DeleteOnClose);
    adminWindow->show();
    this->hide();
}

void SecondWindow::on_btnUrut_clicked()
{
    QString kriteria = ui->cbSort->currentText();

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
                swap(SecondWindow::dataInventaris[j], SecondWindow::dataInventaris[j + 1]);
            }
        }
    }

    refreshTable();
}
