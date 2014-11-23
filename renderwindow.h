#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "openglwindow.h"
#include "tiny_obj_loader.h"
#include "camera.h"
#include "objectmodel.h"
#include "light.h"

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QLabel>

class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;

class RenderWindow : public OpenGLWindow
{
    Q_OBJECT

public:
    RenderWindow();

    void initialize();
    void render();
    void checkError(const QString& prefix);
    void linkShaderPrograms();
    void enableAttr(int vlen);

    void toggleWireFrame(bool on);
    void getFileAndMatrices(QVector<QString> typeNames, QVector<QString> actualFiles, QVector<std::string> objFiles, QVector<QMatrix4x4> transformMatrices);
    void updateModelProperties(int size, QVector<QVector3D> trans, QVector<QVector3D> rot, QVector<QVector3D> scale);
    void setFilePath(std::string p);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    bool perspectiveOn; // toggle between perspective and orthographic projections
    bool wireFrameOn; // toggle between wire frame and solid face rendering

    QVector<ObjectModel> objectmodels;

    void calculateSurfaceNormals(QVector3D v1, QVector3D v2, QVector3D v3);
    void setShader(bool flat, bool gouraud, bool phong);

    QVector4D lightPos[10];
    QVector3D IaRGB[10], IdRGB[10], IsRGB[10];

    Light lighting;
    int totalLights;

    //GLfloat Ia[10], Id[10], Is[10];

    //GLfloat Ka, Ka_r, Ka_g, Ka_b,
    //        Kd, Kd_r, Kd_g, Kd_b,
    //        Ks, Ks_r, Ks_g, Ks_b;
    //GLfloat n;
    void setTotalLights(int i);


private:

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_normAttr;
    GLuint m_matrixUniform;

    GLuint m_modelViewUniform;
    GLuint m_normalMatrixUniform;

    GLuint m_numOfLights;
    GLuint m_lightPosition;
    GLuint m_eyePosition;

    GLuint m_IaUniform;
    GLuint m_IdUniform;
    GLuint m_IsUniform;
    GLuint m_IaRGBUniform;
    GLuint m_IdRGBUniform;
    GLuint m_IsRGBUniform;
    GLuint m_KaUniform;
    GLuint m_KdUniform;
    GLuint m_KsUniform;
    GLuint m_shineUniform;

    QOpenGLShaderProgram *m_program;
    QOpenGLShaderProgram *m_flatShaderProgram;
    QOpenGLShaderProgram *m_gouraudShaderProgram;
    QOpenGLShaderProgram *m_phongShaderProgram;

    QVector<QOpenGLVertexArrayObject*> m_vao;
    QVector<QOpenGLBuffer*> m_vbo;
    QVector<QOpenGLBuffer*> m_ibo;

    int m_frame;
    bool m_useSourceCode;

    QVector<QString> objectNames;
    QVector<std::string> filenames;
    QVector<QString> fnames; // same as filenames, but type is QString
    QVector<QMatrix4x4> matrices;

    std::vector<GLuint> indicesCount;

    // used for storing OBJ data parsed using tinyobj parser
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    Camera camera;
    QPoint lastPos;
    std::string path;

    std::vector<QVector3D> normals;
    bool m_flatShadeOn;
    bool m_gouraudShadeOn;
    bool m_phongShadeOn;

};

class RenderWindowWidget : public QWidget
{
    Q_OBJECT
public:
  RenderWindowWidget(QWidget* parent): QWidget(parent) {

      renWin = new RenderWindow();

      QWidget* widget = QWidget::createWindowContainer(renWin);
      QHBoxLayout* layout = new QHBoxLayout(this);
      layout->addWidget(widget);

  }

  RenderWindow* GetRenderWindow() {
      return renWin;
  }


private:
  RenderWindow* renWin;

};

#endif // RENDERWINDOW_H
