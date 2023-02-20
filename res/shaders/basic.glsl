#VERTEX
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 thecolor;
out vec2 thetexCoord;

uniform float u_time;


mat2 rotate2d(float angle)
{
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}


void main() {
    vec2 p = rotate2d(u_time) * vec2(position.x, position.y);
    gl_Position = vec4(p, position.z, 1.0);
    thecolor = color;
    thetexCoord = texCoord;
}

#FRAGMENT
#version 450 core

in vec4 thecolor;
in vec2 thetexCoord;

out vec4 color;

uniform sampler2D u_texture;

void main(){

    color = thecolor * texture(u_texture, thetexCoord);

}
