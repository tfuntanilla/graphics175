#include "renderwindow.h"

#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QFileDialog>
#include <QByteArray>

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
    indicesCount = 0;
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
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string inputfile = "/Users/trishamariefuntanilla/Box Sync/ECS175/Project1/teapot.obj";

    tinyobj::LoadObj(shapes, materials, inputfile.c_str());

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

    m_program->bind();

    /// check for errors to ensure OpenGL
    /// is functioning properly.
    checkError("after program bind");

    m_vao->bind();


    int vlen = 0;
    for (size_t i = 0; i < shapes.size(); i++) {
        vlen += shapes[i].mesh.positions.size();
    }

    /* Debugging vertices */
    /*
    std::cout << "Total no. of shapes: " << shapes.size() << std::endl;
    std::cout << "Vertices: " << std::endl;

    for (size_t i = 0; i < shapes.size(); i++) {
        for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
          printf("  v[%ld] = (%f, %f, %f)\n", v,
            shapes[i].mesh.positions[3*v+0],
            shapes[i].mesh.positions[3*v+1],
            shapes[i].mesh.positions[3*v+2]);
        }
    }

    std::cout << "Total no. of vertices: " << vlen << std::endl;
    */

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

    indicesCount = ilen;
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

    //m_vbo->write(0, vertices, vlen * sizeof(GLfloat));
    m_vbo->write(vlen*sizeof(GLfloat), colors, clen * sizeof(GLfloat));

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

    m_vao->release();
    m_program->release();
}

void RenderWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    m_program->bind();

    /// set up projection
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
    model.translate(0, 0, -2000); /// place it a certain distance from camera
    model.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0); /// rotate if animation is on.

    m_program->setUniformValue(m_matrixUniform, projection * view * model);

    m_vao->bind();
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
    m_vao->release();
    m_program->release();

    checkError("after program release");

    if(isAnimating()) {
        ++m_frame;
    }
}
