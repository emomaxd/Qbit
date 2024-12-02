#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjection;
};

layout (location = 0) out vec4 o_Color;
layout (location = 1) out vec2 o_TexCoord;
layout (location = 2) out flat int o_EntityID;

void main()
{
    o_Color = a_Color;
    o_TexCoord = a_TexCoord;
    o_EntityID = a_EntityID;

    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

layout (location = 0) in vec4 Input_Color;
layout (location = 1) in vec2 Input_TexCoord;
layout (location = 2) in flat int v_EntityID;

layout (binding = 0) uniform sampler2D u_FontAtlas;

float screenPxRange() {
    const float pxRange = 2.0;
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(Input_TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    vec4 texColor = Input_Color * texture(u_FontAtlas, Input_TexCoord);

    vec3 msd = texture(u_FontAtlas, Input_TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    if (opacity == 0.0)
        discard;

    vec4 bgColor = vec4(0.0);
    o_Color = mix(bgColor, Input_Color, opacity);
    if (o_Color.a == 0.0)
        discard;
    
    o_EntityID = v_EntityID;
}
