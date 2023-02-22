#VERTEX
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

out vec3 v_surfacenormal;
out vec3 v_lightdirection;
out vec3 v_fagpos;

void main() {
    vec4 worldPos = u_model * vec4(position, 1.0);
    gl_Position = u_projection * u_view * worldPos;

    v_surfacenormal = (u_model * vec4(normal, 0.0)).xyz;
    v_lightdirection = u_lightPos - worldPos.xyz;
    v_fagpos = worldPos.xyz;
}

#FRAGMENT
#version 450 core

uniform vec3 u_lightColor;
uniform vec3 u_viewPos;

in vec3 v_surfacenormal;
in vec3 v_lightdirection;
in vec3 v_fagpos;

out vec4 color;
void main(){
    vec3 normal = normalize(v_surfacenormal);
    vec3 lightDir = normalize(v_lightdirection);
    float dotproduct = dot(lightDir, normal);
    dotproduct = max(dotproduct, 0.0);


    vec3 diffuse = dotproduct * u_lightColor;
    diffuse = diffuse + 0.2;

    float specularStrength = 1.0;
    vec3 viewDir = normalize(u_viewPos - v_fagpos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_lightColor;

    vec3 light = diffuse + specular;
    color= vec4(diffuse, 1.0) * vec4(1.0, 1.0, 1.0, 1.0);
}
