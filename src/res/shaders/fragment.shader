#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec4 lightColor;

void main() {
    float ambientStrength = 0.8;
    vec4 ambient = ambientStrength * lightColor;

    vec4 result = ambient * u_Color;
    color = result;
};