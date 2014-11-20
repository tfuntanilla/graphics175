#version 330

out vec4 fragColor;

uniform vec4 lightPos;
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
    // light direction
    vec3 L = normalize(vec3(lightPos - worldPos));

    // N dot L
    float NdotL = max(0.0, dot(N, L));

    // view direction
    vec3 V = normalize(eyePos - vec3(worldPos));

    vec3 specular = vec3(0.0, 0.0, 0.0);

    if (NdotL > 0.0) {

        // reflection
        vec3 R = -normalize(reflect(N, L));

        specular = Is * Ks * pow(max(0.0, dot(R, V)), n);
    }

    // light intensity
    vec3 intensity = (Ia * Ka) + (Id * Kd * NdotL) + specular;

    fragColor = vec4(intensity, 1.0);
}
