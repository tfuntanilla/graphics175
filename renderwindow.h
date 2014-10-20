#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include "openglwindow.h"
#include "tiny_obj_loader.h"
#include "scenehandler.h"

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
    void toggleWireFrame(bool c);
    void checkError(const QString& prefix);

    int angle;
    int xRot, xTrans, xScale;
    int yRot, yTrans, yScale;
    int zRot, zTrans, zScale;

    bool togglePers;

private:

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    //GLuint m_pos2Attr;
    //GLuint m_col2Attr;

    QOpenGLShaderProgram *m_program;

    QOpenGLVertexArrayObject* m_vao;
    QOpenGLBuffer *m_vbo;
    QOpenGLBuffer *m_ibo;

    int m_frame;
    bool m_useSourceCode;

    QOpenGLVertexArrayObject* m_vao2;
    QOpenGLBuffer *m_vbo2;
    QOpenGLBuffer *m_ibo2;

    GLuint indicesCountChair;
    GLuint indicesCountDesk;

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

  void mousePressEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);

public slots:
  void zoom(int value);

signals:
  void zChanged(int value);

private:
  RenderWindow* renWin;
  QPoint lastPos;

};

#endif // RENDERWINDOW_H
