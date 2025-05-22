#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QWidget>

namespace Ui {
class thirdwindow;
}

class thirdwindow : public QWidget
{
    Q_OBJECT

public:
    explicit thirdwindow(QWidget *parent = nullptr);
    ~thirdwindow();

    void loadData();  // Fungsi untuk menampilkan data inventaris

private slots:
    void on_btnUrut_clicked();  // Slot tombol urut

private:
    Ui::thirdwindow *ui;

    void sortData(const QString &kriteria);  // Fungsi bantu untuk sorting
};

#endif // THIRDWINDOW_H
