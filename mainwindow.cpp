#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "renderwindow.h"
#include <iostream>
#include <cmath>
#include <QRgb>
#include <QScrollArea>
#include <QColorDialog>

#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    fileOnLoad = false;

    menuBar()->setNativeMenuBar(false);

    ambSelected = true; diffSelected = false; specSelected = false;
    ui->listWidget_lights->setCurrentRow(0);
    red = false; green = false; blue = false;

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
    QVector<Lights*> lightSettings;

    scene.scenedemoRead(filename, scenes);

    for (int i=0; i<scenes[0]->root.size(); i++) {
        if (scenes[0]->root[i]->type == "model") {
            models.push_back(static_cast<Model*>(scenes[0]->root[i]->children[0]));
        }
        else if (scenes[0]->root[i]->type == "light") {
            lightSettings.push_back(static_cast<Lights*>(scenes[0]->root[i]->children[0]));
        }
    }

    QVector<QString> names, lNames, lSources;
    QVector<QString> filenames;
    QVector<QMatrix4x4> matrices;

    QVector<float> n, d;
    QVector<QVector3D> t, r, s, k, ac, dc, sc, il, af;
    QVector<QVector4D> lp;

    QVector<std::string> objectFiles;

    // Store contents of JSON file in appropriate vectors
    for (int i = 0; i < models.size(); i++) {
        names.push_back(models[i]->name);
        filenames.push_back(models[i]->fileName);
        matrices.push_back(models[i]->transform);
        t.push_back(models[i]->translate);
        r.push_back(models[i]->rotate);
        s.push_back(models[i]->scale);
        k.push_back(models[i]->kConsts);
        n.push_back(models[i]->shine);

        ui->listWidget->insertItem(i, models[i]->name);
    }

    for (int i = 0; i < lightSettings.size(); i++) {
        lNames.push_back(lightSettings[i]->name);
        //qDebug() << "Names:" << lNames;
        lSources.push_back(lightSettings[i]->source);
        //qDebug() << "Sources:" << lSources;
        lp.push_back(lightSettings[i]->lightPosition);
        //qDebug() << "Light Position:" << lp;
        ac.push_back(lightSettings[i]->ambientColor);
        //qDebug() << "Ambient:" << ac;
        dc.push_back(lightSettings[i]->diffuseColor);
        //qDebug() << "Diffuse:" << dc;
        sc.push_back(lightSettings[i]->specColor);
        //qDebug() << "Specular:" << sc;
        il.push_back(lightSettings[i]->intensityLevel);
        //qDebug() << "Intensities:" << il;
        af.push_back(lightSettings[i]->attenuationFactors);
        //qDebug() << "Attenuation Factors:" << af;
        d.push_back(lightSettings[i]->distance);
        //qDebug() << "Distance:" << d;

        ui->listWidget_lights->insertItem(i, lightSettings[i]->name);
    }

    ui->listWidget->setCurrentRow(0);
    ui->listWidget_lights->setCurrentRow(0);

    // Convert QString filenames to const char *
    // Necessary for loading the OBJ files in tinyobj parser
    for (int i=0; i<filenames.size(); i++) {
        std::string str = convertQStringtoString(filenames[i]);
        objectFiles.push_back(str);
    }

    // Send attributes of the JSON file to the render
    ui->renderwindowwidget->GetRenderWindow()->setFilePath(pathOfFile);
    //std::cout << pathOfFile << std::endl;
    ui->renderwindowwidget->GetRenderWindow()->getFileAndMatrices(names, filenames, objectFiles, matrices);
    ui->renderwindowwidget->GetRenderWindow()->updateModelProperties(models.size(), t, r, s, k, n);
    ui->renderwindowwidget->GetRenderWindow()->updateLightProperties(lightSettings.size(), lp, af, ac, dc, sc, il, d);
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

    int kaVal = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].getKa();
    int kdVal = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].getKd();
    int ksVal = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].getKs();

    ui->horizontalSlider_Ka->setValue(asin(kaVal) * 180/PI);
    ui->horizontalSlider_Kd->setValue(asin(kdVal) * 180/PI);
    ui->horizontalSlider_Ks->setValue(asin(ksVal) * 180/PI);

    QColor color =ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].getActualColor();
    if(color.isValid()) {
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton_Mat->setStyleSheet(qss);
    }

    int nVal = ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].getN();
    ui->horizontalSlider_n->setValue(nVal);
}

