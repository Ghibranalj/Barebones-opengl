#VERTEX
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 thecolor;

uniform float u_time;


mat2 rotate2d(float angle)
{
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}


void main() {
    vec2 p = rotate2d(u_time) * vec2(position.x, position.y);
    gl_Position = vec4(p, position.z, 1.0);
    thecolor = color;
}

#FRAGMENT
#version 450 core

in vec4 thecolor;

out vec4 color;

void main(){
    // color = rotate(thecolor, u_time);
    color = thecolor;
}
