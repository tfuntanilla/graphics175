/* ****************************************************
 * Camera Class for 3D Viewing
 *****************************************************/

#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera
{
public:
    Camera();
    ~Camera();
    
    void camTranslate(float dist, QVector3D trans);
    void camRotate(float amount, QVector3D rot);
    void camZoom(float amount);
    //void setCenter(QVector3D vector);
    //void setEye(QVector3D vector);
    
    QMatrix4x4 returnView();
   // QVector3D getEyeVec();

private:
    QMatrix4x4 rotationMatrix;
    QVector3D eye;
    QVector3D center;
    QVector3D up;
};

#endif
