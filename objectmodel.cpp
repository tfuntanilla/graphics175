#include "objectmodel.h"

ObjectModel::ObjectModel()
{
    identifier = " ";

    projection.setToIdentity();
    view.setToIdentity();
    model.setToIdentity();

    xTrans = 10; yTrans = 15; zTrans = 20;
    xRot = 0; yRot = 0; zRot = 0;
    xScale = 30; yScale = 30; zScale = 30;

}

ObjectModel::~ObjectModel()
{
	
}

void ObjectModel::setNameAndIndex(QString name, int i)
{
    identifier = name;
    index = i;
}

void ObjectModel::setPropertiesValues(int xT, int yT, int zT, int xR, int yR, int zR, int xS, int yS, int zS)
{

	xTrans = xT; yTrans = yT; zTrans = zT;
	xRot = xR; yRot = yR; zRot = zR;
	xScale = xS; yScale = yS; zScale = zS;

}

void ObjectModel::setModel(QMatrix4x4 matrix)
{
    model = matrix;
}

QString ObjectModel::getIdentifier()
{
	return identifier;
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
