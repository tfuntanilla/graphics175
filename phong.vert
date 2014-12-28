#version 330

in vec4 posAttr;
in vec3 normAttr;
in vec2 texAttr;
in vec3 tanAttr;
in vec3 bitanAttr;

uniform int normalMap;

uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvp;

out vec4 modelViewPos;
out vec3 N;

out vec4 texCoord;
out vec2 uvCoord;
out vec3 T;
out vec3 B;

void main()
{
    // position in model view
    modelViewPos = modelViewMatrix * posAttr;

    // normals in model view
    N = normalize(normalMatrix * normAttr);

    // for bump mapping
    T = normalize(normalMatrix * tanAttr);
    //B = bitanAttr;
    B = normalize(normalMatrix * (cross(N, T)));
    // get texture coordinates
    texCoord = posAttr; // for quad, cube, cylinder, and sphere mapping
    uvCoord = texAttr; // for uv mapping

    gl_Position = mvp * posAttr;
}

