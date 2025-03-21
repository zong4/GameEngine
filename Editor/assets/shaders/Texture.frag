#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_Color;

in vec3 v_Position;
in vec2 v_TexCoord;

layout(location = 0) out vec4 color;

void main()
{
    color = texture(u_Texture, v_TexCoord) * u_Color;
}