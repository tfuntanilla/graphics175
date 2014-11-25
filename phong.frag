#version 330

out vec4 fragColor;

uniform int numOfLights;

uniform vec4 lightPos[10];
uniform vec3 eyePos;

uniform float Ia;
uniform float Id[10];
uniform float Is[10];
uniform vec3 IaRGB;
uniform vec3 IdRGB[10];
uniform vec3 IsRGB[10];

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform float n[10];
uniform float attenuationFactor[10];
uniform float lightDistance[10];

in vec4 modelViewPos;
in vec3 N;

void main()
{
    vec3 lightIntensity = vec3(0.0, 0.0, 0.0);

    // ambient term
    vec3 ambient = Ia * IaRGB * Ka;

    for (int i = 0; i < numOfLights; i++) {

        // light direction
        vec3 L = normalize(vec3(lightPos[i] - modelViewPos));

        // N dot L
        float NdotL = max(0.0, dot(N, L));     

        // diffuse term
        vec3 diffuse = Id[i] * IdRGB[i] * Kd * NdotL;

        // view direction
        vec3 V = normalize(-modelViewPos.xyz);

        // reflection
        vec3 R = -normalize(reflect(N, L));

        // specular term
        vec3 specular = vec3(0.0, 0.0, 0.0);
        if (NdotL > 0.0) {
            specular = Is[i] * IsRGB[i] * Ks * pow(max(0.0, dot(R, V)), n[i]);
        }

        float lightAttenuation = 1.0 / (1.0 + attenuationFactor[i] * pow(lightDistance[i], 2));

        // sum up light intensities
        lightIntensity += (ambient + (lightAttenuation * (diffuse + specular)));
    }

    fragColor = vec4(lightIntensity, 1.0);
}
