#include "renderwindow.h"

#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QByteArray>
#include <QJsonObject>
#include <QOpenGLTexture>

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
    , m_useSourceCode(false)
{
    setAnimating(false);

    perspectiveOn = true;
    wireFrameOn = false;

    m_flatShadeOn = false;
    m_gouraudShadeOn = false;
    m_phongShadeOn = true;

    boxMapOn = false;
    sphereMapOn = true;
    cylinderMapOn = false;
    UVOn = false;

    totalLights = 0;

    texInterpolation = 0;
    normalMap = 0;
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
        m_colAttr = m_flatShaderProgram->attributeLocation("colAttr");
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
        m_attenuation = m_flatShaderProgram->uniformLocation("attenuationFactors");
        m_lightDistance = m_flatShaderProgram->uniformLocation("lightDistance");
    }
    else if (m_gouraudShadeOn) {
        m_gouraudShaderProgram = new QOpenGLShaderProgram(this);
        m_gouraudShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/gouraud.vert");
        m_gouraudShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/gouraud.frag");
        m_gouraudShaderProgram->link();
        m_posAttr = m_gouraudShaderProgram->attributeLocation("posAttr");
        m_colAttr = m_gouraudShaderProgram->attributeLocation("colAttr");
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
        m_attenuation = m_gouraudShaderProgram->uniformLocation("attenuationFactors");
        m_lightDistance = m_gouraudShaderProgram->uniformLocation("lightDistance");
    }
    else if (m_phongShadeOn) {
        m_phongShaderProgram = new QOpenGLShaderProgram(this);
        m_phongShaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/phong.vert");
        m_phongShaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/phong.frag");
        m_phongShaderProgram->link();
        m_posAttr = m_phongShaderProgram->attributeLocation("posAttr");
        m_colAttr = m_phongShaderProgram->attributeLocation("colAttr");
        m_normAttr = m_phongShaderProgram->attributeLocation("normAttr");
        m_matrixUniform = m_phongShaderProgram->uniformLocation("mvp");
        m_modelViewUniform = m_phongShaderProgram->uniformLocation("modelViewMatrix");
        m_modelUniform = m_phongShaderProgram->uniformLocation("modelMatrix");
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
        m_attenuation = m_phongShaderProgram->uniformLocation("attenuationFactors");
        m_lightDistance = m_phongShaderProgram->uniformLocation("lightDistance");

        m_texAttr = m_phongShaderProgram->attributeLocation("texAttr");
        m_tanAttr = m_phongShaderProgram->attributeLocation("tanAttr");
        m_bitanAttr = m_phongShaderProgram->attributeLocation("bitanAttr");

    }
    else {
        m_program = new QOpenGLShaderProgram(this);
        if(!m_useSourceCode) {
            m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/simple.vert");
            m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/simple.frag");
        } else {
            m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
            m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
        }
        m_program->link();
        m_posAttr = m_program->attributeLocation("posAttr");
        m_colAttr = m_program->attributeLocation("colAttr");
        m_matrixUniform = m_program->uniformLocation("mvp");
    }
}

