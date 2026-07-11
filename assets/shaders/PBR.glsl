#type vertex
#version 460


layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} vs_out;

layout(std140, binding = 0) uniform CameraData {
    vec3 ViewPos;
    mat4 ViewProj;
};
uniform mat4 uModel;

void main() {
    vs_out.TexCoord = aTexCoord;
    vs_out.Normal = mat3(transpose(inverse(uModel))) * aNormal;

    gl_Position = ViewProj * uModel * vec4(aPosition, 1.0);
    vs_out.FragPos = vec3(uModel * vec4(aPosition, 1));
}



#type fragment
#version 460

layout (location = 0) out vec4 FragColor;


struct DirLight {
    vec4 dir;
    vec4 color;
};

struct PointLight {
    vec4 Position;
    vec4 Color;

    float Constant;
    float Linear;
    float Quadratic;
};


const int MAX_POINT_LIGHTS = 32;
const float PI = 3.14159265359;


in VS_OUT{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} fs_in;


layout (binding = 0) uniform sampler2D uAlbedoMap;       //Slot 0


layout(std140, binding = 0) uniform CameraData {
    vec3 ViewPos;
    mat4 ViewProj;
};

layout(std140, binding = 1) uniform LightingData {
    DirLight uDirLight;
    PointLight uPointLights[MAX_POINT_LIGHTS];
    int uNumPointLights;
};


uniform vec3 uColor;

uniform float uShininess;
uniform float uMetallic;
uniform float uRoughness;


vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main() {
    vec3 N = normalize(fs_in.Normal);
    vec3 viewDir = normalize(ViewPos - fs_in.FragPos);
    vec3 albedo = uColor;

    const float LightIntensity = 100.0f;

    vec3 Lo = vec3(0);
    for(int i = 0; i < uNumPointLights; i++) {
        vec3 lightDir = normalize(uPointLights[i].Position.xyz - fs_in.FragPos);
        vec3 halfway = normalize(viewDir + lightDir);

        float distance = length(uPointLights[i].Position.xyz - fs_in.FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = uPointLights[i].Color.xyz * attenuation * LightIntensity;

        vec3 F0 = vec3(0.04);
        F0 = mix(F0, albedo, uMetallic);
        vec3 F = fresnelSchlick(max(dot(halfway, viewDir), 0), F0);

        float NDF = DistributionGGX(N, halfway, uRoughness);
        float G = GeometrySmith(N, viewDir, lightDir, uRoughness);

        //0.0001 to prevent divide by zero
        vec3 num = NDF * G * F;
        float denom = 4.0 * max(dot(N, viewDir), 0.0) * max(dot(N, lightDir), 0.0) + 0.0001;
        vec3 specular = num / denom;

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        kD *= 1.0 - uMetallic;

        float NdotL = max(dot(N, lightDir), 0.0);
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * albedo;
    vec3 color = ambient + Lo;

    //gamma correction
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1);
}