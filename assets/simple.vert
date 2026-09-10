#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture_coords;

uniform mat4 model;
out vec2 out_texture_coords;

layout(std140, binding = 0) uniform camera
{
    mat4 view;
    mat4 projection;

};
void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    out_texture_coords = texture_coords;
}