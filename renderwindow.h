#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "openglwindow.h"
#include "tiny_obj_loader.h"
#include "camera.h"
#include "objectmodel.h"

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

    void toggleWireFrame(bool c);
    void getFileAndMatrices(QVector<QString> typeNames, QVector<QString> actualFiles, QVector<std::string> objFiles, QVector<QMatrix4x4> transformMatrices);
    void updateModelProperties(int size, QVector<QVector3D> trans, QVector<QVector3D> rot, QVector<QVector3D> scale);
    void setFilePath(std::string p);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    bool togglePers;
    Camera camera;
    QPoint lastPos;
    QVector<ObjectModel> objectmodels;
    std::string path;

    std::vector<GLfloat> canvas;
    void softwareRender();
    void clipOnW(std::vector<QVector4D> inVertices, std::vector<QVector4D> &outputVertices);
    void clipOnAxis(int axis, std::vector<QVector4D> inVertices, std::vector<QVector4D> &outputVertices);

private:

    QVector<QString> objectNames;
    QVector<std::string> filenames;
    QVector<QString> fnames; // same as filenames, but type is QString
    QVector<QMatrix4x4> matrices;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;

    QVector<QOpenGLVertexArrayObject*> m_vao;
    QVector<QOpenGLBuffer*> m_vbo;
    QVector<QOpenGLBuffer*> m_ibo;

    int m_frame;
    bool m_useSourceCode;

    QVector<GLuint> indicesCount;
    QVector<QMatrix4x4> mvp;

    // used for storing OBJ data parsed using tinyobj parser
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::vector<tinyobj::shape_t> m_shapes;

    QLabel softRenWin;


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
