#version 450 core //for openGL version 4.5

in vec4 vertex_color;
in vec2 texCoords;

layout (location = 0) out vec4 outColor;
//uniform sampler2D texture1;

void main(){
    outColor = vertex_color; //* texture(texture1, texCoords);
}