void RenderWindow::enableAttr(int vlen, int nlen)
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

        m_phongShaderProgram->enableAttributeArray(m_colAttr);
        m_phongShaderProgram->setAttributeBuffer(m_colAttr, GL_FLOAT, vlen * sizeof(GLfloat), 3);

        m_phongShaderProgram->enableAttributeArray(m_normAttr);
        m_phongShaderProgram->setAttributeBuffer(m_normAttr, GL_FLOAT, (2 * vlen) * sizeof(GLfloat), 3);

        m_phongShaderProgram->enableAttributeArray(m_texAttr);
        m_phongShaderProgram->setAttributeBuffer(m_texAttr, GL_FLOAT, (2 * vlen + nlen) * sizeof(GLfloat), 2);

        m_phongShaderProgram->enableAttributeArray(m_tanAttr);
        m_phongShaderProgram->setAttributeBuffer(m_tanAttr, GL_FLOAT, (3 * vlen + nlen) * sizeof(GLfloat), 3);

        m_phongShaderProgram->enableAttributeArray(m_bitanAttr);
        m_phongShaderProgram->setAttributeBuffer(m_bitanAttr, GL_FLOAT, (4 * vlen + nlen) * sizeof(GLfloat), 3);

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
            int tlen = 0;


            for (size_t i = 0; i < shapes.size(); i++) {
                vlen += shapes[i].mesh.positions.size();
                ilen += shapes[i].mesh.indices.size();
                nlen += shapes[i].mesh.normals.size();
                tlen += shapes[i].mesh.texcoords.size();
                //qDebug() << vlen << ilen << nlen << tlen;
            }

            if (nlen == 0) {
                nlen = vlen;
                tlen = vlen;
            }

            std::vector<QVector3D> verticesVector;
            std::vector<QVector2D> texVectors;
            GLfloat vertices[vlen];
            GLuint indices[ilen];
            GLfloat normals[nlen];
            GLfloat texcoords[tlen];
            GLfloat tangents[vlen];
            GLfloat bitangents[vlen];
            indicesCount.push_back(ilen);

            for (size_t i = 0; i < shapes.size(); i++) {
                for (size_t j = 0; j < shapes[i].mesh.positions.size() / 3; j++) {
                    vertices[3*j+0] = shapes[i].mesh.positions[3*j+0];
                    vertices[3*j+1] = shapes[i].mesh.positions[3*j+1];
                    vertices[3*j+2] = shapes[i].mesh.positions[3*j+2];

                    //qDebug() << vertices[3*j+0] << vertices[3*j+1] << vertices[3*j+2];

                    // store vertex in verticesVector
                    QVector3D vertex(vertices[3*j+0], vertices[3*j+1], vertices[3*j+2]);
                    verticesVector.push_back(vertex); // first vertex = 181
                }

                if (shapes[i].mesh.texcoords.size() != 0) {
                    for (size_t j = 0; j < shapes[i].mesh.texcoords.size() / 2; j++) {
                        texcoords[2*j+0] = shapes[i].mesh.texcoords[2*j+0];
                        texcoords[2*j+1] = shapes[i].mesh.texcoords[2*j+1];
                        texVectors.push_back(QVector2D(texcoords[2*j+0], texcoords[2*j+1]));
                    }
                }
                else {
                    for (int j = 0; j < vlen; j++) {
                        texcoords[2*j+0] = vertices[3*j+0];
                        texcoords[2*j+1] = vertices[3*j+1];
                        texVectors.push_back(QVector2D(texcoords[2*j+0], texcoords[2*j+1]));
                    }
                }

                //qDebug() << vlen/3 << verticesVector.size() << texVectors.size();

                tangentVectors.clear();
                normalVectors.clear();
                bitangentVectors.clear();
                for (size_t j = 0; j < verticesVector.size(); j++) {
                    tangentVectors.append(QVector3D(0, 0, 0));
                    normalVectors.append(QVector3D(0, 0, 0));
                    bitangentVectors.append(QVector3D(0, 0, 0));
                }

                for (size_t j = 0; j < shapes[i].mesh.indices.size() / 3; j++) {
                    indices[3*j+0] = shapes[i].mesh.indices[3*j+0];
                    indices[3*j+1] = shapes[i].mesh.indices[3*j+1];
                    indices[3*j+2] = shapes[i].mesh.indices[3*j+2];
                    //qDebug() << indices[3*j+0] << indices[3*j+1] << indices[3*j+2];

                    calculateSurfaceNormals(verticesVector, texVectors, indices[3*j+0], indices[3*j+1], indices[3*j+2]);
                }


                //qDebug() << normalVectors.size() << tangentVectors.size();
                for (int j = 0; j < tangentVectors.size(); j++) {
                    tangents[3*j+0] = tangentVectors[j].x();
                    tangents[3*j+1] = tangentVectors[j].y();
                    tangents[3*j+2] = tangentVectors[j].z();

                    bitangents[3*j+0] = bitangentVectors[j].x();
                    bitangents[3*j+1] = bitangentVectors[j].y();
                    bitangents[3*j+2] = bitangentVectors[j].z();

                    //qDebug() << tangents[3*j+0] << tangents[3*j+1] << tangents[3*j+2];
                }


                if (m_flatShadeOn) {
                    for (int j = 0; j < normalVectors.size(); j++) {
                        normals[3*j+0] = normalVectors[j].x();
                        normals[3*j+1] = normalVectors[j].y();
                        normals[3*j+2] = normalVectors[j].z();
                    }
                }
                else if (shapes[i].mesh.normals.size() > 0) {
                    for (size_t j = 0; j < shapes[i].mesh.normals.size() / 3; j++) {
                        normals[3*j+0] = shapes[i].mesh.normals[3*j+0];
                        normals[3*j+1] = shapes[i].mesh.normals[3*j+1];
                        normals[3*j+2] = shapes[i].mesh.normals[3*j+2];
                    }
                }
                else {
                    for (int j = 0; j < normalVectors.size(); j++) {
                        normals[3*j+0] = normalVectors[j].x();
                        normals[3*j+1] = normalVectors[j].y();
                        normals[3*j+2] = normalVectors[j].z();
                    }
                }

            }

            int clen = vlen;
            GLfloat colors[clen];
            std::fill_n(colors, clen, 1.0f);
            /*for (int i = 0; i < clen; i+=9) {
               colors[i] = 1.0f;
               if ((i+4) <= clen) {
                    colors[i+4] = 1.0f;
               }
               if ((i+4) <= clen) {
                    colors[i+8] = 1.0f;
                }
            }*/

            m_vbo[i]->bind();
            m_vbo[i]->allocate((vlen + clen + nlen + tlen + vlen + vlen)*sizeof(GLfloat));
            m_vbo[i]->write(0, vertices, vlen * sizeof(GLfloat));
            m_vbo[i]->write(vlen*sizeof(GLfloat), colors, clen * sizeof(GLfloat));
            m_vbo[i]->write((vlen + clen)*sizeof(GLfloat), normals, nlen * sizeof(GLfloat));
            m_vbo[i]->write((vlen + clen + nlen)*sizeof(GLfloat), texcoords, tlen * sizeof(GLfloat));
            m_vbo[i]->write((vlen + clen + nlen + tlen)*sizeof(GLfloat), tangents, vlen * sizeof(GLfloat));
            m_vbo[i]->write((vlen + clen + nlen + tlen + vlen)*sizeof(GLfloat), bitangents, vlen * sizeof(GLfloat));

            checkError("after vertex buffer allocation");

            m_ibo[i]->bind();
            m_ibo[i]->allocate(indices, ilen*sizeof(GLuint));

            checkError("after index buffer allocation");

            enableAttr(vlen, nlen);

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

            // create texture
            QImage image("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/checkered.png");
            QOpenGLTexture texture(image.mirrored());
            checkError("after new texture");

            //create bump texture
            QImage bumpImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg");
            QOpenGLTexture bumpTexture(bumpImage);
            checkError("after new texture");

            // create cube texture
            QOpenGLTexture* cubeTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
            checkError("after new cube texture");
            // the 6 environment images
            QImage up = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box1.png").convertToFormat(QImage::Format_RGBA8888);
            QImage dn = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box2.png").convertToFormat(QImage::Format_RGBA8888);
            QImage lf = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box3.png").convertToFormat(QImage::Format_RGBA8888);
            QImage rt = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box4.png").convertToFormat(QImage::Format_RGBA8888);
            QImage ft = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box5.png").convertToFormat(QImage::Format_RGBA8888);
            QImage bk = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/box6.png").convertToFormat(QImage::Format_RGBA8888);
            // texture setData
            cubeTexture->setFormat(QOpenGLTexture::RGB32F);
            cubeTexture->setSize(lf.width(), lf.height());
            cubeTexture->allocateStorage();
            checkError("after allocate storage");
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, lf.constBits());
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, rt.constBits());
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, dn.constBits());
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, up.constBits());
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, ft.constBits());
            cubeTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, bk.constBits());

            // create cube bump texture
            QOpenGLTexture* cubeBumpTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
            checkError("after new cube texture");
            // the 6 environment images
            QImage upb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            QImage dnb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            QImage lfb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            QImage rtb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            QImage ftb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            QImage bkb = QImage("/Users/trishamariefuntanilla/Box Sync/ECS175/Project/Project/normaltexture.jpg").convertToFormat(QImage::Format_RGBA8888);
            // texture setData
            cubeBumpTexture->setFormat(QOpenGLTexture::RGB32F);
            cubeBumpTexture->setSize(lfb.width(), lfb.height());
            cubeBumpTexture->allocateStorage();
            checkError("after cube bump allocate storage");
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, lfb.constBits());
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, rtb.constBits());
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, dnb.constBits());
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, upb.constBits());
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, ftb.constBits());
            cubeBumpTexture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, bkb.constBits());


            // set texture wrap mode based on user selection
            if (wrapMode == 0) {
                texture.setWrapMode(QOpenGLTexture::Repeat);
                bumpTexture.setWrapMode(QOpenGLTexture::Repeat);
                cubeTexture->setWrapMode(QOpenGLTexture::Repeat);
                cubeBumpTexture->setWrapMode(QOpenGLTexture::Repeat);
            }
            else if (wrapMode == 1) {
                texture.setWrapMode(QOpenGLTexture::MirroredRepeat);
                bumpTexture.setWrapMode(QOpenGLTexture::MirroredRepeat);
                cubeTexture->setWrapMode(QOpenGLTexture::MirroredRepeat);
                cubeBumpTexture->setWrapMode(QOpenGLTexture::MirroredRepeat);
            }
            else if (wrapMode == 2) {
                texture.setWrapMode(QOpenGLTexture::ClampToEdge);
                bumpTexture.setWrapMode(QOpenGLTexture::ClampToEdge);
                cubeTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
                cubeBumpTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
            }
            else if (wrapMode == 3) {
                texture.setWrapMode(QOpenGLTexture::ClampToBorder);
                bumpTexture.setWrapMode(QOpenGLTexture::ClampToBorder);
                cubeTexture->setWrapMode(QOpenGLTexture::ClampToBorder);
                cubeBumpTexture->setWrapMode(QOpenGLTexture::ClampToBorder);
            }

            // set interpolation based on user selection
            if (texInterpolation == 0) {
                texture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
                bumpTexture.setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
                cubeTexture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
                cubeBumpTexture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
            }
            else {
                texture.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
                bumpTexture.setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
                cubeTexture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
                cubeBumpTexture->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
            }

            if (m_flatShadeOn) {
                m_flatShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);
                m_flatShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_flatShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());
                m_flatShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_flatShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);
                m_flatShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));
                m_flatShaderProgram->setUniformValue(m_IaUniform, lighting.getIa());
                m_flatShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_flatShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_flatShaderProgram->setUniformValue(m_IaRGBUniform, lighting.getIaRGB());
                m_flatShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_flatShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_flatShaderProgram->setUniformValue(m_KaUniform, objectmodels[i].getKaRGB());
                m_flatShaderProgram->setUniformValue(m_KdUniform, objectmodels[i].getKdRGB());
                m_flatShaderProgram->setUniformValue(m_KsUniform, objectmodels[i].getKsRGB());
                m_flatShaderProgram->setUniformValue(m_shineUniform, objectmodels[i].getN());
                m_flatShaderProgram->setUniformValueArray(m_attenuation, lighting.getAttenuationFactors(), 10);
                m_flatShaderProgram->setUniformValueArray(m_lightDistance, lighting.getLightDistance(), 10, 1);
            }
            else if (m_gouraudShadeOn) {
                m_gouraudShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);
                m_gouraudShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_gouraudShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());
                m_gouraudShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_gouraudShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);
                m_gouraudShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));
                m_gouraudShaderProgram->setUniformValue(m_IaUniform, lighting.getIa());
                m_gouraudShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_gouraudShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_gouraudShaderProgram->setUniformValue(m_IaRGBUniform, lighting.getIaRGB());
                m_gouraudShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_gouraudShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_gouraudShaderProgram->setUniformValue(m_KaUniform, objectmodels[i].getKaRGB());
                m_gouraudShaderProgram->setUniformValue(m_KdUniform, objectmodels[i].getKdRGB());
                m_gouraudShaderProgram->setUniformValue(m_KsUniform, objectmodels[i].getKsRGB());
                m_gouraudShaderProgram->setUniformValue(m_shineUniform, objectmodels[i].getN());
                m_gouraudShaderProgram->setUniformValueArray(m_attenuation, lighting.getAttenuationFactors(), 10);
                m_gouraudShaderProgram->setUniformValueArray(m_lightDistance, lighting.getLightDistance(), 10, 1);
            }
            else if (m_phongShadeOn) {
                m_phongShaderProgram->setUniformValue(m_matrixUniform, projection * view * model);
                m_phongShaderProgram->setUniformValue(m_modelViewUniform, view * model);
                m_phongShaderProgram->setUniformValue(m_modelUniform, model);
                m_phongShaderProgram->setUniformValue(m_normalMatrixUniform, (view * model).normalMatrix());
                m_phongShaderProgram->setUniformValue(m_numOfLights, totalLights);
                m_phongShaderProgram->setUniformValueArray(m_lightPosition, lighting.lightPos, 10);
                m_phongShaderProgram->setUniformValue(m_eyePosition, QVector3D(camera.returnEye()));
                m_phongShaderProgram->setUniformValue(m_IaUniform, lighting.getIa());
                m_phongShaderProgram->setUniformValueArray(m_IdUniform, lighting.getId(), 10, 1);
                m_phongShaderProgram->setUniformValueArray(m_IsUniform, lighting.getIs(), 10, 1);
                m_phongShaderProgram->setUniformValue(m_IaRGBUniform, lighting.getIaRGB());
                m_phongShaderProgram->setUniformValueArray(m_IdRGBUniform, lighting.getIdRGB(), 10);
                m_phongShaderProgram->setUniformValueArray(m_IsRGBUniform, lighting.getIsRGB(), 10);
                m_phongShaderProgram->setUniformValue(m_KaUniform, objectmodels[i].getKaRGB());
                m_phongShaderProgram->setUniformValue(m_KdUniform, objectmodels[i].getKdRGB());
                m_phongShaderProgram->setUniformValue(m_KsUniform, objectmodels[i].getKsRGB());
                m_phongShaderProgram->setUniformValue(m_shineUniform, objectmodels[i].getN());
                m_phongShaderProgram->setUniformValueArray(m_attenuation, lighting.getAttenuationFactors(), 10);
                m_phongShaderProgram->setUniformValueArray(m_lightDistance, lighting.getLightDistance(), 10, 1);

                // set uniform sampler
                m_phongShaderProgram->setUniformValue("tex", 0);
                m_phongShaderProgram->setUniformValue("cubeTex", 1);
                m_phongShaderProgram->setUniformValue("bumpTex", 2);
                m_phongShaderProgram->setUniformValue("cubeBumpTex", 3);


                // select whether normal mapping is on or not
                if (normalMap == 0) {
                    m_phongShaderProgram->setUniformValue("normalMap", 0);
                }
                else {
                    m_phongShaderProgram->setUniformValue("normalMap", 1);
                }

                // for all the other mapping types
                if (sphereMapOn) {
                    if (objectmodels[i].getName() == "quad") {
                        m_phongShaderProgram->setUniformValue("mappingType", 4);
                    }
                    else {
                        m_phongShaderProgram->setUniformValue("mappingType", 0);
                    }
                }
                else if (cylinderMapOn) {
                    if (objectmodels[i].getName() == "quad") {
                        m_phongShaderProgram->setUniformValue("mappingType", 4);
                    }
                    else {
                        m_phongShaderProgram->setUniformValue("mappingType", 1);
                    }
                }
                else if (UVOn) {
                    if (objectmodels[i].getName() == "quad") {
                        m_phongShaderProgram->setUniformValue("mappingType", 4);
                    }
                    else {
                        m_phongShaderProgram->setUniformValue("mappingType", 2);
                    }
                }
                else if (boxMapOn) {
                    if (objectmodels[i].getName() == "quad") {
                        m_phongShaderProgram->setUniformValue("mappingType", 4);
                    }
                    else {
                        m_phongShaderProgram->setUniformValue("mappingType", 3);
                    }
                }
            }
            else {
                m_program->setUniformValue(m_matrixUniform, projection * view * model);
                //m_program->setUniformValue("tex", 0);
            }

            texture.bind(0); // bind texture
            checkError("after texture bind");

            cubeTexture->bind(1);
            checkError("after cube texture bind");

            bumpTexture.bind(2);
            checkError("after bump texture bind");

            cubeBumpTexture->bind(3);
            checkError("after cube bump texture bind");

            m_vao[i]->bind();

            glDrawElements(GL_TRIANGLES, indicesCount[i], GL_UNSIGNED_INT, 0);

            texture.release(0); // release texture
            checkError("after texture release");

            cubeTexture->release(1);
            checkError("after cube texture release");

            bumpTexture.release(2);
            checkError("after bump texture release");

            cubeBumpTexture->release(3);
            checkError("after cube bump texture release");

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

