#shader fragment
#version 330 core

out vec4 fragColor;

uniform sampler2D texture1;

in vec2 texCoord;

void main()
{
    fragColor = texture(texture1, texCoord);
}






#shader vertex
#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 inTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main()
{  
    texCoord = inTextureCoordinates;
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}