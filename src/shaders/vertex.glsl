#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 acolor;
layout(location = 2) in vec2 texCoord;

out vec3 color;
out vec2 TexCoord;

uniform mat4 model;

void main() {
    color = acolor;
    TexCoord = texCoord;
    vec4 resultantPosition = model * vec4(position, 1.0f);

    gl_Position = resultantPosition;
}