void MainWindow::on_actionSave_triggered()
{
    QString out = QFileDialog::getSaveFileName(this, "Save As");

    SceneHandler savedScene;

    QVector<Scene *> scenes;

    Scene* s = new Scene();
    scenes.push_back(s);

    QString type = "model";
    QString lightType = "light";
    QString texType = "texture";
    QVector<QString> names, lightNames, lightSources, mappings, wrapModes, interpolations, bumpModes;
    QVector<QString> files;
    QVector<QString> qfiles;
    QVector<QMatrix4x4> models;

    QVector<QVector4D> lpos;
    QVector<QVector3D> tr, ro, sc, K, ambC, diffC, specC, iLevel, attenF;
    QVector<float> n, d;

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
        K.push_back(QVector3D(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getKa(),
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getKd(),
                               ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getKs()));
        n.push_back(ui->renderwindowwidget->GetRenderWindow()->objectmodels[i].getN());
    }

    int lightsTotal = ui->renderwindowwidget->GetRenderWindow()->totalLights;
    for (int i = 0; i < lightsTotal; i++) {
        QString lightN = "light_";
        QString lightID;
        lightNames.push_back(lightN.append(lightID.setNum(i+1)));
        lightSources.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getLightSource(i));
        lpos.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[i]);
        ambC.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getIaRGB());
        diffC.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getIdRGB(i));
        specC.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getIsRGB(i));
        iLevel.push_back(QVector3D(ui->renderwindowwidget->GetRenderWindow()->lighting.getIa(),
                                   ui->renderwindowwidget->GetRenderWindow()->lighting.getId(i),
                                   ui->renderwindowwidget->GetRenderWindow()->lighting.getIs(i)));
        attenF.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getAttenuationFactors(i));
        d.push_back(ui->renderwindowwidget->GetRenderWindow()->lighting.getLightDistance(i));
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
        m->kConsts = K[i];
        m->shine = n[i];

        scenes[0]->root.push_back(new Node());
        scenes[0]->root[i]->type = type;
        scenes[0]->root[i]->children.push_back(new Node());
        scenes[0]->root[i]->children[0] = m;
    }

    for (int i = 0; i < lightsTotal; i++) {
        Lights* l = new Lights();
        l->name = lightNames[i];
        l->source = lightSources[i];
        l->lightPosition = lpos[i];
        l->ambientColor = ambC[i];
        l->diffuseColor = diffC[i];
        l->specColor = specC[i];
        l->intensityLevel = iLevel[i];
        l->attenuationFactors = attenF[i];
        l->distance = d[i];

        scenes[0]->root.push_back(new Node());
        scenes[0]->root[i+totalModels]->type = lightType;
        scenes[0]->root[i+totalModels]->children.push_back(new Node());
        scenes[0]->root[i+totalModels]->children[0] = l;
    }

    const char *c = convertQStringtoString(out);
    scenes[0]->name = out;
    scenes[0]->description = QString("This is ").append(c);

    savedScene.scenedemoWrite(out, scenes);
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

void MainWindow::on_comboBox_shading_activated(const QString &arg1)
{
    int light = ui->listWidget_lights->currentRow();
    if (ui->listWidget_lights->count() > 1 && light != 0) {
        ui->listWidget_lights->setCurrentRow(0);
    }

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

    else if (arg1 == "Phong") {
        ui->renderwindowwidget->GetRenderWindow()->setShader(0, 0, 1);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_lights_activated(const QString &arg1)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        if (index >= 0) {
            if (arg1 == "Point") {
                ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].setW(1.0);
                ui->renderwindowwidget->GetRenderWindow()->renderLater();
            }
            else if (arg1 == "Directional") {
                ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].setW(0.0);
                ui->renderwindowwidget->GetRenderWindow()->renderLater();
            }
        }
    }
}

void MainWindow::on_horizontalSlider_lightPosX_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].setX((float)value);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select light from list."));

        }
    }
}

