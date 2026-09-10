#version 460 core

out vec4 frag_color;
in vec2 out_texture_coords;
uniform sampler2D sampler;

void main()
{
    frag_color = texture(sampler, out_texture_coords);
}