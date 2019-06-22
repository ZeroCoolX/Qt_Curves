#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->spinPixelScale->setValue(this->ui->renderArea->getPixelScale());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui(){
    this->ui->renderArea->repaint();
    this->ui->spinPixelScale->setValue(this->ui->renderArea->getPixelScale());
    this->ui->spinInterval->setValue(this->ui->renderArea->getIntervalLength());
    this->ui->spinStepCount->setValue(this->ui->renderArea->getStepCount());
}


void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Astroid);
    this->update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Cycloid);
    this->update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HuygensCycloid);
    this->update_ui();
}

void MainWindow::on_btnHypoCycloid_clicked()
{
    this->ui->renderArea->setShape(RenderArea::HypoCycloid);
    this->update_ui();
}


void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->setShape(RenderArea::Line);
    this->update_ui();
}

void MainWindow::on_spinPixelScale_valueChanged(double pixelScale)
{
    this->ui->renderArea->setPixelScale(pixelScale);
}

void MainWindow::on_spinInterval_valueChanged(double interval)
{
    this->ui->renderArea->setIntervalLength(interval);
}

void MainWindow::on_spinStepCount_valueChanged(int stepCount)
{
    this->ui->renderArea->setStepCount(stepCount);
}
