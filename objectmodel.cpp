#include "objectmodel.h"

ObjectModel::ObjectModel()
{
    name = " ";
    originFile = " ";

    xTrans = 0.0; yTrans = 0.0; zTrans = 0.0;
    xRot = 0.0; yRot = 0.0; zRot = 0.0;
    xScale = 30.0; yScale = 30.0; zScale = 30.0;

    Ka = 1.0; Kd = 1.0; Ks = 1.0;
    mtlColor = QColor("white");

}

ObjectModel::~ObjectModel()
{
	
}

void ObjectModel::setNameAndIndex(QString n, QString f, int i)
{
    name = n;
    originFile = f;
    index = i;
}

void ObjectModel::setPropertiesValues(float xT, float yT, float zT, float xR, float yR, float zR,
                                      float xS, float yS, float zS)
{

    xTrans = xT; yTrans = yT; zTrans = zT;
    xRot = xR; yRot = yR; zRot = zR;
    xScale = xS; yScale = yS; zScale = zS;

}

void ObjectModel::setModel(QMatrix4x4 matrix)
{
    model *= matrix;
}

void ObjectModel::setProjection(QMatrix4x4 matrix)
{
    projection = matrix;
}

void ObjectModel::setView(QMatrix4x4 matrix)
{
    view = matrix;
}

void ObjectModel::setKa(float val)
{
    Ka = val;
}

void ObjectModel::setKd(float val)
{
    Kd = val;
}

void ObjectModel::setKs(float val)
{
    Ks = val;
}

void ObjectModel::setMaterialColor(QColor c)
{
    mtlColor = c;
}

GLfloat ObjectModel::getKa()
{
    return Ka;
}

GLfloat ObjectModel::getKd()
{
    return Kd;
}

GLfloat ObjectModel::getKs()
{
    return Ks;
}

QVector3D ObjectModel::getKaRGB()
{
    return Ka * getColor();
}

QVector3D ObjectModel::getKdRGB()
{
    return Kd * getColor();
}

QVector3D ObjectModel::getKsRGB()
{
    return Ks * getColor();
}

QVector3D ObjectModel::getColor()
{
    return QVector3D((float)mtlColor.redF(), (float)mtlColor.greenF(), (float)mtlColor.blueF());
}

QColor ObjectModel::getActualColor()
{
    return mtlColor;
}

QString ObjectModel::getName()
{
    return name;
}

QString ObjectModel::getOriginFile()
{
    return originFile;
}

QMatrix4x4 ObjectModel::getProjection()
{
	return projection;
}

QMatrix4x4 ObjectModel::getView()
{
    return view;
}

QMatrix4x4 ObjectModel::getModel()
{
    return model;
}
