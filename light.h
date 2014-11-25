#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QVector4D>

class Light
{
private:

    QVector3D IaRGB, IdRGB[10], IsRGB[10];

    GLfloat Ia, Id[10], Is[10];

    //QVector3D KaRGB[10], KdRGB[10], KsRGB[10];

    //GLfloat Ka[10], Kd[10], Ks[10];

    GLfloat n[10];

    GLfloat attenuation[10];
    GLfloat lightDistance[10];


public:
    Light();

    //QVector3D* getKa();
    //QVector3D* getKd();
    //QVector3D* getKs();
    QVector3D getIaRGB();
    QVector3D* getIdRGB();
    QVector3D* getIsRGB();
    GLfloat* getn();
    GLfloat getIa();
    GLfloat *getId();
    GLfloat *getIs();
    //float getIa(int i);
    float getId(int i);
    float getIs(int i);
    float getAttenuationFactor(int i);
    float getLightDistance(int i);
    GLfloat* getAttenuationFactor();
    GLfloat* getLightDistance();

    void setIaValue(float val);
    void setIdValues(int i, float val);
    void setIsValues(int i, float val);
    void setIaRGBValues(qreal r, qreal g, qreal b);
    void setIdRGBValues(int i, qreal r, qreal g, qreal b);
    void setIsRGBValues(int i, qreal r, qreal g, qreal b);
    //void setKaRGBValues(int i, int r, int g, int b);
    //void setKdRGBValues(int i, int r, int g, int b);
    //void setKsRGBValues(int i, int r, int g, int b);
    void setN(int i, float val);
    void setAttenuationFactor(int i, float val);
    void setLightDistance(int i, float val);

    QVector4D lightPos[10];

    //void setKa(int i, float val);
    //void setKd(int i, float val);
    //void setKs(int i, float val);

};

#endif // LIGHT_H
