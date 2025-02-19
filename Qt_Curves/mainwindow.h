#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAstroid_clicked();

    void on_btnCycloid_clicked();

    void on_btnHuygens_clicked();

    void on_btnHypoCycloid_clicked();

    void on_btnLine_clicked();

    void on_spinPixelScale_valueChanged(double arg1);

    void on_spinInterval_valueChanged(double arg1);

    void on_spinStepCount_valueChanged(int arg1);

    void on_btnBackgroundColor_clicked();

    void on_btnLineColor_clicked();

    void on_btnCircle_clicked();

    void on_btnFancy_clicked();

    void on_btnStarfish_clicked();

    void on_btnCloud_clicked();

    void on_btnInvCloud_clicked();

private:
    void update_ui();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
