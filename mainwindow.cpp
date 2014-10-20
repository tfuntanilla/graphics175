#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(zChanged(int)), ui->zTransSlider, SLOT(setValue(int)));
    connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(xRotationChanged(int)), ui->xRotSlider, SLOT(setValue(int)));
    connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(yRotationChanged(int)), ui->yRotSlider, SLOT(setValue(int)));
    connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(zRotationChanged(int)), ui->zRotSlider, SLOT(setValue(int)));
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

void MainWindow::on_wireFrameButton_toggled(bool checked)
{

    ui->renderwindowwidget->GetRenderWindow()->toggleWireFrame(checked);

}

void MainWindow::on_projectionButton_toggled(bool checked)
{
    ui->renderwindowwidget->GetRenderWindow()->togglePers = checked;
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{

}