void RenderWindow::updateModelProperties(int size, QVector<QVector3D> trans, QVector<QVector3D> rot, QVector<QVector3D> scale, QVector<QVector3D> kvec, QVector<float> nvec)
{
    objectmodels.resize(size);

    for (int i = 0; i < size; i++) {
        objectmodels[i].setNameAndIndex(objectNames[i], fnames[i], i);
    }

    for (int i = 0; i < size; i++) {
        objectmodels[i].setPropertiesValues(trans[i].x(), trans[i].y(), trans[i].z(),
                                            rot[i].x(), rot[i].y(), rot[i].z(),
                                            scale[i].x(), scale[i].y(),scale[i].z());

        objectmodels[i].setKa(kvec[i].x());
        objectmodels[i].setKd(kvec[i].y());
        objectmodels[i].setKs(kvec[i].z());
        objectmodels[i].setN(nvec[i]);
        objectmodels[i].setModel(matrices[i]);
    }
}

void RenderWindow::setFilePath(std::string p)
{
    path.append(p);
}

void RenderWindow::updateLightProperties
(int size, QVector<QVector4D> lPos, QVector<QVector3D> atten,
 QVector<QVector3D> ambient, QVector<QVector3D> diffuse, QVector<QVector3D> specular,
 QVector<QVector3D> intensities, QVector<float> dist)
{
    setTotalLights(size);
    for (int i = 0; i < size; i++) {
        lighting.lightPos[i] = lPos[i];
        lighting.setConstantAtten(i, atten[i].x());
        lighting.setLinearAtten(i, atten[i].y());
        lighting.setQuadAtten(i, atten[i].z());

        lighting.setIaRGBValues((qreal)ambient[i].x(), (qreal)ambient[i].y(), (qreal)ambient[i].z());
        lighting.setIdRGBValues(i, (qreal)diffuse[i].x(), (qreal)diffuse[i].y(), (qreal)diffuse[i].z());
        lighting.setIsRGBValues(i, (qreal)specular[i].x(), (qreal)specular[i].y(), (qreal)specular[i].z());
        lighting.setIaValue(intensities[i].x());
        lighting.setIdValues(i, intensities[i].y());
        lighting.setIsValues(i, intensities[i].z());

        lighting.setLightDistance(i, dist[i]);
    }
}

