#version 330

out vec4 fragColor;

// from vertex shader
in vec3 intensity;

void main(){

    fragColor = vec4(intensity, 1.0);
}
