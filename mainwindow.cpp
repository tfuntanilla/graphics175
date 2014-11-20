#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"
#include <iostream>
#include <QRgb>
#include <QScrollArea>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    fileOnLoad = false;

    menuBar()->setNativeMenuBar(false);

    ambSelected = true; diffSelected = false; specSelected = false;

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
    //ui->renderwindowwidget->GetRenderWindow()->collectShapes();
    ui->renderwindowwidget->GetRenderWindow()->renderLater();

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

    ui->xTransSlider->setValue(currXTrans);
    ui->yTransSlider->setValue(currYTrans);
    ui->zTransSlider->setValue(currZTrans);

    ui->xRotSlider->setValue(currXRot);
    ui->yRotSlider->setValue(currYRot);
    ui->zRotSlider->setValue(currZRot);

    ui->xScaleSlider->setValue(currXScale);
    ui->yScaleSlider->setValue(currYScale);
    ui->zScaleSlider->setValue(currZScale);


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

void MainWindow::on_polygonMode_comboBox_activated(const QString &arg1)
{
    if (arg1 == "Wire Frame") {
        ui->renderwindowwidget->GetRenderWindow()->toggleWireFrame(true);
    }
    else {
        ui->renderwindowwidget->GetRenderWindow()->toggleWireFrame(false);
    }
}

void MainWindow::on_comboBox_projectionMode_activated(const QString &arg1)
{

    if (arg1 == "Perspective") {
       ui->renderwindowwidget->GetRenderWindow()->perspectiveOn = true;
       ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        ui->renderwindowwidget->GetRenderWindow()->perspectiveOn = false;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_colorButton_Mat_clicked()
{
    QColorDialog *qcd = new QColorDialog(QColor::fromRgb(0, 0, 0, 255), this);
    QColor color = qcd->getColor();
    if(color.isValid()) {
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton_Mat->setStyleSheet(qss);

        ui->renderwindowwidget->GetRenderWindow()->Ka_r = (float)color.redF();
        //qDebug() << "Ambient" << (float)color.redF();
        ui->renderwindowwidget->GetRenderWindow()->Ka_g = (float)color.greenF();
        //qDebug() << "Ambient" << (float)color.greenF();
        ui->renderwindowwidget->GetRenderWindow()->Ka_b = (float)color.blueF();
        //qDebug() << "Ambient" << (float)color.blueF();

        ui->renderwindowwidget->GetRenderWindow()->Kd_r = (float)color.redF();
        //qDebug() << "Diffuse" << (float)color.redF();
        ui->renderwindowwidget->GetRenderWindow()->Kd_g = (float)color.greenF();
        //qDebug() << "Diffuse" << (float)color.greenF();
        ui->renderwindowwidget->GetRenderWindow()->Kd_b = (float)color.blueF();
        //qDebug() << "Diffuse" << (float)color.blueF();


        ui->renderwindowwidget->GetRenderWindow()->Ks_r = (float)color.redF();
        //qDebug() << "Specular" << (float)color.redF();
        ui->renderwindowwidget->GetRenderWindow()->Ks_g = (float)color.greenF();
        //qDebug() << "Specular" << (float)color.greenF();
        ui->renderwindowwidget->GetRenderWindow()->Ks_b = (float)color.blueF();
        //qDebug() << "Specular" << (float)color.blueF();

        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_shading_activated(const QString &arg1)
{
    if (arg1 == "No Shading") {
        ui->renderwindowwidget->GetRenderWindow()->setShader(0, 0, 0);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Flat") {
        ui->renderwindowwidget->GetRenderWindow()->setShader(1, 0, 0);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }

    else if (arg1 == "Gouraud") {
        ui->renderwindowwidget->GetRenderWindow()->setShader(0, 1, 0);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }

    else {
        ui->renderwindowwidget->GetRenderWindow()->setShader(0, 0, 1);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_lights_activated(const QString &arg1)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();

        if (arg1 == "Point") {
            ui->renderwindowwidget->GetRenderWindow()->lightPos[index].setW(1.0);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }

        else if (arg1 == "Directional") {
            ui->renderwindowwidget->GetRenderWindow()->lightPos[index].setW(0.0);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
    }
}

void MainWindow::on_horizontalSlider_lightPosX_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        ui->renderwindowwidget->GetRenderWindow()->lightPos[index].setX((float)value);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_horizontalSlider_lightPosY_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        ui->renderwindowwidget->GetRenderWindow()->lightPos[index].setY((float)value);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_horizontalSlider_lightPosZ_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        ui->renderwindowwidget->GetRenderWindow()->lightPos[index].setZ((float)value);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_lightType_activated(const QString &arg1)
{
    if (arg1 == "Ambient") {
        ambSelected = true;
        diffSelected = false;
        specSelected = false;
    }
    else if (arg1 == "Diffuse") {
        ambSelected = false;
        diffSelected = true;
        specSelected = false;
    }
    else if (arg1 == "Specular") {
        ambSelected = false;
        diffSelected = false;
        specSelected = true;
    }
}

void MainWindow::on_horizontalSlider_Ia_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Ia = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_Id_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Id = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_Is_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Is = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_colorButton_Light_clicked()
{
    QColorDialog *qcd = new QColorDialog(QColor::fromRgb(0, 0, 0, 255), this);
    QColor color = qcd->getColor();
    if(color.isValid()) {
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton_Light->setStyleSheet(qss);

        if (ambSelected) {
            ui->renderwindowwidget->GetRenderWindow()->Ia_r = (float)color.redF();
            //qDebug() << "Ambient" << (float)color.redF();
            ui->renderwindowwidget->GetRenderWindow()->Ia_g = (float)color.greenF();
            //qDebug() << "Ambient" << (float)color.greenF();
            ui->renderwindowwidget->GetRenderWindow()->Ia_b = (float)color.blueF();
            //qDebug() << "Ambient" << (float)color.blueF();
        }
        else if (diffSelected) {
            ui->renderwindowwidget->GetRenderWindow()->Id_r = (float)color.redF();
            //qDebug() << "Diffuse" << (float)color.redF();
            ui->renderwindowwidget->GetRenderWindow()->Id_g = (float)color.greenF();
            //qDebug() << "Diffuse" << (float)color.greenF();
            ui->renderwindowwidget->GetRenderWindow()->Id_b = (float)color.blueF();
            //qDebug() << "Diffuse" << (float)color.blueF();
        }
        else if (specSelected) {
            ui->renderwindowwidget->GetRenderWindow()->Is_r = (float)color.redF();
            //qDebug() << "Specular" << (float)color.redF();
            ui->renderwindowwidget->GetRenderWindow()->Is_g = (float)color.greenF();
            //qDebug() << "Specular" << (float)color.greenF();
            ui->renderwindowwidget->GetRenderWindow()->Is_b = (float)color.blueF();
            //qDebug() << "Specular" << (float)color.blueF();
        }
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_horizontalSlider_Ka_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Ka = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_Kd_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Kd = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_Ks_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->Ks = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_n_valueChanged(int value)
{
    ui->renderwindowwidget->GetRenderWindow()->n = (float)value;
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_pushButton_newLight_clicked()
{
    ui->renderwindowwidget->GetRenderWindow()->totalLights++;
    int lights = ui->renderwindowwidget->GetRenderWindow()->totalLights;
    QString newlight = "light_";
    QString totalLights;
    ui->listWidget_lights->addItem(newlight.append(totalLights.setNum(lights)));

}

void MainWindow::on_pushButton_removeLight_clicked()
{

}

void MainWindow::on_listWidget_lights_itemClicked(QListWidgetItem *item)
{

}
