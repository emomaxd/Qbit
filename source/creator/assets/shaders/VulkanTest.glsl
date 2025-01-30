#type vertex
#version 450

layout(location = 0) out vec3 fragColor;

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

void main() {
    gl_Position = vec4(a_Position, 0.0, 1.0);
    
    // Use position to dynamically change color (e.g., based on X or Y position)
    fragColor = a_Color * (sin(a_Position.x * 3.14159) * 0.5 + 0.5);  // Modifying color based on X position
}



#type fragment
#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);  // Output the color calculated in the vertex shader
}
