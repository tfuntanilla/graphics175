#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

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

    void on_angleRotSlider_valueChanged(int value);

    void on_xRotSlider_valueChanged(int value);

    void on_yRotSlider_valueChanged(int value);

    void on_zRotSlider_valueChanged(int value);

    void on_xScaleSlider_valueChanged(int value);

    void on_yScaleSlider_valueChanged(int value);

    void on_zScaleSlider_valueChanged(int value);

    void on_wireFrameButton_toggled(bool checked);

    void on_projectionButton_toggled(bool checked);

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
