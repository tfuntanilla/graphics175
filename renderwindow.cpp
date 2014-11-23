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

#define W_CLIPPING_PLANE 0.00001

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

    perspectiveOn = true;
    wireFrameOn = false;

    m_flatShadeOn = false;
    m_gouraudShadeOn = false;
    m_phongShadeOn = false;

    totalLights = 1;
/*
    for (int i = 0; i < 10; i++) {
        lightPos[i].setX(0.0); lightPos[i].setY(0.0); lightPos[i].setZ(0.0); lightPos[i].setW(1.0);
        Ia[i] = 1.0; Id[i] = 1.0; Is[i] = 1.0;
        IaRGB[i].setX(1.0); IaRGB[i].setY(1.0); IaRGB[i].setZ(1.0);
        IdRGB[i].setX(1.0); IdRGB[i].setY(1.0); IdRGB[i].setZ(1.0);
        IsRGB[i].setX(1.0); IsRGB[i].setY(1.0); IsRGB[i].setZ(1.0);

    }

    Ka = 1.0; Ka_r = 0.45; Ka_g = 0.0; Ka_b = 0.0;
    Kd = 1.0; Kd_r = 0.55; Kd_g = 0.0; Kd_b = 0.0;
    Ks = 1.0; Ks_r = 1.0; Ks_g = 1.0; Ks_b = 1.0;


*/
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


    //m_program->link();
    //linkShaderPrograms();

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */
}

void RenderWindow::linkShaderPrograms()
{
    if (m_flatShadeOn) {
        m_flatShaderProgram = new QOpenGLShaderProgram(this);
        m_flatShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/flat.vert");
        m_flatShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/flat.frag");
        m_flatShaderProgram->link();

        m_posAttr = m_flatShaderProgram->attributeLocation("posAttr");
        m_normAttr = m_flatShaderProgram->attributeLocation("normAttr");
        m_matrixUniform = m_flatShaderProgram->uniformLocation("mvp");

        m_modelViewUniform = m_flatShaderProgram->uniformLocation("modelViewMatrix");
        m_normalMatrixUniform = m_flatShaderProgram->uniformLocation("normalMatrix");

        m_numOfLights = m_flatShaderProgram->uniformLocation("numOfLights");
        m_lightPosition = m_flatShaderProgram->uniformLocation("lightPos");
        m_eyePosition = m_flatShaderProgram->uniformLocation("eyePos");

        m_IaUniform = m_flatShaderProgram->uniformLocation("Ia");
        m_IdUniform = m_flatShaderProgram->uniformLocation("Id");
        m_IsUniform = m_flatShaderProgram->uniformLocation("Is");
        m_IaRGBUniform = m_flatShaderProgram->uniformLocation("IaRGB");
        m_IdRGBUniform = m_flatShaderProgram->uniformLocation("IdRGB");
        m_IsRGBUniform = m_flatShaderProgram->uniformLocation("IsRGB");
        m_KaUniform = m_flatShaderProgram->uniformLocation("Ka");
        m_KdUniform = m_flatShaderProgram->uniformLocation("Kd");
        m_KsUniform = m_flatShaderProgram->uniformLocation("Ks");
        m_shineUniform = m_flatShaderProgram->uniformLocation("n");
    }
    else if (m_gouraudShadeOn) {
        m_gouraudShaderProgram = new QOpenGLShaderProgram(this);

        m_gouraudShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/gouraud.vert");
        m_gouraudShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/gouraud.frag");
        m_gouraudShaderProgram->link();

        m_posAttr = m_gouraudShaderProgram->attributeLocation("posAttr");
        m_normAttr = m_gouraudShaderProgram->attributeLocation("normAttr");
        m_matrixUniform = m_gouraudShaderProgram->uniformLocation("mvp");

        m_modelViewUniform = m_gouraudShaderProgram->uniformLocation("modelViewMatrix");
        m_normalMatrixUniform = m_gouraudShaderProgram->uniformLocation("normalMatrix");

        m_numOfLights = m_gouraudShaderProgram->uniformLocation("numOfLights");
        m_lightPosition = m_gouraudShaderProgram->uniformLocation("lightPos");
        m_eyePosition = m_gouraudShaderProgram->uniformLocation("eyePos");

        m_IaUniform = m_gouraudShaderProgram->uniformLocation("Ia");
        m_IdUniform = m_gouraudShaderProgram->uniformLocation("Id");
        m_IsUniform = m_gouraudShaderProgram->uniformLocation("Is");
        m_IaRGBUniform = m_gouraudShaderProgram->uniformLocation("IaRGB");
        m_IdRGBUniform = m_gouraudShaderProgram->uniformLocation("IdRGB");
        m_IsRGBUniform = m_gouraudShaderProgram->uniformLocation("IsRGB");
        m_KaUniform = m_gouraudShaderProgram->uniformLocation("Ka");
        m_KdUniform = m_gouraudShaderProgram->uniformLocation("Kd");
        m_KsUniform = m_gouraudShaderProgram->uniformLocation("Ks");
        m_shineUniform = m_gouraudShaderProgram->uniformLocation("n");
    }
    else if (m_phongShadeOn) {
        m_phongShaderProgram = new QOpenGLShaderProgram(this);
        m_phongShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/phong.vert");
        m_phongShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/phong.frag");
        m_phongShaderProgram->link();

        m_posAttr = m_phongShaderProgram->attributeLocation("posAttr");
        m_normAttr = m_phongShaderProgram->attributeLocation("normAttr");
        m_matrixUniform = m_phongShaderProgram->uniformLocation("mvp");

        m_modelViewUniform = m_phongShaderProgram->uniformLocation("modelViewMatrix");
        m_normalMatrixUniform = m_phongShaderProgram->uniformLocation("normalMatrix");

        m_numOfLights = m_phongShaderProgram->uniformLocation("numOfLights");
        m_lightPosition = m_phongShaderProgram->uniformLocation("lightPos");
        m_eyePosition = m_phongShaderProgram->uniformLocation("eyePos");

        m_IaUniform = m_phongShaderProgram->uniformLocation("Ia");
        m_IdUniform = m_phongShaderProgram->uniformLocation("Id");
        m_IsUniform = m_phongShaderProgram->uniformLocation("Is");
        m_IaRGBUniform = m_phongShaderProgram->uniformLocation("IaRGB");
        m_IdRGBUniform = m_phongShaderProgram->uniformLocation("IdRGB");
        m_IsRGBUniform = m_phongShaderProgram->uniformLocation("IsRGB");
        m_KaUniform = m_phongShaderProgram->uniformLocation("Ka");
        m_KdUniform = m_phongShaderProgram->uniformLocation("Kd");
        m_KsUniform = m_phongShaderProgram->uniformLocation("Ks");
        m_shineUniform = m_phongShaderProgram->uniformLocation("n");
    }
    else {
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
    }

}

