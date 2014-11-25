#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>

#include "scenehandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_zTransSlider_valueChanged(int value);

    void on_xTransSlider_valueChanged(int value);

    void on_yTransSlider_valueChanged(int value);

    void on_xRotSlider_valueChanged(int value);

    void on_yRotSlider_valueChanged(int value);

    void on_zRotSlider_valueChanged(int value);

    void on_xScaleSlider_valueChanged(int value);

    void on_yScaleSlider_valueChanged(int value);

    void on_zScaleSlider_valueChanged(int value);

    void on_actionOpen_triggered();

    void handleScene(QString filename);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_actionSave_triggered();

    void on_polygonMode_comboBox_activated(const QString &arg1);

    void on_comboBox_projectionMode_activated(const QString &arg1);

    void on_colorButton_Mat_clicked();

    void on_comboBox_shading_activated(const QString &arg1);

    void on_comboBox_lights_activated(const QString &arg1);

    void on_horizontalSlider_lightPosX_valueChanged(int value);

    void on_horizontalSlider_lightPosY_valueChanged(int value);

    void on_horizontalSlider_lightPosZ_valueChanged(int value);

    void on_comboBox_lightType_activated(const QString &arg1);

    void on_horizontalSlider_Ia_valueChanged(int value);

    void on_horizontalSlider_Id_valueChanged(int value);

    void on_horizontalSlider_Is_valueChanged(int value);

    void on_colorButton_Light_clicked();

    void on_horizontalSlider_Ka_valueChanged(int value);

    void on_horizontalSlider_Kd_valueChanged(int value);

    void on_horizontalSlider_Ks_valueChanged(int value);

    void on_horizontalSlider_n_valueChanged(int value);

    void on_pushButton_newLight_clicked();

    void on_pushButton_removeLight_clicked();

    void on_listWidget_lights_itemClicked(QListWidgetItem *item);

    void on_comboBox_Kcomponent_activated(const QString &arg1);

    void on_horizontalSlider_attenuation_valueChanged(int value);

    void on_horizontalSlider_lightDist_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    bool fileOnLoad; // flag indicating whether a file is currently being rendered
    std::string pathOfFile; // gets the path of of the JSON file

    bool ambSelected, diffSelected, specSelected;
    bool red, green, blue;

};

#endif // MAINWINDOW_H
