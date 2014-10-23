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
    indicesCount1 = 0, indicesCount2 = 0;
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

    checkError("state initialized");

    /// check for errors to ensure OpenGL
    /// is functioning properly.
    checkError("after program bind");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao2 = new QOpenGLVertexArrayObject(this);
    m_vao2->create();

    m_vbo2 = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vbo2->create();
    m_ibo2 = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_ibo2->create();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

}

void RenderWindow::render()
{
    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    m_program->bind();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao->bind();

    std::string path = "/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/";
    std::string inputfile = path;
    if (!filenames.empty()) {
        tinyobj::LoadObj(shapes, materials, (inputfile.append(filenames[0])).c_str());
    }

    if (!shapes.empty()) {
        int vlen = 0;
        for (size_t i = 0; i < shapes.size(); i++) {
            vlen += shapes[i].mesh.positions.size();
        }

        GLfloat vertices[vlen];
        for (size_t i = 0; i < shapes.size(); i++) {
            for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
                vertices[3*v+0] = shapes[i].mesh.positions[3*v+0];
                vertices[3*v+1] = shapes[i].mesh.positions[3*v+1];
                vertices[3*v+2] = shapes[i].mesh.positions[3*v+2];
            }
        }

        int clen = vlen;
        GLfloat colors[clen];
        std::fill_n(colors, clen, 1.0f);

        int ilen = 0;
        for (size_t i = 0; i < shapes.size(); i++) {
            ilen += shapes[i].mesh.indices.size();
        }

        indicesCount1 = ilen;
        GLuint indices[ilen];
        for (size_t i = 0; i < shapes.size(); i++) {
            for (size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {
                indices[3*v+0] = shapes[i].mesh.indices[3*v+0];
                indices[3*v+1] = shapes[i].mesh.indices[3*v+1];
                indices[3*v+2] = shapes[i].mesh.indices[3*v+2];
            }
        }

        m_vbo->bind();
        m_vbo->allocate((vlen + clen)*sizeof(GLfloat));
        m_vbo->write(0, vertices, vlen * sizeof(GLfloat));
        m_vbo->write(vlen*sizeof(GLfloat), colors, clen * sizeof(GLfloat));

        //std::cout << "first model" << std::endl;
        checkError("after vertex buffer allocation");

        m_ibo->bind();
        m_ibo->allocate(indices, ilen*sizeof(GLuint));

        checkError("after index buffer allocation");

        m_program->enableAttributeArray(m_posAttr);

        /// vertex position start offset is 0, number of value = 3 (x,y,z)
        m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);

        m_program->enableAttributeArray(m_colAttr);

        /// color position start offset is vlen * sizeof(GLFloat), number of values = 3 (r,g,b) (4 if we did rgba)
        m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);

        checkError("after enabling attributes");

        /* *********************************************************************************************** */
        /* *********************************************************************************************** */

        QMatrix4x4 projection = objectmodels[0].getProjection();
        if (togglePers) {
            projection.perspective(60.0, (float)width()/(float)height(), 0.1, 10000);
        }

        else if (!togglePers) {
            projection.ortho(-500.0, 500.0, -500.0, 500.0, 0, 1000);
        }

        QMatrix4x4 model = objectmodels[0].getModel();

        model.translate(objectmodels[0].xTrans, objectmodels[0].yTrans, objectmodels[0].zTrans);
        model.rotate((float)objectmodels[0].xRot/16.0, 1.0, 0.0, 0.0);
        model.rotate((float)objectmodels[0].yRot/16.0, 0.0, 1.0, 0.0);
        model.rotate((float)objectmodels[0].zRot/16.0, 0.0, 0.0, 1.0);
        model.scale((float)objectmodels[0].xScale, (float)objectmodels[0].yScale, (float)objectmodels[0].zScale);

        m_program->setUniformValue(m_matrixUniform, projection * camera.returnView() * model);

        m_vao->bind();
        glDrawElements(GL_TRIANGLES, indicesCount1, GL_UNSIGNED_INT, 0);

        m_vao->release();

    }

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    m_vao2->bind();

    inputfile = path;
    if (!filenames.empty()) {
        tinyobj::LoadObj(shapes, materials, (inputfile.append(filenames[1])).c_str());
    }

    if (!shapes.empty()) {
        int vlen2 = 0;
        for (size_t i = 0; i < shapes.size(); i++) {
            vlen2 += shapes[i].mesh.positions.size();

        }

        GLfloat vertices2[vlen2];
        for (size_t i = 0; i < shapes.size(); i++) {
            for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
                vertices2[3*v+0] = shapes[i].mesh.positions[3*v+0];
                vertices2[3*v+1] = shapes[i].mesh.positions[3*v+1];
                vertices2[3*v+2] = shapes[i].mesh.positions[3*v+2];
                //std::cout << vertices2[obj1_offset + 3*v+0] << " " << vertices2[obj1_offset + 3*v+1] << " " << vertices2[obj1_offset + 3*v+2] << std::endl;
            }
        }

        int clen2 = vlen2;
        GLfloat colors2[clen2];
        std::fill_n(colors2, clen2, 1.0f);

        int ilen2 = 0;
        for (size_t i = 0; i < shapes.size(); i++) {
           ilen2 += shapes[i].mesh.indices.size();
        }

        indicesCount2 = ilen2;

        GLuint indices2[ilen2];
        for (size_t i = 0; i < shapes.size(); i++) {
            for (size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {
                indices2[3*v+0] = shapes[i].mesh.indices[3*v+0];
                indices2[3*v+1] = shapes[i].mesh.indices[3*v+1];
                indices2[3*v+2] = shapes[i].mesh.indices[3*v+2];
            }
        }

        m_vbo2->bind();
        m_vbo2->allocate((vlen2 + clen2)*sizeof(GLfloat));
        m_vbo2->write(0, vertices2, vlen2 * sizeof(GLfloat));
        m_vbo2->write(vlen2*sizeof(GLfloat), colors2, clen2 * sizeof(GLfloat));

        //std::cout << "second model" << std::endl;
        checkError("after vertex buffer allocation");

        m_ibo2->bind();
        m_ibo2->allocate(indices2, ilen2*sizeof(GLuint));

        checkError("after index buffer allocation");

        m_program->enableAttributeArray(m_posAttr);

        /// vertex position start offset is 0, number of value = 3 (x,y,z)
        m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);

        m_program->enableAttributeArray(m_colAttr);

        /// color position start offset is vlen * sizeof(GLFloat), number of values = 3 (r,g,b) (4 if we did rgba)
        m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen2 * sizeof(GLfloat), 3);

        checkError("after enabling attributes");

        /* *********************************************************************************************** */
        /* *********************************************************************************************** */

        QMatrix4x4 projection = objectmodels[1].getProjection();
        if (togglePers) {
            projection.perspective(60.0, (float)width()/(float)height(), 0.1, 10000);
        }

        else if (!togglePers) {
            projection.ortho(-500.0, 500.0, -500.0, 500.0, 0, 1000);
        }

        QMatrix4x4 model = objectmodels[1].getModel();

        model.translate(objectmodels[1].xTrans, objectmodels[1].yTrans, objectmodels[1].zTrans);
        model.rotate((float)objectmodels[1].xRot/16.0, 1.0, 0.0, 0.0);
        model.rotate((float)objectmodels[1].yRot/16.0, 0.0, 1.0, 0.0);
        model.rotate((float)objectmodels[1].zRot/16.0, 0.0, 0.0, 1.0);
        model.scale((float)objectmodels[1].xScale, (float)objectmodels[1].yScale, (float)objectmodels[1].zScale);

        m_program->setUniformValue(m_matrixUniform, projection * camera.returnView() * model);

        m_vao2->bind();
        glDrawElements(GL_TRIANGLES, indicesCount2, GL_UNSIGNED_INT, 0);

        m_vao2->release();
    }

    /* *********************************************************************************************** */
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

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void RenderWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void RenderWindow::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    int xAngle = dx*8;
    int yAngle = dy*8;

    if (event->buttons() & Qt::LeftButton) {
        camera.camTranslate(dx, QVector3D(1, 0, 0));
        camera.camTranslate(dy, QVector3D(0, 1, 0));
    } else if (event->buttons() & Qt::RightButton) {
        qNormalizeAngle(xAngle);
        qNormalizeAngle(yAngle);

        camera.camRotate((float)xAngle/16.0, QVector3D(1, 0, 0));
        camera.camRotate((float)yAngle/16.0, QVector3D(0, 1, 0));
    }

    lastPos = event->pos();

}

