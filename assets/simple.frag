#version 460 core

out vec4 frag_color;
in vec2 o_texture_coords;
in vec3 o_normal;
in vec4 frag_pos;
uniform sampler2D tex0;
uniform sampler2D tex1;

layout(std140, binding = 0) uniform camera
{
    mat4 view;
    mat4 projection;
    vec3 camera_position;

};

layout(std140, binding = 1) uniform lights
{
    vec3 ambient;
    vec3 direction;
    vec3 direction_color;
    vec3 point_pos;
    vec3 point_color;
};

vec4 calculate_ambient()
{
    return vec4(ambient, 1.0f);
}

vec4 calculate_direction()
{
    vec3 ligth_dir = normalize(-direction);
    float diff =  max(dot(o_normal, ligth_dir), 0.0f);
    vec4 dir_color = vec4(direction_color * diff, 1.0f);
    return dir_color;
}

vec4 calculate_point()
{
    vec3 ligth_dir = normalize(point_pos - frag_pos.xyz);
    float diff = max(dot(ligth_dir, o_normal), 0.0f) * 10.0f;
    vec3 reflected_dir = reflect(-ligth_dir, o_normal);
    vec3 camera_dir = normalize(camera_position - frag_pos.xyz);
    float spec = pow(max(dot(reflected_dir, camera_dir), 0.0f), 32) * (50 *texture(tex1, o_texture_coords).r);
    return vec4((diff + spec) / length(point_pos - frag_pos.xyz)  * point_color, 1.0f);
}


void main()
{
    vec4 ambient_color = calculate_ambient();
    vec4 dir_color = calculate_direction();
    vec4 point_color = calculate_point();
    frag_color = (ambient_color +  dir_color + point_color) * texture(tex0, o_texture_coords);
}