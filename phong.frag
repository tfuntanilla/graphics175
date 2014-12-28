#version 330

out vec4 fragColor;

uniform sampler2D tex;
uniform sampler2D bumpTex;
uniform samplerCube cubeTex;
uniform samplerCube cubeBumpTex;
uniform int mappingType;
uniform int normalMap;
in vec4 texCoord;
in vec2 uvCoord;
in vec3 T;
in vec3 B;

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

uniform float n;
uniform vec3 attenuationFactors[10];
uniform float lightDistance[10];

in vec4 modelViewPos;
in vec3 N;


void main()
{
    vec3 Normal = normalize(N);
    vec3 Tangent = normalize(T);
    vec3 Bitangent = normalize(B);
    //vec3 Bitangent = cross(Tangent, Normal);
    Tangent = normalize(Tangent - dot(Tangent, Normal) * Normal);

    vec3 BumpMapNormal;

    if (mappingType == 0) {
        vec2 sphereCoords = vec2((atan(texCoord.z, texCoord.x) / 3.1415926 + 1.0) * 0.5,
                                      (asin(texCoord.y) / 3.1415926 + 0.5));
        BumpMapNormal = texture(bumpTex, sphereCoords).xyz;
    }
    else if (mappingType == 1) {
        vec2 cylinderCoords = vec2((atan(texCoord.z, texCoord.x) / 3.1415926 + 1.0) * 0.5,
                                   (asin(texCoord.y) / 2 + 0.5));
        BumpMapNormal = texture(bumpTex, cylinderCoords).xyz;
    }
    else if (mappingType == 2) {
        BumpMapNormal = texture(bumpTex, uvCoord).xyz;
    }
    else if (mappingType == 3) {
        BumpMapNormal = texture(cubeBumpTex, texCoord.xyz).xyz;
    }
    else if (mappingType == 4) {
        BumpMapNormal = texture(bumpTex, texCoord.xy).xyz;
    }

    //vec3 BumpMapNormal = texture(bumpTex, texCoord.xy).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = transpose(mat3(Tangent, Bitangent, Normal));
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);

    vec3 lightIntensity = vec3(0.0, 0.0, 0.0);
    float NdotL = 0.0;
    vec3 R;

    // ambient term
    vec3 ambient = Ia * IaRGB * Ka;

    for (int i = 0; i < numOfLights; i++) {

        // light direction
        vec3 L = vec3(0.0, 0.0, 0.0);
        if (lightPos[i].w == 0.0) {
            L = normalize(vec3(lightPos[i]));
        }
        else {
            L = normalize(vec3(lightPos[i] - modelViewPos));
        }

        // N dot L
        if (normalMap == 0) {
          NdotL = max(0.0, dot(N, L));
        }
        else {
          NdotL = max(0.0, dot(NewNormal, L));
        }

        // diffuse term
        vec3 diffuse = Id[i] * IdRGB[i] * Kd * NdotL;

        // view direction
        vec3 V = normalize(-modelViewPos.xyz);

        // reflection
        if (normalMap == 0) {
            R = -normalize(reflect(N, L));
        }
        else {
            R = -normalize(reflect(NewNormal, L));
        }

        // specular term
        vec3 specular = vec3(0.0, 0.0, 0.0);
        if (NdotL > 0.0) {
            specular = Is[i] * IsRGB[i] * Ks * pow(max(0.0, dot(R, V)), n);
        }

        if (lightPos[i].w == 0.0) {
            lightIntensity += (ambient + diffuse + specular);
        }
        else {
            float lightAttenuation = 1.0 / (attenuationFactors[i].x +
                                            lightDistance[i] * attenuationFactors[i].y +
                                            lightDistance[i] * lightDistance[i] * attenuationFactors[i].z);

            // sum up light intensities
            lightIntensity += (ambient + (lightAttenuation * (diffuse + specular)));
        }
    }

    // select texture mapping based on mapping type selected by user
    // and calculate appropriate texture coordinates
    if (normalMap == 1) {
        fragColor = vec4(NdotL, NdotL, NdotL, 1.0);
    }
    else if (mappingType == 0) {
        vec2 sphereCoords = vec2((atan(texCoord.z, texCoord.x) / 3.1415926 + 1.0) * 0.5,
                                      (asin(texCoord.y) / 3.1415926 + 0.5));
        fragColor = texture(tex, sphereCoords);
    }
    else if (mappingType == 1) {
        vec2 cylinderCoords = vec2((atan(texCoord.z, texCoord.x) / 3.1415926 + 1.0) * 0.5,
                                   (asin(texCoord.y) / 2 + 0.5));
        fragColor = texture(tex, cylinderCoords);
    }
    else if (mappingType == 2) {
        fragColor = texture(tex, uvCoord);
    }
    else if (mappingType == 3) {
        fragColor = texture(cubeTex, texCoord.xyz);
    }
    else if (mappingType == 4) {
        fragColor = texture(tex, texCoord.xy);
    }
}


