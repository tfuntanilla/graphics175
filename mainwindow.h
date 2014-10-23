#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>

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

    void setLineEditDefaults();

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

    void on_wireFrameButton_toggled(bool checked);

    void on_projectionButton_toggled(bool checked);

    void on_xTransLineEdit_textChanged(const QString &arg1);

    void on_yTransLineEdit_textChanged(const QString &arg1);

    void on_zTransLineEdit_textChanged(const QString &arg1);

    void on_xRotLineEdit_textChanged(const QString &arg1);

    void on_yRotLineEdit_textChanged(const QString &arg1);

    void on_zRotLineEdit_textChanged(const QString &arg1);

    void on_xScaleLineEdit_textChanged(const QString &arg1);

    void on_yScaleLineEdit_textChanged(const QString &arg1);

    void on_zScaleLineEdit_textChanged(const QString &arg1);

    void handleScene(QString filename);

    void on_actionOpen_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_actionSave_triggered();


private:
    Ui::MainWindow *ui;

    QString file;

};

#endif // MAINWINDOW_H
