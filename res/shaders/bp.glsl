#VERTEX
#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_lightPos;

out vec3 v_normal;
out vec2 v_texCoords;
out vec3 v_lightDirection;
out vec3 v_fragPos;

void main() {
    vec4 worldPos = u_model * vec4(position, 1.0);
    gl_Position = u_projection * u_view * worldPos;

    // output to fragment shader
    v_normal = (u_model * vec4(normal, 0.0)).xyz;
    v_texCoords = texCoords;
    v_lightDirection = u_lightPos - worldPos.xyz;
    v_fragPos = worldPos.xyz;
}

#FRAGMENT
#version 450 core

uniform struct material_s{
    vec3 ambient;
    vec3 diffuse;
    vec3 emissive;
    vec3 specular;
    float shininess;
    float transparency;
    uint illumno;
    // texture
    sampler2D diffuseMap;
    sampler2D specularMap;
} material;

uniform uint u_blinn;
uniform vec3 u_lightColor;
uniform vec3 u_viewPos;
uniform vec3 u_lightPos;

in vec3 v_normal;
in vec2 v_texCoords;
in vec3 v_lightDirection;
in vec3 v_fragPos;

const float screenGamma = 2.2;

out vec4 color;

void main(){
    vec3 ambient = u_lightColor;

    vec3 lightDir = normalize(u_lightPos - v_fragPos);
    vec3 normal = normalize(v_normal);

    vec3 diffuse = max(dot(lightDir,normal), 0.1) * u_lightColor * texture(material.diffuseMap,v_texCoords).rgb * material.diffuse;

    if (material.illumno == 1)
        color = vec4(diffuse,1.0);

    // specular
        vec3 viewDir = normalize(u_viewPos - v_fragPos);
    float spec = 0.0;
    if (u_blinn == 1){
         viewDir = normalize(-u_viewPos - v_fragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    } else {
        vec3 reflectDir = reflect(lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess /4);
    }


    vec3 specular = spec * u_lightColor * material.specular * texture(material.specularMap,v_texCoords).rgb;

    vec3 light = specular + diffuse;
    color = vec4(light, 1.0);
}
