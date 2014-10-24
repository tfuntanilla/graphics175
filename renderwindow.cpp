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
    setAnimating(false);
    //indicesCount1 = 0, indicesCount2 = 0;
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

    m_vao.push_back(new QOpenGLVertexArrayObject(this));
    m_vao[0]->create();

    m_vbo.push_back(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    m_vbo[0]->create();
    m_ibo.push_back(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
    m_ibo[0]->create();

    checkError("state initialized");

    /// check for errors to ensure OpenGL
    /// is functioning properly.
    checkError("after program bind");

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */




}

void RenderWindow::render()
{

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // allocate space for additional vertex array objects as necessary
    for (int i = 1; (i < filenames.size() && m_vao.size() != filenames.size()); i++) {
        m_vao.push_back(new QOpenGLVertexArrayObject(this));
        m_vao[i]->create();

        m_vbo.push_back(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
        m_vbo[i]->create();
        m_ibo.push_back(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer));
        m_ibo[i]->create();

        checkError("state initialized");

        /// check for errors to ensure OpenGL
        /// is functioning properly.
        checkError("after program bind");
    }

    m_program->bind();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    // begin reading the file and storing the vertices, colors, indices, etc.

    for (int i = 0; i < filenames.size(); i++) {
        m_vao[i]->bind();

        std::string fp = path;
        if (!filenames.empty()) {
            //std::cout << "From loader: " << path << std::endl;
            tinyobj::LoadObj(shapes, materials, (fp.append(filenames[i])).c_str());
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
            std::fill_n(colors, clen, 0.0f);
            for (int i = 0; i < clen; i+=9) {
               colors[i] = 1.0f;
               if ((i+4) <= clen) {
                    colors[i+4] = 1.0f;
               }
               if ((i+4) <= clen) {
                    colors[i+8] = 1.0f;
                }
            }

            int ilen = 0;
            for (size_t i = 0; i < shapes.size(); i++) {
                ilen += shapes[i].mesh.indices.size();
            }

            //indicesCount = ilen;
            indicesCount.push_back(ilen);
            GLuint indices[ilen];
            for (size_t i = 0; i < shapes.size(); i++) {
                for (size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {
                    indices[3*v+0] = shapes[i].mesh.indices[3*v+0];
                    indices[3*v+1] = shapes[i].mesh.indices[3*v+1];
                    indices[3*v+2] = shapes[i].mesh.indices[3*v+2];
                }
            }

            m_vbo[i]->bind();
            m_vbo[i]->allocate((vlen + clen)*sizeof(GLfloat));
            m_vbo[i]->write(0, vertices, vlen * sizeof(GLfloat));
            m_vbo[i]->write(vlen*sizeof(GLfloat), colors, clen * sizeof(GLfloat));

            checkError("after vertex buffer allocation");

            m_ibo[i]->bind();
            m_ibo[i]->allocate(indices, ilen*sizeof(GLuint));

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

            // set up transformation matrices

            QMatrix4x4 projection = objectmodels[i].getProjection();
            if (togglePers) {
                projection.perspective(60.0, (float)width()/(float)height(), 0.1, 5000);

            }
            else if (!togglePers) {
                projection.ortho(-(float)width()/2, (float)width()/2, -(float)height()/2, (float)height()/2, 0.0, 1000.0);
            }

            QMatrix4x4 model = objectmodels[i].getModel();
            model.translate(objectmodels[i].xTrans, objectmodels[i].yTrans, objectmodels[i].zTrans);
            model.rotate(objectmodels[i].xRot/16.0, 1.0, 0.0, 0.0);
            model.rotate(objectmodels[i].yRot/16.0, 0.0, 1.0, 0.0);
            model.rotate(objectmodels[i].zRot/16.0, 0.0, 0.0, 1.0);
            model.scale(objectmodels[i].xScale, objectmodels[i].yScale, objectmodels[i].zScale);

            QMatrix4x4 view = camera.returnView();

            m_program->setUniformValue(m_matrixUniform, projection * view * model);

            m_vao[i]->bind();
            glDrawElements(GL_TRIANGLES, indicesCount[i], GL_UNSIGNED_INT, 0);

            m_vao[i]->release();

        }
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

    renderLater();
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
        camera.camTranslate(-dx, QVector3D(1, 0, 0));
        camera.camTranslate(dy, QVector3D(0, 1, 0));
    } else if (event->buttons() & Qt::RightButton) {
        qNormalizeAngle(xAngle);
        qNormalizeAngle(yAngle);

        camera.camRotate((float)xAngle/16.0, QVector3D(1, 0, 0));
        camera.camRotate((float)yAngle/16.0, QVector3D(0, 1, 0));
    }

    lastPos = event->pos();

    renderLater();

}

void RenderWindow::wheelEvent(QWheelEvent *event)
{
    int steps = 0;
    if (event != NULL) {
        steps++;
        QPoint z = event->angleDelta();
        if (z.y() == -120) {
            camera.camZoom((float)steps*-3.0);
        }
        else {
            camera.camZoom((float)steps*3.0);
        }
    }

    renderLater();
}

void RenderWindow::getFileAndMatrices(QVector<QString> typeNames, QVector<QString> actualFiles, QVector<std::string> objFiles, QVector<QMatrix4x4> transformMatrices)
{

    for (int i=0; i<typeNames.size(); i++) {
        objectNames.push_back(typeNames[i]);
    }

    for (int i=0; i<objFiles.size(); i++) {
        filenames.push_back(objFiles[i]);
    }

    for (int i=0; i<transformMatrices.size(); i++) {
        matrices.push_back(transformMatrices[i]);
    }

    for (int i=0; i<actualFiles.size(); i++) {
        fnames.push_back(actualFiles[i]);
    }

}

void RenderWindow::updateModelProperties(int size, QVector<QVector3D> trans, QVector<QVector3D> rot, QVector<QVector3D> scale)
{
    objectmodels.resize(size);

    for (int i = 0; i < size; i++) {
        objectmodels[i].setNameAndIndex(objectNames[i], fnames[i], i);
    }

    for (int i = 0; i < size; i++) {
        objectmodels[i].setPropertiesValues(trans[i].x(), trans[i].y(), trans[i].z(),
                                            rot[i].x(), rot[i].y(), rot[i].z(),
                                            scale[i].x(), scale[i].y(),scale[i].z());

        objectmodels[i].setModel(matrices[i]);
    }
}

void RenderWindow::setFilePath(std::string p)
{
    //std::cout << "From render window setFilePath: " << p << std::endl;
    path.append(p);
    //std::cout << "After appending: " << path << std::endl;
}
