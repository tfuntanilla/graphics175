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
#include <algorithm>

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
            mvp.push_back(projection * view * model);

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

void RenderWindow::softwareRender()
{
    //vertex shader
    // store position, color, and indices in a software buffer

    std::vector<QVector2D> pixelVals; // pixel values to draw/color
    for (int a = 0; a < filenames.size(); a++) {
        std::string fp = path;
        if (!filenames.empty()) {
            tinyobj::LoadObj(shapes, materials, (fp.append(filenames[a])).c_str());
        }

        std::vector<QVector4D> posVecTrans;
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

            GLuint indices[ilen];
            for (size_t i = 0; i < shapes.size(); i++) {
                for (size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {
                    indices[3*v+0] = shapes[i].mesh.indices[3*v+0];
                    indices[3*v+1] = shapes[i].mesh.indices[3*v+1];
                    indices[3*v+2] = shapes[i].mesh.indices[3*v+2];
                }
            }

            /*
        int vlen = 9;
        GLfloat vertices[] = {
             0.0f, 0.707f, 0.0f,
            -0.5f, -0.5f,  0.0f,
             0.5f, -0.5f,  0.0f
        }; /// total 9 elements.

        int clen = 9;
        GLfloat colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        int ilen = 3;
        GLuint indices[] = {
            0, 1, 2
        };

        for (size_t v = 0; v < vlen / 3; v++) {
            QVector4D posVec(vertices[3*v+0], vertices[3*v+1], vertices[3*v+2], 1);

            QMatrix4x4 projection;
            projection.setToIdentity(); /// set
            projection.perspective(60, (float)width()/(float)height(), 0.1, 10000);

            /// set up view
            QMatrix4x4 view;
            view.setToIdentity(); /// set

            QVector3D eye(0, 0, 1);
            QVector3D center(0,0,0);
            QVector3D up(0,1,0);

            view.lookAt(eye, center, up);

            /// set up matrix
            QMatrix4x4 model;
            model.setToIdentity(); /// set
            model.translate(0, 0, -2); /// place it a certain distance from camera

            posVecTrans.push_back(projection * view * model * posVec);

        }
        */

            for (size_t i = 0; i < shapes.size(); i++) {
                for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
                    QVector4D posVec(vertices[3*v+0], vertices[3*v+1], vertices[3*v+2], 1);
                    posVecTrans.push_back(mvp[a] * posVec);
                }
            }

            //clipping
            std::vector<QVector4D> outPosVecTrans;
            clipOnW(posVecTrans, outPosVecTrans);
            clipOnAxis(0, posVecTrans, outPosVecTrans);
            clipOnAxis(1, posVecTrans, outPosVecTrans);
            clipOnAxis(2, posVecTrans, outPosVecTrans);

            //perspective divide
            std::vector<QVector4D> persDiv;
            for (unsigned int i = 0; i < outPosVecTrans.size(); ++i) {
                persDiv.push_back(outPosVecTrans[i] / outPosVecTrans[i].w());
            }

            // convert to screen coordinates
            for (unsigned int i = 0; i < persDiv.size(); ++i) {
                int x = (persDiv[i].x() + 1.f) / 2.f * width();
                int y = (persDiv[i].y() + 1.f) / 2.f * height();
                persDiv[i].setX((float)x);
                persDiv[i].setY((float)y);
            }

            //rasterization
            //Barycentric algorithm

            for (int i = 0; i < ilen / 3; ++i) {

                // get triangle vertices to render
                QVector4D v1 = persDiv[indices[3*i+0]];
                QVector4D v2 = persDiv[indices[3*i+1]];
                QVector4D v3 = persDiv[indices[3*i+2]];

                // determine rectangular bounds for pixel selection
                int maxX = std::max(v1.x(), std::max(v2.x(), v3.x()));
                int minX = std::min(v1.x(), std::min(v2.x(), v3.x()));
                int maxY = std::max(v1.y(), std::max(v2.y(), v3.y()));
                int minY = std::min(v1.y(), std::min(v2.y(), v3.y()));

                // determine spanning edges of triangles
                QVector2D vs1(v2.x() - v1.x(), v2.y() - v1.y());
                QVector2D vs2(v3.x() - v1.x(), v3.y() - v1.y());

                // gather pixels to render
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        QVector2D q(x - v1.x(), y - v1.y());

                        float alpha = (float)(q.x()*vs2.y() - q.y()*vs2.x()) / (float)(vs1.x()*vs2.y() - vs1.y()*vs2.x());
                        float beta = (float)(vs1.x()*q.y() - vs1.y()*q.x()) / (float)(vs1.x()*vs2.y() - vs1.y() * vs2.x());

                        if ( (alpha >= 0) && (beta >= 0) && (alpha + beta <= 1)) {
                            pixelVals.push_back(QVector2D(x, y));
                        }
                    }
                }

            }

            //fragment shader
            canvas.resize(width() * height());
            for (unsigned int i = 0; i < canvas.size(); i++) {
                canvas[i] = 0.0f;
            }

            for (unsigned int i = 0; i < pixelVals.size(); ++i) {
                int x = pixelVals[i].x();
                int y = pixelVals[i].y();
                canvas[width() * y + x] = 1.f;
            }

        }
    }

    // display image
    QImage image(width(), height(), QImage::Format_RGB32);

    for (int x = 0; x < width(); ++x) {
        for (int y = 0; y < height(); ++y) {
            if (width() * y + x < canvas.size()) {
                QRgb rgb = qRgb(255 * canvas[(width() * y + x) + 0],
                        255 * canvas[(width() * y + x) + 1],
                        255 * canvas[(width() * y + x) + 2]);
                image.setPixel(x, image.height() - y - 1, rgb);
            }
        }
    }

    softRenWin.resize(width(), height());
    softRenWin.setPixmap(QPixmap::fromImage(image.scaled(width(), height())));

    softRenWin.show();
}

