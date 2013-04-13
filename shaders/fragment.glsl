#version 330

in vec3 v_f_pos_cs;
in vec3 v_f_norm_cs;
in vec3 v_f_color_diffuse;

// maybe convert to uniforms later
const vec4 light_amt = vec4(2.5, 2.5, 2.5, 1.0);
const vec4 v_f_ambient_amt = vec4(0.3, 0.3, 0.3, 1.0);

uniform vec3 light_pos_cs;

out vec4 out_color;

void main() {
    
    vec3 light_diff = light_pos_cs - v_f_pos_cs;
    float light_dist_sqr = dot(light_diff, light_diff);
    vec3 light_dir = light_diff * inversesqrt(light_dist_sqr);
    
    vec4 light_amt_atten = light_amt * (1 / (1.0 + .008 * sqrt(light_dist_sqr)));
    
    float angle = dot(normalize(v_f_norm_cs), light_dir);
    angle = clamp(angle, 0, 1);
    
    out_color = (v_f_ambient_amt * vec4(v_f_color_diffuse, 1.0)) + (light_amt_atten * angle * vec4(v_f_color_diffuse, 1.0));
    
}
