#version 330

out vec4 fragColor;

uniform int numOfLights;

uniform vec4 lightPos[10];
uniform vec3 eyePos;

uniform float Ia[10];
uniform float Id[10];
uniform float Is[10];
uniform vec3 IaRGB[10];
uniform vec3 IdRGB[10];
uniform vec3 IsRGB[10];

uniform vec3 Ka[10];
uniform vec3 Kd[10];
uniform vec3 Ks[10];

uniform float n[10];

in vec4 modelViewPos;
in vec3 N;

void main()
{
    vec3 lightIntensity[10];

    for (int i = 0; i < numOfLights; i++) {
        vec3 ambient = Ia[i] * IaRGB[i] * Ka[i];

        // light direction
        vec3 L = normalize(vec3(lightPos[i] - modelViewPos));
        // N dot L
        float NdotL = max(0.0, dot(N, L));     
        vec3 diffuse = Id[i] * IdRGB[i] * Kd[i] * NdotL;

        // view direction
        vec3 V = normalize(-modelViewPos.xyz);
        // reflection
        vec3 R = -normalize(reflect(N, L));
        vec3 specular = vec3(0.0, 0.0, 0.0);
        if (NdotL > 0.0) {
            specular = Is[i] * IsRGB[i] * Ks[i] * pow(max(0.0, dot(R, V)), n[i]);
        }

        // light intensity
        lightIntensity[i] = ambient + diffuse + specular;

        fragColor = vec4(lightIntensity[i], 1.0);
    }
}
