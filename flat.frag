#version 330

out vec4 fragColor;
uniform int numOfLights;

// from vertex shader
flat in vec3 intensity[10];

void main(){

    for (int i = 0; i < numOfLights; i++) {
        fragColor = vec4(intensity[i], 1.0);
    }
}
