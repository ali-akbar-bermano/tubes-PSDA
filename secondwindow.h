#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class SecondWindow; }
QT_END_NAMESPACE

struct Item {
    QString nama;
    QString kategori;
    int jumlah;
};

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

    // Menjadikan dataInventaris dan jumlahData public static supaya bisa diakses dari luar
    static const int MAX_DATA = 100;
    static Item dataInventaris[MAX_DATA];
    static int jumlahData;

    // Optional: getter static untuk akses data secara terkontrol
    static int getJumlahData() { return jumlahData; }
    static Item getDataInventaris(int index) { return dataInventaris[index]; }

private slots:
    void on_btnTambah_clicked();
    void on_btnEdit_clicked();
    void on_btnHapus_clicked();
    void on_btnUrut_clicked();
    void on_btnUser_clicked();
    void on_tableInventaris_cellClicked(int row, int column);

private:
    Ui::SecondWindow *ui;

    void refreshTable();
};

#endif // SECONDWINDOW_H
