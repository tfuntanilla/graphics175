#version 330

in vec4 posAttr;
in vec3 normAttr;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 mvp;

uniform int numOfLights;

uniform vec3 eyePos;
uniform vec4 lightPos[10];

uniform float Ia[10];
uniform float Id[10];
uniform float Is[10];
uniform vec3 IaRGB[10];
uniform vec3 IdRGB[10];
uniform vec3 IsRGB[10];

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform float n[10];

out vec3 lightIntensity[10];

void main()
{
    for (int i = 0; i < numOfLights; i++) {
        // position in model view
        vec4 modelViewPos = modelViewMatrix * posAttr;

        vec3 ambient = Ia[i] * IaRGB[i] * Ka;

        // normals in model view
        vec3 N = normalize(normalMatrix * normAttr);
        // light direction
        vec3 L = normalize(vec3(lightPos[i] - modelViewPos));
        // N dot L
        float NdotL = max(0.0, dot(N, L));
        vec3 diffuse = Id[i] * IdRGB[i] * Kd * NdotL;

        // view direction
        vec3 V = normalize(-modelViewPos.xyz);
        // reflection
        vec3 R = -normalize(reflect(N, L));
        vec3 specular = vec3(0.0, 0.0, 0.0);
        if (NdotL > 0.0) {
            specular = Is[i] * IsRGB[i] * Ks * pow(max(0, dot(R, V)), n[i]);
        }

        // light intensity
        lightIntensity[i] = ambient + diffuse + specular;

    }

    // final position of the vertex
    gl_Position = mvp * posAttr;

}
