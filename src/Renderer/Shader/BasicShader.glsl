#shader fragment
#version 330 core

out vec4 fragColor;
in vec4 vertexColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	//fragColor = vertexColor;
    fragColor = texture(ourTexture, TexCoord);
}






#shader vertex
#version 330 core
layout (location = 0) in vec3 inPosition;  // Position attribute
layout (location = 1) in vec4 inColor;     // Color attribute
layout (location = 2) in vec2 inTexture;   // Texture attribute

uniform mat4 Matrix;
out vec4 vertexColor; // Define an output for color to pass to the fragment shader
out vec2 TexCoord;

void main()
{
    gl_Position = Matrix * vec4(inPosition, 1.0);
    vertexColor = inColor; // Assign the color to the output variable
    TexCoord = inTexture;
}