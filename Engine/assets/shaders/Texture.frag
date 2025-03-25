#version 450

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec2 u_TilingFactor;

in vec3 v_Position;
in vec2 v_TexCoord;

layout(location = 0) out vec4 out_color;

void main()
{
    out_color = texture(u_Texture, v_TexCoord * u_TilingFactor) * u_Color;
}