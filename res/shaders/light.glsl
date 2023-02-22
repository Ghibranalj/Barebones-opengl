#VERTEX
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

uniform float u_time;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_lightPos;

out vec3 v_surfacenormal;
out vec3 v_lightdirection;


void main() {
    vec4 worldPos = u_model * vec4(position, 1.0);
    gl_Position = u_projection * u_view * worldPos;

    vec3 surfacenormal = (u_model * vec4(normal, 0.0)).xyz;
    v_surfacenormal = normalize(surfacenormal);
    vec3 lightdir = u_lightPos - worldPos.xyz;
    v_lightdirection = normalize(lightdir);
}

#FRAGMENT
#version 450 core

uniform vec3 u_lightColor;

in vec3 v_surfacenormal;
in vec3 v_lightdirection;

out vec4 color;
void main(){

    float dotproduct = dot(v_surfacenormal, v_lightdirection);
    dotproduct = max(dotproduct, 0.0);

    vec3 diffuse = dotproduct * u_lightColor;

    color= vec4(diffuse, 1.0) * vec4(1.0, 1.0, 1.0, 1.0);
}
