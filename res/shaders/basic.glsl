#VERTEX
#version 450 core
layout (location = 0) in vec3 position;

uniform float u_time;
uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;


mat2 rotate2d(float angle){
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

void main() {
    // vec2 p = rotate2d(u_time) * vec2(position.x, position.y);
    gl_Position = u_projection * u_view * u_model * vec4(position.x,position.y, position.z , 1.0);
    // gl_Position = vec4(position, 1.0);
}

#FRAGMENT
#version 450 core

out vec4 color;
void main(){

    color= vec4(1.0, 1.0, 1.0, 1.0);
}
