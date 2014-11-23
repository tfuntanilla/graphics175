#version 330

in vec4 posAttr;
in vec3 normAttr;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvp;

out vec4 modelViewPos;
out vec3 N;

void main()
{
    // position in model view
    modelViewPos = modelViewMatrix * posAttr;
    // normals in model view
    N = normalize(normalMatrix * normAttr);

    gl_Position = mvp * posAttr;
}

