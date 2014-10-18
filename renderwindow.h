#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "openglwindow.h"
#include "tiny_obj_loader.h"

#include <QWidget>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>

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

    int angle;
    int xRot, xTrans, xScale;
    int yRot, yTrans, yScale;
    int zRot, zTrans, zScale;

    QPoint lastPos;


private:

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLBuffer *m_ibo;
    int m_frame;
    bool m_useSourceCode;

    GLuint indicesCount;

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

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
  RenderWindow* renWin;

};

#endif // RENDERWINDOW_H