void RenderWindow::calculateSurfaceNormals(std::vector<QVector3D> v, std::vector<QVector2D> t, int a, int b, int c)
{
    QVector3D U = v[b] - v[a];
    QVector3D V = v[c] - v[a];

    float xNormal = U.y()*V.z() - U.z()*V.y();
    float yNormal = U.z()*V.x() - U.x()*V.z();
    float zNormal = U.x()*V.y() - U.y()*V.x();

    QVector3D normal(xNormal, yNormal, zNormal);
    //normal.normalize();
    normalVectors[a] = normal;
    normalVectors[b] = normal;
    normalVectors[c] = normal;

    float deltaU1 = t[b].x() - t[a].x();
    float deltaV1 = t[b].y() - t[a].y();
    float deltaU2 = t[c].x() - t[a].x();
    float deltaV2 = t[c].y() - t[a].y();

    float f = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

    QVector3D tangent;
    QVector3D bitangent;

    tangent.setX(f * (deltaV2 * U.x() - deltaV1 * V.x()));
    tangent.setY(f * (deltaV2 * U.y() - deltaV1 * V.y()));
    tangent.setZ(f * (deltaV2 * U.z() - deltaV1 * V.z()));

    bitangent.setX(f * (-deltaU2 * U.x() - deltaU1 * V.x()));
    bitangent.setY(f * (-deltaU2 * U.y() - deltaU1 * V.y()));
    bitangent.setZ(f * (-deltaU2 * U.z() - deltaU1 * V.z()));

    //tangent.normalize();
    tangentVectors[a] += tangent;
    tangentVectors[b] += tangent;
    tangentVectors[c] += tangent;

    //bitangent.normalize();
    bitangentVectors[a] += bitangent;
    bitangentVectors[b] += bitangent;
    bitangentVectors[c] += bitangent;

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
