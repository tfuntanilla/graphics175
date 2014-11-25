#include "light.h"

#include <QDebug>

Light::Light()
{
    Ia = 1.0;
    IaRGB.setX(1.0); IaRGB.setY(1.0); IaRGB.setZ(1.0);
    for (int i = 0; i < 10; i++) {

        // initialize to point light source
        lightPos[i].setX(0.0); lightPos[i].setY(0.0); lightPos[i].setZ(0.0); lightPos[i].setW(1.0);

        // initialize intensity factors
        Id[i] = 0.0; Is[i] = 0.0;

        // initialize color components of ambient, diffuse, and specular illumination
        // X is the red component, Y is green, and Z is blue
        IaRGB.setX(1.0); IaRGB.setY(1.0); IaRGB.setZ(1.0);
        IdRGB[i].setX(1.0); IdRGB[i].setY(1.0); IdRGB[i].setZ(1.0);
        IsRGB[i].setX(1.0); IsRGB[i].setY(1.0); IsRGB[i].setZ(1.0);

        attenuationFactors[i].setX(1.0);
        attenuationFactors[i].setY(1.0);
        attenuationFactors[i].setZ(1.0);
        lightDistance[i] = 0.0;

    }

}

QVector4D Light::getLightPositions(int i)
{
    return QVector4D(lightPos[i].x(), lightPos[i].y(), lightPos[i].z(), lightPos[i].w());
}

QString Light::getLightSource(int i)
{
    if (lightPos[i].w() == 0.0) {
        return "Directional";
    }
    else {
        return "Point";
    }
}

QVector3D Light::getIaRGB()
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

QVector3D Light::getIdRGB(int i)
{
    return IdRGB[i];
}

QVector3D Light::getIsRGB(int i)
{
    return IsRGB[i];
}

GLfloat Light::getIa()
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

float Light::getId(int i)
{
    return Id[i];
}

float Light::getIs(int i)
{
    return Is[i];
}

QVector3D Light::getAttenuationFactors(int i)
{
    return attenuationFactors[i];
}

float Light::getLightDistance(int i)
{
    return lightDistance[i];
}

QVector3D *Light::getAttenuationFactors()
{
    return attenuationFactors;
}

GLfloat *Light::getLightDistance()
{
    return lightDistance;
}
/*
float *Light::getn()
{
    return n;
}
*/
void Light::setIaValue(float val)
{
    Ia = val;
}

void Light::setIdValues(int i, float val)
{
    Id[i] = val;
}

void Light::setIsValues(int i, float val)
{
    Is[i] = val;
}

void Light::setIaRGBValues(qreal r, qreal g, qreal b)
{
    IaRGB.setX((float)r);
    IaRGB.setY((float)g);
    IaRGB.setZ((float)b);
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

void Light::setQuadAtten(int i, float val)
{
    attenuationFactors[i].setZ(val);
}

void Light::setLinearAtten(int i, float val)
{
    attenuationFactors[i].setY(val);
}

void Light::setConstantAtten(int i, float val)
{
    attenuationFactors[i].setX(val);
}


void Light::setLightDistance(int i, float val)
{
    lightDistance[i] = val;
}
