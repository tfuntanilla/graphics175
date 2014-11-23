#include "light.h"

#include <QDebug>

Light::Light()
{
    for (int i = 0; i < 10; i++) {

        // initialize to point light source
        lightPos[i].setX(0.0); lightPos[i].setY(0.0); lightPos[i].setZ(0.0); lightPos[i].setW(1.0);

        // initialize intensity factors
        Ia[i] = 1.0; Id[i] = 0.0; Is[i] = 0.0;

        // initialize color components of ambient, diffuse, and specular illumination
        // X is the red component, Y is green, and Z is blue
        IaRGB[i].setX(1.0); IaRGB[i].setY(1.0); IaRGB[i].setZ(1.0);
        IdRGB[i].setX(1.0); IdRGB[i].setY(1.0); IdRGB[i].setZ(1.0);
        IsRGB[i].setX(1.0); IsRGB[i].setY(1.0); IsRGB[i].setZ(1.0);

        // initialize reflectivity coefficient vector values
        KaRGB[i].setX(1.0); KaRGB[i].setY(1.0); KaRGB[i].setZ(1.0);
        KdRGB[i].setX(1.0); KdRGB[i].setY(1.0); KdRGB[i].setZ(1.0);
        KsRGB[i].setX(1.0); KsRGB[i].setY(1.0); KsRGB[i].setZ(1.0);

        // initialize shininess factor
        n[i] = 50.0;
    }

}

QVector3D* Light::getKa()
{
    return KaRGB;
}

QVector3D* Light::getKd()
{
    return KdRGB;
}

QVector3D* Light::getKs()
{
    return KsRGB;
}

QVector3D *Light::getIaRGB()
{
    return IaRGB;
}

QVector3D *Light::getIdRGB()
{
    return IdRGB;
}

QVector3D *Light::getIsRGB()
{
    return IsRGB;
}

GLfloat *Light::getIa()
{
    return Ia;
}

GLfloat *Light::getId()
{
    return Id;
}


GLfloat *Light::getIs()
{
    return Is;
}


float Light::getIa(int i)
{
    return Ia[i];
}

float Light::getId(int i)
{
    return Id[i];
}

float Light::getIs(int i)
{
    return Is[i];
}

float *Light::getn()
{
    return n;
}

void Light::setIaValues(int i, float val)
{
    Ia[i] = val;
}

void Light::setIdValues(int i, float val)
{
    Id[i] = val;
}

void Light::setIsValues(int i, float val)
{
    Is[i] = val;
}

void Light::setIaRGBValues(int i, qreal r, qreal g, qreal b)
{
    IaRGB[i].setX((float)r);
    IaRGB[i].setY((float)g);
    IaRGB[i].setZ((float)b);
    //qDebug() << IaRGB[i];
}

void Light::setIdRGBValues(int i, qreal r, qreal g, qreal b)
{
    IdRGB[i].setX((float)r);
    IdRGB[i].setY((float)g);
    IdRGB[i].setZ((float)b);
}

void Light::setIsRGBValues(int i, qreal r, qreal g, qreal b)
{
    IsRGB[i].setX((float)r);
    IsRGB[i].setY((float)g);
    IsRGB[i].setZ((float)b);
}

void Light::setKaRGBValues(int i, int r, int g, int b)
{
    KaRGB[i].setX(((float)r / 255.0));
    KaRGB[i].setY(((float)g / 255.0));
    KaRGB[i].setZ(((float)b / 255.0));
}

void Light::setKdRGBValues(int i, int r, int g, int b)
{
    KdRGB[i].setX(((float)r / 255.0));
    KdRGB[i].setY(((float)g / 255.0));
    KdRGB[i].setZ(((float)b / 255.0));
}

void Light::setKsRGBValues(int i, int r, int g, int b)
{
    KsRGB[i].setX(((float)r / 255.0));
    KsRGB[i].setY(((float)g / 255.0));
    KsRGB[i].setZ(((float)b / 255.0));
}

void Light::setN(int i, float val)
{
    n[i] = val;
}

void Light::setKa(int i, float val)
{
    Ka[i] = val;
}

void Light::setKd(int i, float val)
{
    Kd[i] = val;
}

void Light::setKs(int i, float val)
{
    Ks[i] = val;
}
