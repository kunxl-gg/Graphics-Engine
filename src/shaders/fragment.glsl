#version 330 core

// This is the framgent shader for ambient lighting
// Defining the input and output variables
in vec4 vertexColor;
out vec4 FragColor;

// Considering ambient lighting 
float ambientStrength = 0.1;
vec3 ambient = ambientStrength * lightColor;

// Uniforms for light and Object Color
uniform vec3 lightColor;
uniform vec3 objectColor

void main() {
    vec3 result = ambient * objectColor;
    vec3 resultant = (ambient) * objectColor;
    FragColor = vec4(result, 1.0);
}
