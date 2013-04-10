#version 330

in vec3 v_f_color;

out vec4 out_color;

void main() {
    out_color = vec4(v_f_color, 1.0);
    //out_color = vec4(0.0,0.3,0.5, 1.0);
}
