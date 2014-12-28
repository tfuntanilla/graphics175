#version 330

uniform mat4 mvp;

in vec4 posAttr;
in vec4 colAttr;

out vec2 texCoord;

void main() {
    // get texture coordinate
    texCoord = posAttr.xy;
    gl_Position = mvp * posAttr;
}
