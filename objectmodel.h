#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H


#include <QMatrix4x4>

class ObjectModel {

public:
    ObjectModel();
	~ObjectModel();

    void setNameAndIndex(QString name, int i);
    void setPropertiesValues(int xT, int yT, int zT, int xR, int yR, int zR, int xS, int yS, int zS);
    void setModel(QMatrix4x4 matrix);

    QMatrix4x4 getProjection();
    QMatrix4x4 getView();
    QMatrix4x4 getModel();
	QString getIdentifier();

	int index;

	int xTrans;
	int yTrans;
	int zTrans;

	int xRot;
	int yRot;
	int zRot;

	int xScale;
	int yScale;
	int zScale;

private:
	QString identifier;
	QMatrix4x4 projection;
	QMatrix4x4 view;
    QMatrix4x4 model;
	
};

#endif