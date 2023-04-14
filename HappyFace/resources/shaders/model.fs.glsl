#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_filter;
uniform vec4 value;

void main()
{   
    FragColor = mix(texture(texture_diffuse1, TexCoords), texture(texture_filter, TexCoords), 0.0) * value;
}
