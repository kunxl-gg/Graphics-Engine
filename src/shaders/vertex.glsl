#version 330 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 acolor;

out vec3 color;

uniform mat4 model;

void main() {
    color = acolor;
    vec4 resultantPosition = model * vec4(position, 1.0f);
    gl_Position = resultantPosition;
}