void RenderWindow::enableAttr(int vlen)
{
    if (m_flatShadeOn) {
        m_flatShaderProgram->enableAttributeArray(m_posAttr);
        m_flatShaderProgram->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
        m_flatShaderProgram->enableAttributeArray(m_normAttr);
        m_flatShaderProgram->setAttributeBuffer(m_normAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);
    }
    else if (m_gouraudShadeOn) {
        m_gouraudShaderProgram->enableAttributeArray(m_posAttr);
        m_gouraudShaderProgram->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
        m_gouraudShaderProgram->enableAttributeArray(m_normAttr);
        m_gouraudShaderProgram->setAttributeBuffer(m_normAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);
    }
    else if (m_phongShadeOn) {
        m_phongShaderProgram->enableAttributeArray(m_posAttr);
        m_phongShaderProgram->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
        m_phongShaderProgram->enableAttributeArray(m_normAttr);
        m_phongShaderProgram->setAttributeBuffer(m_normAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);
    }
    else {
        m_program->enableAttributeArray(m_posAttr);
        m_program->setAttributeBuffer(m_posAttr, GL_FLOAT, 0, 3);
        m_program->enableAttributeArray(m_colAttr);
        m_program->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);
    }
    checkError("after enabling attributes");
}

void RenderWindow::render()
{
    linkShaderPrograms();

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // allocate space for vertex array objects as necessary
    for (int i = 0; (i < filenames.size() && m_vao.size() != filenames.size()); i++) {
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

    // select which shader to bind initially;
    if (m_flatShadeOn) {
        m_flatShaderProgram->bind();
    }
    else if (m_gouraudShadeOn) {
        m_gouraudShaderProgram->bind();
    }
    else if (m_phongShadeOn) {
        m_phongShaderProgram->bind();
    }
    else {
        m_program->bind();
    }

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
            int ilen = 0;
            int nlen = 0;

            for (size_t i = 0; i < shapes.size(); i++) {
                vlen += shapes[i].mesh.positions.size();
                ilen += shapes[i].mesh.indices.size();
            }
            nlen = vlen;

            std::vector<QVector3D> triangleVectors;
            GLfloat vertices[vlen];
            GLuint indices[ilen];
            GLfloat normals[nlen];
            indicesCount.push_back(ilen);

            for (size_t i = 0; i < shapes.size(); i++) {
                for (size_t j = 0; j < shapes[i].mesh.positions.size() / 3; j++) {
                    vertices[3*j+0] = shapes[i].mesh.positions[3*j+0];
                    vertices[3*j+1] = shapes[i].mesh.positions[3*j+1];
                    vertices[3*j+2] = shapes[i].mesh.positions[3*j+2];

                    QVector3D triangleVec(vertices[3*j+0], vertices[3*j+1], vertices[3*j+2]);
                    triangleVectors.push_back(triangleVec);
                }

                for (size_t j = 0; j < shapes[i].mesh.indices.size() / 3; j++) {
                    indices[3*j+0] = shapes[i].mesh.indices[3*j+0];
                    indices[3*j+1] = shapes[i].mesh.indices[3*j+1];
                    indices[3*j+2] = shapes[i].mesh.indices[3*j+2];

                    calculateSurfaceNormals(triangleVectors[indices[3*j+0]], triangleVectors[indices[3*j+1]], triangleVectors[indices[3*j+2]]);
                }

                if (m_flatShadeOn) {
                    for (size_t j = 0; j < triangleVectors.size(); j++) {
                        normals[3*j+0] = triangleVectors[j].x();
                        normals[3*j+1] = triangleVectors[j].y();
                        normals[3*j+2] = triangleVectors[j].z();
                    }
                }
                else {
                    for (size_t j = 0; j < shapes[i].mesh.normals.size() / 3; j++) {
                        normals[3*j+0] = shapes[i].mesh.normals[3*j+0];
                        normals[3*j+1] = shapes[i].mesh.normals[3*j+1];
                        normals[3*j+2] = shapes[i].mesh.normals[3*j+2];
                    }
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

            m_vbo[i]->bind();
            m_vbo[i]->allocate((vlen + nlen)*sizeof(GLfloat));
            m_vbo[i]->write(0, vertices, vlen * sizeof(GLfloat));
            m_vbo[i]->write(vlen*sizeof(GLfloat), normals, nlen * sizeof(GLfloat));

            checkError("after vertex buffer allocation");

            m_ibo[i]->bind();
            m_ibo[i]->allocate(indices, ilen*sizeof(GLuint));

            checkError("after index buffer allocation");

            enableAttr(vlen);

            /* *********************************************************************************************** */
            /* *********************************************************************************************** */

            // set up transformation matrices
            QMatrix4x4 projection = objectmodels[i].getProjection();
            if (perspectiveOn) {
                projection.perspective(60.0, (float)width()/(float)height(), 0.1, 1000);
            }
            else if (!perspectiveOn) {
                projection.ortho(-(float)width()/2, (float)width()/2, -(float)height()/2, (float)height()/2, 0.0, 1000.0);
            }

            QMatrix4x4 model = objectmodels[i].getModel();
            model.translate(objectmodels[i].xTrans, objectmodels[i].yTrans, objectmodels[i].zTrans);
            model.rotate(objectmodels[i].xRot/16.0, 1.0, 0.0, 0.0);
            model.rotate(objectmodels[i].yRot/16.0, 0.0, 1.0, 0.0);
            model.rotate(objectmodels[i].zRot/16.0, 0.0, 0.0, 1.0);
            model.scale(objectmodels[i].xScale, objectmodels[i].yScale, objectmodels[i].zScale);

            QMatrix4x4 view = camera.returnView();

            if (m_flatShadeOn) {
                m_flatShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);

                m_flatShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_flatShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());

                m_flatShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_flatShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);

                m_flatShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));

                m_flatShaderProgram->setUniformValueArray(m_IaUniform, lighting.getIa(), 10, 1);
                m_flatShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_flatShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_flatShaderProgram->setUniformValueArray(m_IaRGBUniform, lighting.getIaRGB(), 10);
                m_flatShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_flatShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_flatShaderProgram->setUniformValueArray(m_KaUniform, lighting.getKa(), 10);
                m_flatShaderProgram->setUniformValueArray(m_KdUniform, lighting.getKd(), 10);
                m_flatShaderProgram->setUniformValueArray(m_KsUniform, lighting.getKs(), 10);
                m_flatShaderProgram->setUniformValueArray(m_shineUniform, lighting.getn(), 10, 1);

            }
            else if (m_gouraudShadeOn) {
                m_gouraudShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);

                m_gouraudShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_gouraudShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());

                m_gouraudShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_gouraudShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);
                m_gouraudShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));

                m_gouraudShaderProgram->setUniformValueArray(m_IaUniform, lighting.getIa(), 10, 1);
                m_gouraudShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_gouraudShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_gouraudShaderProgram->setUniformValueArray(m_IaRGBUniform, lighting.getIaRGB(), 10);
                m_gouraudShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_gouraudShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_gouraudShaderProgram->setUniformValue(m_KaUniform, QVector3D(1.0, 1.0, 1.0));
                m_gouraudShaderProgram->setUniformValue(m_KdUniform, QVector3D(1.0, 1.0, 1.0));
                m_gouraudShaderProgram->setUniformValue(m_KsUniform, QVector3D(1.0, 1.0, 1.0));
                m_gouraudShaderProgram->setUniformValueArray(m_shineUniform, lighting.getn(), 10, 1);
            }
            else if (m_phongShadeOn) {
                m_phongShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);

                m_phongShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_phongShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());

                m_phongShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_phongShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);
                m_phongShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));

                m_phongShaderProgram->setUniformValueArray(m_IaUniform, lighting.getIa(), 10, 1);
                m_phongShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_phongShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_phongShaderProgram->setUniformValueArray(m_IaRGBUniform, lighting.getIaRGB(), 10);
                m_phongShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_phongShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_phongShaderProgram->setUniformValueArray(m_KaUniform, lighting.getKa(), 10);
                m_phongShaderProgram->setUniformValueArray(m_KdUniform, lighting.getKd(), 10);
                m_phongShaderProgram->setUniformValueArray(m_KsUniform, lighting.getKs(), 10);
                m_phongShaderProgram->setUniformValueArray(m_shineUniform, lighting.getn(), 10, 1);

            }
            else {
                m_program->setUniformValue(m_matrixUniform, projection * view * model);
            }


            m_vao[i]->bind();
            glDrawElements(GL_TRIANGLES, indicesCount[i], GL_UNSIGNED_INT, 0);

            m_vao[i]->release();

        }
    }

    /* *********************************************************************************************** */
    /* *********************************************************************************************** */

    if (m_flatShadeOn) {
        m_flatShaderProgram->release();
    }
    else if (m_gouraudShadeOn) {
        m_gouraudShaderProgram->release();
    }
    else if (m_phongShadeOn) {
        m_phongShaderProgram->release();
    }
    else {
        m_program->release();
    }

    checkError("after program release");

    if(isAnimating()) {
        ++m_frame;
    }
}

void RenderWindow::toggleWireFrame(bool on)
{
    if (on) {
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    path.append(p);
}

void RenderWindow::calculateSurfaceNormals(QVector3D v1, QVector3D v2, QVector3D v3)
{

    QVector3D U = v2 - v1;
    QVector3D V = v3 - v1;

    float xNormal = U.y()*V.z() - U.z()*V.y();
    float yNormal = U.z()*V.x() - U.x()*V.z();
    float zNormal = U.x()*V.y() - U.y()*V.x();

    QVector3D normal(xNormal, yNormal, zNormal);
    //qDebug() << normal;

    normals.push_back(normal);

}

void RenderWindow::setShader(bool flat, bool gouraud, bool phong)
{
    m_flatShadeOn = flat;
    m_gouraudShadeOn = gouraud;
    m_phongShadeOn = phong;
}

void RenderWindow::setTotalLights(int i)
{
    totalLights = totalLights + i;
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






















