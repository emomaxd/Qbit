#shader fragment
#version 330 core

out vec4 fragColor;


void main()
{
    fragColor   = vec4(1.0f);
}






#shader vertex
#version 330 core
layout (location = 0) in vec3 inPosition;  // Position attribute


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{  
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}