void RenderWindow::wheelEvent(QWheelEvent *event)
{
    int steps = 0;
    if (event != NULL) {
        steps++;
        QPoint z = event->angleDelta();
        if (z.y() == -120) {
            camera.camZoom((float)steps*2.0);
        }
        else {
            camera.camZoom((float)steps*-2.0);
        }
    }
}

void RenderWindow::getFileAndMatrices(QVector<QString> typeNames, QVector<std::string> objFiles, QVector<QMatrix4x4> transformMatrices)
{

    for (int i=0; i<typeNames.size(); i++) {
        types.push_back(typeNames[i]);
        qDebug() << types[i];
    }

    for (int i=0; i<objFiles.size(); i++) {
        filenames.push_back(objFiles[i]);
        std::cout << filenames[i] << std::endl;
    }

    for (int i=0; i<transformMatrices.size(); i++) {
        matrices.push_back(transformMatrices[i]);
    }

}

void RenderWindow::updateModelProperties(int size)
{
    objectmodels.resize(size);

    ObjectModel model;

    for (int i = 0; i < size; i++) {
        model.setNameAndIndex(types[i], i);
        objectmodels.insert(i, model);
    }

    for (int i = 0; i < size; i++) {
        objectmodels[i].setPropertiesValues(0, 0, 0, 0, 0, 0, 30, 45, 45);
        objectmodels[i].setModel(matrices[i]);
    }
}
