#ifndef SHAPES_H
#define SHAPES_H

#include <QOpenGLFunctions>

class Shapes
{
public:

    Shapes();
    ~Shapes();

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    std::vector<GLuint> indices;

    int index;
    int vlen;
    int clen;
    int ilen;

};

#endif // SHAPES_H
