#type fragment
#version 330 core

out vec4 fragColor;

void main()
{
    fragColor   = vec4(0.8, 0.2, 0.3, 1);
}






#type vertex
#version 330 core
layout (location = 0) in vec3 inPosition;  // Position attribute


uniform mat4 Matrix;

void main()
{
    gl_Position = vec4(inPosition, 1.0);
}