#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector4D>

class Light
{
private:

    GLfloat Ia, Id[10], Is[10];
    QVector3D IaRGB, IdRGB[10], IsRGB[10];

    GLfloat lightDistance[10];
    QVector3D attenuationFactors[10];


public:
    Light();

    QVector4D getLightPositions(int i);
    QString getLightSource(int i);

    QVector3D getIaRGB();
    QVector3D* getIdRGB();
    QVector3D* getIsRGB();
    QVector3D getIdRGB(int i);
    QVector3D getIsRGB(int i);

    GLfloat getIa();
    GLfloat *getId();
    GLfloat *getIs();
    float getId(int i);
    float getIs(int i);

    QVector3D getAttenuationFactors(int i);
    float getLightDistance(int i);
    QVector3D *getAttenuationFactors();
    GLfloat* getLightDistance();

    void setIaValue(float val);
    void setIdValues(int i, float val);
    void setIsValues(int i, float val);

    void setIaRGBValues(qreal r, qreal g, qreal b);
    void setIdRGBValues(int i, qreal r, qreal g, qreal b);
    void setIsRGBValues(int i, qreal r, qreal g, qreal b);

    void setQuadAtten(int i, float val);
    void setLinearAtten(int i, float val);
    void setConstantAtten(int i, float val);
    void setLightDistance(int i, float val);

    QVector4D lightPos[10];
};

#endif // LIGHT_H
