#version 330

out vec4 fragColor;

// from vertex shader
in vec3 lightIntensity;

void main() {

    fragColor = vec4(lightIntensity, 1.0);
}
