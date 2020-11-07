#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 lightPosition;
layout(location = 4) in vec3 lightColor;
layout(location = 5) in float lightStrenght;
layout(location = 6) in float lightSpecular;
layout(location = 7) in vec3 fragPosition;
layout(location = 8) in vec3 cameraPosition;

layout(location = 0) out vec4 outColor;

void main() {
    //outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, 1.0);
    //outColor = vec4(texture(texSampler, fragTexCoord).rgb, 1.0);
    //outColor = texture(texSampler, fragTexCoord);
    //outColor = vec4(fragColor, 1.0);

    vec3 objectColor = fragColor * texture(texSampler, fragTexCoord).rgb;

    //
    // ambient light
    vec3 ambient = lightStrenght * lightColor;

    //
    // diffuse light
    vec3 norm = normalize(fragNormal);
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * lightColor;

    //
    // specular
    vec3 viewDir = normalize(cameraPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDirection, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = lightSpecular * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    outColor = vec4(result, 1.0);
}