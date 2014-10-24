#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileOnLoad = false;

    menuBar()->setNativeMenuBar(false);
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

void MainWindow::on_xTransSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xTrans = value;
            ui->xTransLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_yTransSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yTrans = value;
            ui->yTransLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();

        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_zTransSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zTrans = value;
            ui->zTransLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_xRotSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xRot = value;
            ui->xRotLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }

}

void MainWindow::on_yRotSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yRot = value;
            ui->yRotLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_zRotSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zRot = value;
            ui->zRotLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_xScaleSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].xScale = value;
            ui->xScaleLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }

    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_yScaleSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].yScale = value;
            ui->yScaleLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_zScaleSlider_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].zScale = value;
            ui->zScaleLineEdit->setText(QString::number(value));
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
}

void MainWindow::on_wireFrameButton_toggled(bool checked)
{

    ui->renderwindowwidget->GetRenderWindow()->toggleWireFrame(checked);

}

void MainWindow::on_projectionButton_toggled(bool checked)
{
    ui->renderwindowwidget->GetRenderWindow()->togglePers = checked;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
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

    scene.scenedemoRead(filename, scenes);

    for (int i=0; i<scenes[0]->root.size(); i++) {
        if (scenes[0]->root[i]->type == "model") {
            models.push_back(static_cast<Model*>(scenes[0]->root[i]->children[0]));
        }
    }

    QVector<QString> names;
    QVector<QString> filenames;
    QVector<QMatrix4x4> matrices;

    QVector<QVector3D> t;
    QVector<QVector3D> r;
    QVector<QVector3D> s;

    QVector<std::string> objectFiles;


    // Store contents of JSON file in appropriate vectors
    for (int i = 0; i < models.size(); i++) {
        names.push_back(models[i]->name);
        filenames.push_back(models[i]->fileName);
        matrices.push_back(models[i]->transform);
        t.push_back(models[i]->translate);
        r.push_back(models[i]->rotate);
        s.push_back(models[i]->scale);

        ui->listWidget->insertItem(i, models[i]->name);
    }

    ui->listWidget->setCurrentRow(0);

    // Convert QString filenames to const char *
    // Necessary for loading the OBJ files in tinyobj parser
    for (int i=0; i<filenames.size(); i++) {
        std::string str = convertQStringtoString(filenames[i]);
        objectFiles.push_back(str);
    }

    // Send attributes of the JSON file to the render
    ui->renderwindowwidget->GetRenderWindow()->setFilePath(pathOfFile);
    std::cout << pathOfFile << std::endl;
    ui->renderwindowwidget->GetRenderWindow()->getFileAndMatrices(names, filenames, objectFiles, matrices);
    ui->renderwindowwidget->GetRenderWindow()->updateModelProperties(models.size(), t, r, s);
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
    setLineEditDefaults();
}

void MainWindow::on_actionOpen_triggered()
{

    if (!fileOnLoad) {
        QString file = QFileDialog::getOpenFileName(ui->renderwindowwidget, "Open File", "../Project1/", tr("JSON (*.json)"));

        if(!file.isEmpty()) {

            // get file path - needed to load .obj files in renderwindow.cpp
            QFileInfo filepath(file);
            QString fp = filepath.absoluteFilePath();
            QString base = filepath.baseName();
            QString stuff = filepath.suffix();

            base.append(".");
            base.append(stuff);
            fp.remove(base);

            //qDebug() << fp;
            pathOfFile = convertQStringtoString(fp);

            fileOnLoad = true;
            handleScene(file);
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("No file selected!"));
        }
    }
    else {
         QMessageBox::information(this, QString("Alert"),
                                  QString("Another file is already open. To proceed, close the current window and run app again."));
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    item->setSelected(true);

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

void MainWindow::on_actionSave_triggered()
{
    qDebug() << "Start saving file...";

    QString out = QFileDialog::getSaveFileName(this, "Save As");

    SceneHandler savedScene;

    QVector<Scene *> scenes;

    Scene* s = new Scene();
    scenes.push_back(s);

    QString type = "model";
    QVector<QString> names;
    QVector<QString> files;
    QVector<QString> qfiles;
    QVector<QMatrix4x4> models;

    QVector<QVector3D> tr;
    QVector<QVector3D> ro;
    QVector<QVector3D> sc;


    int totalModels = ui->renderwindowwidget->GetRenderWindow()->objectmodels.size();

    // retrieve objects
    for (int i = 0; i < totalModels; i++) {
        names.push_back(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getName());
        files.push_back(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getOriginFile());
        models.push_back(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getModel());
        tr.push_back(QVector3D(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].xTrans,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].yTrans,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].zTrans));
        ro.push_back(QVector3D(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].xRot,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].yRot,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].zRot));
        sc.push_back(QVector3D(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].xScale,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].yScale,
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].zScale));
    }

    for (int i = 0; i < files.size(); i++) {
        qfiles.push_back(QString(files[i]));
    }

    // store the objects in the scene vector
    for(int i = 0; i < totalModels; i++) {
        Model* m = new Model();
        m->name = names[i];
        m->fileName = qfiles[i];
        m->transform = models[i];
        m->translate = tr[i];
        m->rotate = ro[i];
        m->scale = sc[i];

        scenes[0]->root.push_back(new Node());
        scenes[0]->root[i]->type = type;
        scenes[0]->root[i]->children.push_back(new Node());
        scenes[0]->root[i]->children[0] = m;
    }

    const char *c = convertQStringtoString(out);
    scenes[0]->name = out;
    scenes[0]->description = QString("This is ").append(c);

    savedScene.scenedemoWrite(out, scenes);

    qDebug() << "File saved!";

}

void MainWindow::setLineEditDefaults()
{
    if (fileOnLoad && (ui->renderwindowwidget->GetRenderWindow()->objectmodels.size() > 0)) {
        int xt = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].xTrans;
        ui->xTransLineEdit->setText(QString::number(xt));

        int yt = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].yTrans;
        ui->yTransLineEdit->setText(QString::number(yt));

        int zt = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].zTrans;
        ui->zTransLineEdit->setText(QString::number(zt));

        int xr = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].xRot;
        ui->xRotLineEdit->setText(QString::number(xr));

        int yr = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].yRot;
        ui->yRotLineEdit->setText(QString::number(yr));

        int zr = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].zRot;
        ui->zRotLineEdit->setText(QString::number(zr));

        int xs = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].xScale;
        ui->xScaleLineEdit->setText(QString::number(xs));

        int ys = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].yScale;
        ui->yScaleLineEdit->setText(QString::number(ys));

        int zs = ui->renderwindowwidget->GetRenderWindow()->objectmodels[0].zScale;
        ui->zScaleLineEdit->setText(QString::number(zs));
    }

}
