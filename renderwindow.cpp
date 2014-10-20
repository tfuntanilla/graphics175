#include "renderwindow.h"

#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QByteArray>
#include <QJsonObject>


#include <cstdlib>
#include <iostream>

static const char *vertexShaderSource =
    "#version 330\n"
    "uniform mat4 mvp;\n"
    "in vec4 posAttr;\n"
    "in vec4 colAttr;\n"
    "out vec4 col;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = mvp * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "#version 330\n"
    "in vec4 col;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "   fragColor = col;\n"
    "}\n";


RenderWindow::RenderWindow()
    : OpenGLWindow()
    , m_program(0)
    , m_frame(0)
    , m_useSourceCode(true)
{
    setAnimating(true);
    indicesCountChair = 0, indicesCountDesk = 0;
    angle = 0;
    xRot = 0, xTrans = 0, xScale = 0;
    yRot = 1, yTrans = 0, yScale = 0;
    zRot = 0, zTrans = -5, zScale = 0;

    togglePers = false;
}

void RenderWindow::checkError(const QString &prefix)
{
    /// if OpenGL Logging is enabled or active
    /// then use that instead.

    if(isOpenGLLogging()) {
        return;
    }

    GLenum glErr = glGetError();

    while(glErr != GL_NO_ERROR) {
        QString error;
        switch (glErr)
        {
        case GL_NO_ERROR:               error="NO_ERROR";               break;
        case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
        case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
        case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
        case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        if(error != "NO_ERROR") {
            qDebug() << prefix << ":" << error;
        }
        glErr = glGetError();
    }
}

void RenderWindow::initialize()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    m_program = new QOpenGLShaderProgram(this);

    if(m_useSourceCode) {
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    } else {
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
    }
    m_program->link();

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("mvp");

    m_vao = new QOpenGLVertexArrayObject(this);
    m_vao->create();

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo->create();
    m_ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo->create();
    
    m_program->bind();

    checkError("state initialized");

    /// check for errors to ensure OpenGL
    /// is functioning properly.
    checkError("after program bind");

    m_vao->bind();
    m_vao->release();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao2 = new QOpenGLVertexArrayObject(this);
    m_vao2->create();

    m_vbo2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo2->create();
    m_ibo2 = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo2->create();

    m_vao2->bind();
    m_vao2->release();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_program->release();
}

