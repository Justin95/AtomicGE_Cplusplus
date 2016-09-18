#version 450 core //for openGL version 4.5

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec4 color;

out vec4 vertex_color;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    vertex_color = color;
    texCoords = textureCoords;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
