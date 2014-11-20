#ifndef LIGHT_H
#define LIGHT_H

#include <QOpenGLFunctions>

class Light
{
private:

    GLfloat lightPosX, lightPosY, lightPosZ, lightPosW;

    GLfloat Ia, Ia_r, Ia_g, Ia_b,
            Id, Id_r, Id_g, Id_b,
            Is, Is_r, Is_g, Is_b;
    GLfloat Ka, Ka_r, Ka_g, Ka_b,
            Kd, Kd_r, Kd_g, Kd_b,
            Ks, Ks_r, Ks_g, Ks_b;
    GLfloat n;

public:
    Light();
};

#endif // LIGHT_H