void RenderWindow::render()
{

    /*
    SceneHandler scene;
    QVector<Scene*> scenes;

    scene.scenedemoRead("/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/scene.json", scenes);

    QJsonObject object;

    object["name"] = scenes[0]->name;
    object["description"] = scenes[0]->description;

    scene.parseModel(object);
    */



    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    m_program->bind();


    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    /* Load obj files */
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string inputfile = "/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/chair.obj";
    tinyobj::LoadObj(shapes, materials, inputfile.c_str());

    std::vector<tinyobj::shape_t> shapes2;
    std::vector<tinyobj::material_t> materials2;
    std::string inputfile2 = "/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/table.obj";
    tinyobj::LoadObj(shapes2, materials2, inputfile2.c_str());

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    /* Set aside space for vertices of the chairs */

    int vlen = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        vlen += shapes[i].mesh.positions.size();
    }

    int vlen2 = 0;
    for (size_t i = 0; i < shapes2.size(); i++) {
        vlen2 += shapes2[i].mesh.positions.size();

    }

    /* Debugging vertices */
    /*

    std::cout << "Vertices: " << std::endl;

    for (size_t i = 0; i < shapes2.size(); i++) {
        for (size_t v = 0; v < shapes2[i].mesh.positions.size() / 3; v++) {
          printf("  v[%ld] = (%f, %f, %f)\n", v,
            shapes2[i].mesh.positions[3*v+0],
            shapes2[i].mesh.positions[3*v+1],
            shapes2[i].mesh.positions[3*v+2]);
        }
    }

    std::cout << "Total no. of vertices: " << vlen << std::endl;

    */

    /* First chair vertices */
    GLfloat vertices[vlen];
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
            vertices[3*v+0] = shapes[i].mesh.positions[3*v+0];
            vertices[3*v+1] = shapes[i].mesh.positions[3*v+1];
            vertices[3*v+2] = shapes[i].mesh.positions[3*v+2];
        }
    }

    GLfloat vertices2[vlen2];
    for (size_t i = 0; i < shapes2.size(); i++) {
        for (size_t v = 0; v < shapes2[i].mesh.positions.size() / 3; v++) {
            vertices2[3*v+0] = shapes2[i].mesh.positions[3*v+0];
            vertices2[3*v+1] = shapes2[i].mesh.positions[3*v+1];
            vertices2[3*v+2] = shapes2[i].mesh.positions[3*v+2];
            //std::cout << vertices2[obj1_offset + 3*v+0] << " " << vertices2[obj1_offset + 3*v+1] << " " << vertices2[obj1_offset + 3*v+2] << std::endl;
        }
    }


    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    int clen = vlen;
    GLfloat colors[clen];
    std::fill_n(colors, clen, 1.0f);


    int clen2 = vlen2;
    GLfloat colors2[clen2];
    std::fill_n(colors2, clen2, 1.0f);

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */


    /* Set aside space for indices of the chairs */

    int ilen = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        ilen += shapes[i].mesh.indices.size();
    }

    int ilen2 = 0;
    for (size_t i = 0; i < shapes2.size(); i++) {
       ilen2 += shapes2[i].mesh.indices.size();
    }


    /* Debugging indices */

    /*
    std::cout << "Total no. of indices: " << ilen << std::endl;

    std::cout << "Total no. of indices for each shape: " << std::endl;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        std::cout << "shapes[" << i << "]: " << shapes[i].mesh.indices.size() << std::endl;
    }

    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
            printf("  idx[%ld] = %d, %d, %d. mat_id = %d\n", f, shapes[i].mesh.indices[3*f+0], shapes[i].mesh.indices[3*f+1], shapes[i].mesh.indices[3*f+2], shapes[i].mesh.material_ids[f]);
        }
    }
    */


    /* First chair indices */
    indicesCountChair = ilen;
    indicesCountDesk = ilen2;

    GLuint indices[ilen];
    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {
            indices[3*v+0] = shapes[i].mesh.indices[3*v+0];
            indices[3*v+1] = shapes[i].mesh.indices[3*v+1];
            indices[3*v+2] = shapes[i].mesh.indices[3*v+2];
        }
    }

    GLuint indices2[ilen2];
    for (size_t i = 0; i < shapes2.size(); i++) {
        for (size_t v = 0; v < shapes2[i].mesh.indices.size() / 3; v++) {
            indices2[3*v+0] = shapes2[i].mesh.indices[3*v+0];
            indices2[3*v+1] = shapes2[i].mesh.indices[3*v+1];
            indices2[3*v+2] = shapes2[i].mesh.indices[3*v+2];
        }
    }

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao->bind();

    m_vbo->bind();
    m_vbo->allocate((vlen + clen)*sizeof(GLfloat));
    m_vbo->write(0, vertices, vlen * sizeof(GLfloat));

    m_vbo->write(vlen*sizeof(GLfloat), colors, clen * sizeof(GLfloat));

    checkError("after vertex buffer allocation");

    m_ibo->bind();
    m_ibo->allocate(indices, ilen*sizeof(GLuint));

    checkError("after index buffer allocation");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_program->enableAttributeArray(m_posAttr);

    /// vertex position start offset is 0, number of value = 3 (x,y,z)
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);

    m_program->enableAttributeArray(m_colAttr);

    /// color position start offset is vlen * sizeof(GLFloat), number of values = 3 (r,g,b) (4 if we did rgba)
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);

    checkError("after enabling attributes");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    /// set up projection
    QMatrix4x4 projection_chair1;
    projection_chair1.setToIdentity(); /// set

    if (togglePers) {
        projection_chair1.perspective(60, (float)width()/(float)height(), 0.1, 10000);
    }

    else if (!togglePers) {
        projection_chair1.ortho(1.0, -1.0, 1.0, -1.0, 0.1, 5.0);
    }

    /// set up view
    QMatrix4x4 view_chair1;
    view_chair1.setToIdentity(); /// set

    QVector3D eye_chair1(0, 0, 1);
    QVector3D center_chair1(0,0,0);
    QVector3D up_chair1(0,1,0);

    view_chair1.lookAt(eye_chair1, center_chair1, up_chair1);

    /// set up matrix
    QMatrix4x4 model_chair1;
    model_chair1.setToIdentity(); /// set

    model_chair1.translate(xTrans, yTrans, zTrans); /// place it a certain distance from camera
    model_chair1.rotate((float)angle, (float)xRot, (float)yRot, (float)zRot);
    model_chair1.scale((float)xScale, (float)yScale, (float)zScale);

    m_program->setUniformValue(m_matrixUniform, projection_chair1 * view_chair1 * model_chair1);

    m_vao->bind();
    glDrawElements(GL_TRIANGLES, indicesCountChair, GL_UNSIGNED_INT, 0);

    m_vao->release();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao2->bind();

    m_vbo2->bind();
    m_vbo2->allocate((vlen2 + clen2)*sizeof(GLfloat));
    m_vbo2->write(0, vertices2, vlen2 * sizeof(GLfloat));

    m_vbo2->write(vlen2*sizeof(GLfloat), colors2, clen2 * sizeof(GLfloat));

    checkError("after vertex buffer allocation");

    m_ibo2->bind();
    m_ibo2->allocate(indices2, ilen2*sizeof(GLuint));

    checkError("after index buffer allocation");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_program->enableAttributeArray(m_posAttr);

    /// vertex position start offset is 0, number of value = 3 (x,y,z)
    m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);

    m_program->enableAttributeArray(m_colAttr);

    /// color position start offset is vlen * sizeof(GLFloat), number of values = 3 (r,g,b) (4 if we did rgba)
    m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen2 * sizeof(GLfloat), 3);

    checkError("after enabling attributes");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    /// set up projection
    QMatrix4x4 projection_desk1;
    projection_desk1.setToIdentity(); /// set

    if (togglePers) {
        projection_desk1.perspective(60, (float)width()/(float)height(), 0.1, 10000);
    }

    else if (!togglePers) {
        projection_desk1.ortho(1.0, -1.0, 1.0, -1.0, 0.1, 5.0);
    }

    /// set up view
    QMatrix4x4 view_desk1;
    view_desk1.setToIdentity(); /// set

    QVector3D eye_desk1(0, 0, 1);
    QVector3D center_desk1(0,0,0);
    QVector3D up_desk1(0,1,0);

    view_desk1.lookAt(eye_desk1, center_desk1, up_desk1);

    /// set up matrix
    QMatrix4x4 model_desk1;
    model_desk1.setToIdentity(); /// set

    model_desk1.translate(xTrans+10, yTrans+10, zTrans-10); /// place it a certain distance from camera
    model_desk1.rotate((float)angle+25.0, (float)xRot, (float)yRot, (float)zRot);
    model_desk1.scale((float)xScale, (float)yScale, (float)zScale);

    m_program->setUniformValue(m_matrixUniform, projection_desk1 * view_desk1 * model_desk1);

    m_vao2->bind();
    glDrawElements(GL_TRIANGLES, indicesCountDesk, GL_UNSIGNED_INT, 0);

    m_vao2->release();

    /* *********************************************************************************************** */

    
    m_program->release();

    checkError("after program release");

    if(isAnimating()) {
        ++m_frame;
    }
}

void RenderWindow::toggleWireFrame(bool c)
{
    if (c) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}


void RenderWindowWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void RenderWindowWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void RenderWindowWidget::mouseReleaseEvent(QMouseEvent *event)
{

}

void RenderWindowWidget::wheelEvent(QWheelEvent *event)
{
    lastPos = event->angleDelta();
    emit zChanged(lastPos.x());
}

void RenderWindowWidget::zoom(int value)
{
    renWin->zTrans += value;
    renWin->render();
}
