#shader fragment
#version 330 core

out vec4 fragColor;


uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{


    // Lighting test
    fragColor   = vec4(objectColor * lightColor, 1.0f);
}






#shader vertex
#version 330 core
layout (location = 0) in vec3 inPosition;  // Position attribute


uniform mat4 Matrix;

void main()
{
    gl_Position = Matrix * vec4(inPosition, 1.0);
}