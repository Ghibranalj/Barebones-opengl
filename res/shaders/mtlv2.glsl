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
out vec2 v_texCoords;
out vec3 v_color;

void main() {
    vec4 worldPos = u_model * vec4(position, 1.0);
    gl_Position = u_projection * u_view * worldPos;

    v_surfacenormal = (u_model * vec4(normal, 0.0)).xyz;
    v_lightdirection = u_lightPos - worldPos.xyz;
    v_fagpos = worldPos.xyz;
    v_texCoords = texCoords;
}

#FRAGMENT
#version 450 core
// material properties
uniform vec3 mat_ambient;
uniform vec3 mat_diffuse;
uniform vec3 mat_emissive;
uniform vec3 mat_specular;
uniform float mat_shininess;
uniform float mat_transparency;
uniform float mat_refractivity;
uniform uint mat_illumno;

uniform vec3 u_lightColor;
uniform vec3 u_viewPos;

in vec3 v_surfacenormal;
in vec3 v_lightdirection;
in vec3 v_fagpos;
in vec2 v_texCoords;

uniform sampler2D u_texture;

out vec4 color;

void main(){

    vec3 ambient = mat_ambient * u_lightColor;

    vec3 normal = normalize(v_surfacenormal);
    vec3 lightDir = normalize(v_lightdirection);
    float dotproduct = dot(lightDir, normal);
    dotproduct = max(dotproduct, 0.1);

    vec3 diffuse = dotproduct * ambient;
   
    diffuse = diffuse * mat_diffuse;

    if (mat_illumno == 1){
        color = vec4(diffuse , 1.0) * texture(u_texture, v_texCoords);
        return;
    }

    vec3 viewDir = normalize(u_viewPos - v_fagpos);
    vec3 reflectDir = reflect(lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat_shininess);
    vec3 specular = u_lightColor * spec * u_lightColor * mat_specular;
    specular = specular * mat_specular;

    vec3 light = diffuse + specular +mat_emissive;
    color= vec4(light, 1.0) * texture(u_texture, v_texCoords);
}
