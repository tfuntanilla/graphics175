#version 330

uniform sampler2D tex;
in vec2 texCoord;

in vec4 color;
out vec4 fragColor;

void main() {
    // sample texture
    fragColor = texture(tex, texCoord);
}
