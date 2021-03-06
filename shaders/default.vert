#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(push_constant) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 pos;
    vec3 color;
    float strenght;
    float specular;
    vec3 cameraPosition;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 lightPosition;
layout(location = 4) out vec3 lightColor;
layout(location = 5) out float lightStrenght;
layout(location = 6) out float lightSpecular;
layout(location = 7) out vec3 fragPos;
layout(location = 8) out vec3 cameraPosition;

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    lightPosition = ubo.pos;
    lightColor = ubo.color;
    lightStrenght = ubo.strenght;
    lightSpecular = ubo.specular;
    fragPos = vec3(ubo.model * vec4(inPosition, 1.0));
    cameraPosition = ubo.cameraPosition;
}