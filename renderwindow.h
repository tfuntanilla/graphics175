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
#include <QKeyEvent>

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

    int xRot, xTrans, xScale;
    int yRot, yTrans, yScale;
    int zRot, zTrans, zScale;

    bool togglePers;
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

    QPoint lastPos;

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
public slots:
  void setXRotation(int value);
  void setYRotation(int value);
  void setXTranslation(int value);
  void setYTranslation(int value);
  void setZTranslation(int value);

signals:
  void xRotationChanged(int value);
  void yRotationChanged(int value);
  void xTranslationChanged(int value);
  void yTranslationChanged(int value);
  void zTranslationChanged(int value);
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
