#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out vec2 TexCoords;


void main()
{ 
    gl_Position = vec4(aPos, 1.0);
    TexCoords = aTexCoords;
}