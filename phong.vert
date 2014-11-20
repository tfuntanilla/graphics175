#version 330

in vec3 posAttr;
in vec3 normAttr;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvp;

out vec4 worldPos;
out vec3 N;

void main()
{
    worldPos = modelViewMatrix * vec4(posAttr, 1.0);
    N = normalize(normalMatrix * normAttr);

    gl_Position = mvp * vec4(posAttr, 1.0);
}

