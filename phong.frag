#version 330

out vec4 fragColor;

uniform int numOfLights;
uniform vec4 lightPos[10];
uniform vec3 eyePos;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float n;

in vec4 worldPos;
in vec3 N;

void main()
{
    // view direction
    vec3 V = normalize(eyePos - vec3(worldPos));

    vec3 intensity[10];

    for (int i = 0; i < numOfLights; i++) {
        // light direction
        vec3 L = normalize(vec3(lightPos[i] - worldPos));

        // N dot L
        float NdotL = max(0.0, dot(N, L));

        vec3 specular = vec3(0.0, 0.0, 0.0);

        if (NdotL > 0.0) {

            // reflection
            vec3 R = -normalize(reflect(N, L));

            specular = Is * Ks * pow(max(0.0, dot(R, V)), n);
        }

        // light intensity
        intensity[i] = (Ia * Ka) + (Id * Kd * NdotL) + specular;

        fragColor = vec4(intensity[i], 1.0);

    }


}
