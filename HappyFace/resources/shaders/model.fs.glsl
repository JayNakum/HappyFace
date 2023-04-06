#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

// uniform vec4 add_value;
// uniform vec4 mul_value;

void main()
{   
    // FragColor = texture(texture_diffuse1, TexCoords) + add_value;
    // FragColor = texture(texture_diffuse1, TexCoords) * mul_value;

    FragColor = texture(texture_diffuse1, TexCoords);
}