void MainWindow::on_horizontalSlider_lightPosY_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].setY((float)value);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select light from list."));

        }
    }
}

void MainWindow::on_horizontalSlider_lightPosZ_valueChanged(int value)
{
    if (ui->listWidget_lights->count() > 0) {
        int index = ui->listWidget_lights->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].setZ((float)value);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select light from list."));

        }
    }
}

void MainWindow::on_comboBox_lightType_activated(const QString &arg1)
{
    int index = ui->listWidget_lights->currentRow();
    QVector3D iargb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIaRGB();
    QVector3D* idrgb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIdRGB();
    QVector3D* isrgb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIsRGB();

    if (arg1 == "Ambient") {
        ambSelected = true;
        diffSelected = false;
        specSelected = false;

        if (index >= 0) {
            QColor color(iargb.x()*255, iargb.y()*255, iargb.z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
    else if (arg1 == "Diffuse") {
        ambSelected = false;
        diffSelected = true;
        specSelected = false;

        if (index >= 0) {
            QColor color(idrgb[index].x()*255, idrgb[index].y()*255, idrgb[index].z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
    else if (arg1 == "Specular") {
        ambSelected = false;
        diffSelected = false;
        specSelected = true;

        if (index >= 0) {
            QColor color(isrgb[index].x()*255, isrgb[index].y()*255, isrgb[index].z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
}

void MainWindow::on_horizontalSlider_Ia_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    ui->renderwindowwidget->GetRenderWindow()->lighting.setIaValue(adjustedValue);
    ui->renderwindowwidget->GetRenderWindow()->renderLater();

}

void MainWindow::on_horizontalSlider_Id_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    int index = ui->listWidget_lights->currentRow();
    if (index >= 0) {
        ui->renderwindowwidget->GetRenderWindow()->lighting.setIdValues(index, adjustedValue);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("Select light from list."));
    }
}

void MainWindow::on_horizontalSlider_Is_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    int index = ui->listWidget_lights->currentRow();
    if (index >= 0) {
        ui->renderwindowwidget->GetRenderWindow()->lighting.setIsValues(index, adjustedValue);
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("Select light from list."));
    }
}

void MainWindow::on_colorButton_Light_clicked()
{
    QColorDialog *qcd = new QColorDialog(QColor::fromRgb(0, 0, 0, 255), this);
    QColor color = qcd->getColor();
    if(color.isValid()) {
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton_Light->setStyleSheet(qss);

        int index = ui->listWidget_lights->currentRow();

        if (index >= 0) {
            if (ambSelected) {
                ui->renderwindowwidget->GetRenderWindow()->lighting.setIaRGBValues(color.redF(), color.greenF(), color.blueF());
            }
            else if (diffSelected) {
                ui->renderwindowwidget->GetRenderWindow()->lighting.setIdRGBValues(index, color.redF(), color.greenF(), color.blueF());
            }
            else if (specSelected) {
                ui->renderwindowwidget->GetRenderWindow()->lighting.setIsRGBValues(index, color.redF(), color.greenF(), color.blueF());
            }

            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
    }
}

void MainWindow::on_colorButton_Mat_clicked()
{
    QColorDialog *qcd = new QColorDialog(QColor::fromRgb(0, 0, 0, 255), this);
    QColor color = qcd->getColor();
    if(color.isValid()) {
        QString qss = QString("background-color: %1").arg(color.name());
        ui->colorButton_Mat->setStyleSheet(qss);

        if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
            int index = ui->listWidget->currentRow();
            if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
                ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].setMaterialColor(color);
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
}

void MainWindow::on_horizontalSlider_Ka_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].setKa(adjustedValue);
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

void MainWindow::on_horizontalSlider_Kd_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].setKd(adjustedValue);
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

void MainWindow::on_horizontalSlider_Ks_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].setKs(adjustedValue);
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

void MainWindow::on_horizontalSlider_n_valueChanged(int value)
{
    if (!ui->renderwindowwidget->GetRenderWindow()->objectmodels.empty()) {
        int index = ui->listWidget->currentRow();
        if ((index >= 0) && (index < ui->renderwindowwidget->GetRenderWindow()->objectmodels.size())) {
            ui->renderwindowwidget->GetRenderWindow()->objectmodels[index].setN((float)value);
            ui->renderwindowwidget->GetRenderWindow()->renderLater();
        }
        else {
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("No file loaded. Load scene file first."));
    }
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_pushButton_newLight_clicked()
{
    if (ui->renderwindowwidget->GetRenderWindow()->totalLights == 10) {
        QMessageBox::information(this, QString("Alert"), QString("Max number of light sources reached."));
    }
    else {
        ui->renderwindowwidget->GetRenderWindow()->setTotalLights(1);
        int lights = ui->renderwindowwidget->GetRenderWindow()->totalLights;
        QString newlight = "light_";
        QString totalLights;
        ui->listWidget_lights->addItem(newlight.append(totalLights.setNum(lights)));
    }
}

void MainWindow::on_pushButton_removeLight_clicked()
{
    if (ui->listWidget_lights->count() == 0) {
        QMessageBox::information(this, QString("Alert"), QString("Nothing to be removed."));
    }
    else {
        int index = ui->listWidget_lights->currentRow();
        if (index < 0 || index > ui->listWidget_lights->count()) {
            QMessageBox::information(this, QString("Alert"), QString("Select light to be removed from list."));
        }
        else {
            ui->renderwindowwidget->GetRenderWindow()->setTotalLights(-1);
            QListWidgetItem* item = ui->listWidget_lights->takeItem(index);
            delete item;
        }
    }
}

void MainWindow::on_listWidget_lights_itemClicked(QListWidgetItem *item)
{
    item->setSelected(true);
    int index = ui->listWidget_lights->currentRow();

    int lpX = ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].x();
    int lpY = ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].y();
    int lpZ = ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].z();
    int lpW = ui->renderwindowwidget->GetRenderWindow()->lighting.lightPos[index].w();

    ui->horizontalSlider_lightPosX->setValue(lpX);
    ui->horizontalSlider_lightPosY->setValue(lpY);
    ui->horizontalSlider_lightPosZ->setValue(lpZ);

    if (lpW == 1) {
        ui->comboBox_lights->setCurrentIndex(0);
    }
    else if (lpW == 0) {
        ui->comboBox_lights->setCurrentIndex(1);
    }

    float ia = ui->renderwindowwidget->GetRenderWindow()->lighting.getIa();
    float id = ui->renderwindowwidget->GetRenderWindow()->lighting.getId(index);
    float is = ui->renderwindowwidget->GetRenderWindow()->lighting.getIs(index);

    ui->horizontalSlider_Ia->setValue(asin(ia) * 180/PI);
    ui->horizontalSlider_Id->setValue(asin(id) * 180/PI);
    ui->horizontalSlider_Is->setValue(asin(is) * 180/PI);

    float ld = ui->renderwindowwidget->GetRenderWindow()->lighting.getLightDistance(index);
    ui->horizontalSlider_lightDist->setValue(asin(ld) * 180/PI);

    QVector3D atten = ui->renderwindowwidget->GetRenderWindow()->lighting.getAttenuationFactors(index);
    ui->horizontalSlider_constAtten->setValue(asin(atten.x()) * 180/PI);
    ui->horizontalSlider_linearAtten->setValue(asin(atten.y()) * 180/PI);
    ui->horizontalSlider_quadAtten->setValue(asin(atten.z()) * 180/PI);

    QVector3D iargb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIaRGB();
    QVector3D* idrgb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIdRGB();
    QVector3D* isrgb = ui->renderwindowwidget->GetRenderWindow()->lighting.getIsRGB();

    if (ambSelected) {
        if (index >= 0) {
            QColor color(iargb.x()*255, iargb.y()*255, iargb.z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
    else if (diffSelected) {
        if (index >= 0) {
            QColor color(idrgb[index].x()*255, idrgb[index].y()*255, idrgb[index].z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
    else if (specSelected) {
        if (index >= 0) {
            QColor color(isrgb[index].x()*255, isrgb[index].y()*255, isrgb[index].z()*255, 255);
            if(color.isValid()) {
                QString qss = QString("background-color: %1").arg(color.name());
                ui->colorButton_Light->setStyleSheet(qss);
            }
        }
    }
}

void MainWindow::on_horizontalSlider_constAtten_valueChanged(int value)
{
    if (ui->comboBox_lights->itemText(ui->comboBox_lights->currentIndex()) == "Point") {
        float adjustedValue = -cos((value + 90) * PI / 180.0);
        int index = ui->listWidget->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.setConstantAtten(index, adjustedValue);
        }
        else{
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("Disabled for directional light"));
    }

}

void MainWindow::on_horizontalSlider_lightDist_valueChanged(int value)
{
    float adjustedValue = -cos((value + 90) * PI / 180.0);
    int index = ui->listWidget->currentRow();
    if (index >= 0) {
        ui->renderwindowwidget->GetRenderWindow()->lighting.setLightDistance(index, adjustedValue);
    }
    else{
        QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
    }
    ui->renderwindowwidget->GetRenderWindow()->renderLater();
}

void MainWindow::on_horizontalSlider_linearAtten_valueChanged(int value)
{
    if (ui->comboBox_lights->itemText(ui->comboBox_lights->currentIndex()) == "Point") {
        float adjustedValue = -cos((value + 90) * PI / 180.0);
        int index = ui->listWidget->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.setLinearAtten(index, adjustedValue);
        }
        else{
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("Disabled for directional light"));
    }
}

void MainWindow::on_horizontalSlider_quadAtten_valueChanged(int value)
{
    if (ui->comboBox_lights->itemText(ui->comboBox_lights->currentIndex()) == "Point") {
        float adjustedValue = -cos((value + 90) * PI / 180.0);
        int index = ui->listWidget->currentRow();
        if (index >= 0) {
            ui->renderwindowwidget->GetRenderWindow()->lighting.setQuadAtten(index, adjustedValue);
        }
        else{
            QMessageBox::information(this, QString("Alert"), QString("Select object from list."));
        }
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        QMessageBox::information(this, QString("Alert"), QString("Disabled for directional light"));
    }
}

void MainWindow::on_comboBox_textureMapping_activated(const QString &arg1)
{
    if (arg1 == "Box") {
        ui->renderwindowwidget->GetRenderWindow()->boxMapOn = true;
        ui->renderwindowwidget->GetRenderWindow()->UVOn = false;
        ui->renderwindowwidget->GetRenderWindow()->sphereMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->cylinderMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Sphere") {
        ui->renderwindowwidget->GetRenderWindow()->boxMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->UVOn = false;
        ui->renderwindowwidget->GetRenderWindow()->sphereMapOn = true;
        ui->renderwindowwidget->GetRenderWindow()->cylinderMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Cylinder") {
        ui->renderwindowwidget->GetRenderWindow()->boxMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->UVOn = false;
        ui->renderwindowwidget->GetRenderWindow()->cylinderMapOn = true;
        ui->renderwindowwidget->GetRenderWindow()->sphereMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "UV") {
        ui->renderwindowwidget->GetRenderWindow()->boxMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->UVOn = true;
        ui->renderwindowwidget->GetRenderWindow()->cylinderMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->sphereMapOn = false;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_textureWrapMode_activated(const QString &arg1)
{
    if (arg1 == "Repeat") {
        ui->renderwindowwidget->GetRenderWindow()->wrapMode = 0;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Mirrored") {
        ui->renderwindowwidget->GetRenderWindow()->wrapMode = 1;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Clamp to Edge") {
        ui->renderwindowwidget->GetRenderWindow()->wrapMode = 2;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else if (arg1 == "Clamp to Border") {
        ui->renderwindowwidget->GetRenderWindow()->wrapMode = 3;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_textureInterpolation_activated(const QString &arg1)
{
    if (arg1 == "Nearest") {
        ui->renderwindowwidget->GetRenderWindow()->texInterpolation = 0;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        ui->renderwindowwidget->GetRenderWindow()->texInterpolation = 1;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}

void MainWindow::on_comboBox_textureBumpMapping_activated(const QString &arg1)
{
    if (arg1 == "Normal") {
        ui->renderwindowwidget->GetRenderWindow()->normalMap = 1;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
    else {
        ui->renderwindowwidget->GetRenderWindow()->normalMap = 0;
        ui->renderwindowwidget->GetRenderWindow()->renderLater();
    }
}
