#version 450

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec2 in_TexCoord;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec3 v_Position;
out vec2 v_TexCoord;

void main()
{
    v_Position = in_Position;
    v_TexCoord = in_TexCoord;
    
    gl_Position = u_ViewProjection * u_Transform * vec4(in_Position, 1.0);
}