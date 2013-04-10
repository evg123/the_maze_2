#version 330

in vec3 position;
in vec3 normal;
in vec3 in_color;

out vec3 v_f_pos;
out vec3 v_f_norm;
out vec3 v_f_color_diffuse;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 vert_model;
uniform mat4 norm_model;

void main() {
    gl_Position = proj * view * vert_model * vec4(position, 1.0);
    
    v_f_pos = (view * vert_model * vec4(position, 1.0)).xyz;
    v_f_norm = (view * norm_model * vec4(normal, 0.0)).xyz;
    v_f_color_diffuse = in_color;
}
