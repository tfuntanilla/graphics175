#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuBar()->setNativeMenuBar(false);

    setLineEditDefaults();

    //connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(xRotationChanged(int)), ui->xRotSlider, SLOT(setValue(int)));
    //connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(yRotationChanged(int)), ui->yRotSlider, SLOT(setValue(int)));

    //connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(xTranslationChanged(int)), ui->xTransSlider, SLOT(setValue(int)));
    //connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(yTranslationChanged(int)), ui->yTransSlider, SLOT(setValue(int)));
    //connect(ui->renderwindowwidget->GetRenderWindow(), SIGNAL(zTranslationChanged(int)), ui->zTransSlider, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

static const char* convertQStringtoString(QString string)
{

    QByteArray byteArray = string.toUtf8();
    const char* cString = byteArray.constData();

    return cString;
}

void MainWindow::setLineEditDefaults()
{
    ui->xTransLineEdit->setText("-10");
    ui->yTransLineEdit->setText("-15");
    ui->zTransLineEdit->setText("0");

    ui->xRotLineEdit->setText("0");
    ui->yRotLineEdit->setText("0");
    ui->zRotLineEdit->setText("0");

    ui->xScaleLineEdit->setText("10");
    ui->yScaleLineEdit->setText("10");
    ui->zScaleLineEdit->setText("0");

}

void MainWindow::on_xTransSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xTrans = value;
    ui->xTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();

    /*
    ui->renderwindowwidget->GetRenderWindow()->xTrans = value;
    ui->xTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_yTransSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yTrans = value;
    ui->yTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();

    /*
    ui->renderwindowwidget->GetRenderWindow()->yTrans = value;   
    ui->yTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_zTransSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zTrans = value;
    ui->zTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();

    /*
    ui->renderwindowwidget->GetRenderWindow()->zTrans = value;
    ui->zTransLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_xRotSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xRot = value;
    ui->xRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();

    /*
    ui->renderwindowwidget->GetRenderWindow()->xRot = value;
    ui->xRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_yRotSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yRot = value;
    ui->yRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    /*
    ui->renderwindowwidget->GetRenderWindow()->yRot = value;
    ui->yRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_zRotSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zRot = value;
    ui->zRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    /*
    ui->renderwindowwidget->GetRenderWindow()->zRot = value;
    ui->zRotLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_xScaleSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xScale = value;
    ui->xScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    /*
    ui->renderwindowwidget->GetRenderWindow()->xScale = value;
    ui->xScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_yScaleSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yScale = value;
    ui->yScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    /*
    ui->renderwindowwidget->GetRenderWindow()->yScale = value;
    ui->yScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
}

void MainWindow::on_zScaleSlider_valueChanged(int value)
{
    int index = ui->listWidget->currentRow();
    ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zScale = value;
    ui->zScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    /*
    ui->renderwindowwidget->GetRenderWindow()->zScale = value;
    ui->zScaleLineEdit->setText(QString::number(value));
    ui->renderwindowwidget->GetRenderWindow()->render();
    */
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

void MainWindow::on_xTransLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->xTransSlider->setValue(value);
}

void MainWindow::on_yTransLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->yTransSlider->setValue(value);
}

void MainWindow::on_zTransLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->zTransSlider->setValue(value);
}

void MainWindow::on_xRotLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->xRotSlider->setValue(value);
}

void MainWindow::on_yRotLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->yRotSlider->setValue(value);
}

void MainWindow::on_zRotLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->zRotSlider->setValue(value);
}

void MainWindow::on_xScaleLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->xScaleSlider->setValue(value);
}

void MainWindow::on_yScaleLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->yScaleSlider->setValue(value);
}

void MainWindow::on_zScaleLineEdit_textChanged(const QString &arg1)
{
    bool ok;
    int value = arg1.toInt(&ok, 10);
    ui->zScaleSlider->setValue(value);
}

void MainWindow::handleScene(QString filename)
{
    SceneHandler scene;

    QVector<Scene*> scenes;
    QVector<Model*> models;

    scene.scenedemoRead("/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/scene.json", scenes);

    for (int i=0; i<scenes[0]->root.size(); i++) {
        if (scenes[0]->root[i]->type == "model") {
            models.push_back(static_cast<Model*>(scenes[0]->root[i]->children[0]));
        }
    }

    QVector<QString> names; // name of the object
    QVector<QString> filenames;
    QVector<QMatrix4x4> matrices;

    QVector<std::string> objectFiles;

    //int row = 0;

    // Store contents of JSON file in appropriate vectors
    for (int i = 0; i < models.size(); i++) {
        names.push_back(models[i]->name);
        filenames.push_back(models[i]->fileName);
        matrices.push_back(models[i]->transform);


        ui->listWidget->insertItem(i, models[i]->name);
        //ui->listWidget->insertItem(row++, (models[i]->name+"_2"));
        //ui->listWidget->insertItem(row++, (models[i]->name+"_3"));
        //ui->listWidget->insertItem(row++, (models[i]->name+"_4"));
    }

    // Select first element in list widget by default
    ui->listWidget->setCurrentRow(0);


    // Convert QString filenames to const char *
    // Necessary for loading the OBJ files in tinyobj parser
    for (int i=0; i<filenames.size(); i++) {
        std::string str = convertQStringtoString(filenames[i]);
        objectFiles.push_back(str);
    }

    //int totalNumOfObjects = models.size();

    // Send attributes of the JSON file to the render
    ui->renderwindowwidget->GetRenderWindow()->getFileAndMatrices(names, objectFiles, matrices);
    ui->renderwindowwidget->GetRenderWindow()->updateModelProperties(models.size());
    ui->renderwindowwidget->GetRenderWindow()->render();
}

void MainWindow::on_actionOpen_triggered()
{
    //file = QFileDialog::getOpenFileName(this, "Open File");
    //QMessageBox::information(this, "File Selected", file.length() == 0 ? "No File Selected" : file);

    handleScene(file);

}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->currentRow();

    int currXTrans = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xTrans;
    int currYTrans = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yTrans;
    int currZTrans = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zTrans;

    int currXRot = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xRot;
    int currYRot = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yRot;
    int currZRot = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zRot;

    int currXScale = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xScale;
    int currYScale = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yScale;
    int currZScale = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zScale;

    ui->xTransLineEdit->setText(QString::number(currXTrans));
    ui->yTransLineEdit->setText(QString::number(currYTrans));
    ui->zTransLineEdit->setText(QString::number(currZTrans));

    ui->xRotLineEdit->setText(QString::number(currXRot));
    ui->yRotLineEdit->setText(QString::number(currYRot));
    ui->zRotLineEdit->setText(QString::number(currZRot));

    ui->xScaleLineEdit->setText(QString::number(currXScale));
    ui->yScaleLineEdit->setText(QString::number(currYScale));
    ui->zScaleLineEdit->setText(QString::number(currZScale));


}
