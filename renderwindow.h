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
    void getFileAndMatrices(QVector<QString> typeNames, QVector<std::string> objFiles, QVector<QMatrix4x4> transformMatrices);
    void updateModelProperties(int size);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    bool togglePers;
    Camera camera;
    QPoint lastPos;
    QVector<ObjectModel> objectmodels;

private:

    QVector<QString> types; // stores the types/names of the objects
    QVector<std::string> filenames; // stores the filenames
    QVector<QMatrix4x4> matrices; // stores the transformation matrices

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;

    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLBuffer *m_ibo;

    int m_frame;
    bool m_useSourceCode;

    QOpenGLVertexArrayObject* m_vao2;
    QOpenGLBuffer *m_vbo2;
    QOpenGLBuffer *m_ibo2;

    GLuint indicesCount1;
    GLuint indicesCount2;

    // used for storing OBJ data parsed using tinyobj parser
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

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
