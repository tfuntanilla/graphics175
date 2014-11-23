#version 330

out vec4 fragColor;
uniform int numOfLights;

// from vertex shader
in vec3 lightIntensity[10];

void main(){

    for (int i = 0; i < numOfLights; i++) {
        fragColor = vec4(lightIntensity[i], 1.0);
    }

}