void RenderWindow::clipOnW(std::vector<QVector4D> inVertices, std::vector<QVector4D>& outputVertices)
{
    float W_CLIPPING_PLANE = 0.00001;
    QVector4D currVertice;
    QVector4D prevVertice;
    //qDebug() << inVertices[0].x() << inVertices[0].y() << inVertices[0].z() << inVertices[0].w();

    prevVertice = inVertices[inVertices.size() - 1];

    float prevDot = (prevVertice.w() < W_CLIPPING_PLANE) ? -1 : 1;
    float currDot;

    float intersectionFactor;
    QVector4D intersectionPoint;

    for (size_t i = 0; i < inVertices.size(); i++) {
        currVertice = inVertices[i];
        currDot = (currVertice.w() < W_CLIPPING_PLANE) ? -1 : 1;

        if (prevDot * currDot < 0) {
            intersectionFactor = (W_CLIPPING_PLANE - prevVertice.w() ) / (prevVertice.w() - currVertice.w());
            intersectionPoint = currVertice;
            intersectionPoint -= prevVertice;
            intersectionPoint *= intersectionFactor;
            intersectionPoint += prevVertice;

            outputVertices.push_back(intersectionPoint);
        }
        if (currDot > 0) {
            outputVertices.push_back(currVertice);
        }

        prevDot = currDot;
        prevVertice = currVertice;
    }
}

void RenderWindow::clipOnAxis(int axis, std::vector<QVector4D> inVertices, std::vector<QVector4D>& outputVertices)
{
    QVector4D currVertice;
    QVector4D prevVertice;

    float prevDot;
    float currDot;

    float intersectionFactor;
    QVector4D intersectionPoint;

    int prevPoint, currPoint;
    if (axis == 0) {
        prevPoint = prevVertice.x();
        currPoint = currVertice.x();
    }
    else if (axis == 1) {
        prevPoint = prevVertice.y();
        currPoint = currVertice.y();
    }
    else {
        prevPoint = prevVertice.z();
        currPoint = currVertice.z();
    }

    // clip against first plane
    prevVertice = inVertices[inVertices.size() - 1];
    prevDot = (prevPoint <= prevVertice.w()) ? 1 : -1;

    for (size_t i = 0; i < inVertices.size(); i++) {
        currVertice = inVertices[i];
        currDot = (currPoint <= currVertice.w()) ? 1 : -1;

        if (prevDot * currDot < 0)
        {
            //Need to clip against plan w=0

            intersectionFactor = (prevVertice.w() - prevPoint) / ((prevVertice.w() - prevPoint) - (currVertice.w() - currPoint) );
            intersectionPoint = currVertice;
            intersectionPoint -= prevVertice;
            intersectionPoint *= intersectionFactor;
            intersectionPoint += prevVertice;

            outputVertices.push_back(intersectionPoint);
        }

        if (currDot > 0) {
            outputVertices.push_back(currVertice);
        }

        prevDot = currDot;
        prevVertice = currVertice;
    }

    // clip against opposite plane
    prevVertice = inVertices[inVertices.size() - 1];
    prevDot = (-prevPoint <= prevVertice.w()) ? 1 : -1;
    for (size_t i = 0; i < inVertices.size(); i++) {
        currVertice = inVertices[i];
        currDot = (-currPoint <= currVertice.w()) ? 1 : -1;

        if (prevDot * currDot < 0) {
            intersectionFactor = (prevVertice.w() + prevPoint) / ((prevVertice.w() + prevPoint) - (currVertice.w() + currPoint));
            intersectionPoint = currVertice;
            intersectionPoint -= prevVertice;
            intersectionPoint *= intersectionFactor;
            intersectionPoint += prevVertice;

            outputVertices.push_back(intersectionPoint);
        }

        if (currDot > 0) {
            outputVertices.push_back(currVertice);
        }

        prevDot = currDot;
        prevVertice = currVertice;
    }
}
