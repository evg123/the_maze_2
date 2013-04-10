#version 330

in vec3 position;
in vec3 in_color;

out vec3 v_f_color;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {
    v_f_color = in_color;
    //v_f_color = vec3(1.0,1.0,0.0);
    gl_Position = proj * view * model * vec4(position, 1.0);
}
