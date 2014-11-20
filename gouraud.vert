#version 330

in vec3 posAttr;
in vec3 normAttr;

uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 mvp;

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

out vec3 intensity[10];

void main()
{

    // transform vertex position into eye coordinates
    vec4 modelViewPos = modelViewMatrix * vec4(posAttr, 1.0);

    // transform normal into eye coordinates
    vec3 N = normalize(normalMatrix * normAttr);

    // view direction
    vec3 V = normalize(eyePos - vec3(modelViewPos));

    for (int i = 0; i < numOfLights; i++) {
        // light direction
        vec3 L = normalize(vec3(lightPos[i] - modelViewPos));

        // N dot L
        float NdotL = max(0.0, dot(N, L));

        vec3 specular = vec3(0.0, 0.0, 0.0);
        if (NdotL > 0.0) {

            // reflection
            vec3 R = -normalize(reflect(N, L));

            specular = Is * Ks * pow(max(0, dot(R, V)), n);
        }

        // light intensity
        intensity[i] = (Ia * Ka) + (Id * Kd * NdotL) + specular;

    }



    // final position of the vertex
    gl_Position = mvp * vec4(posAttr, 1.0);

}
