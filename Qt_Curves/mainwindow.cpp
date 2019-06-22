#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAsteroid_clicked()
{
    this->changeRenderColor(Qt::red);
}

void MainWindow::on_btnCycloid_clicked()
{
    this->changeRenderColor(Qt::green);
}

void MainWindow::on_btnHuygens_clicked()
{
    this->changeRenderColor(Qt::blue);
}

void MainWindow::on_btnHypoCycloid_clicked()
{
    this->changeRenderColor(Qt::yellow);
}

void MainWindow::changeRenderColor(QColor color){
    // change background color for render area
    ui->renderArea->setBackgroundColor(color);
    this->ui->renderArea->repaint();
}

