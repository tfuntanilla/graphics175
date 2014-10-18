#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"

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

void MainWindow::on_xTransSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->xTrans = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_yTransSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->yTrans = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_zTransSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->zTrans = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_angleRotSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->angle = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_xRotSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->xRot = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_yRotSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->yRot = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_zRotSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->zRot = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_xScaleSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->xScale = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_yScaleSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->yScale = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_zScaleSlider_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->zScale = value;
    ui->renderwindowwidget->GetRenderWindow()->render();
}
