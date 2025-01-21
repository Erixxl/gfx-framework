#version 330


layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec3 vert_normal;
layout (location = 2) in vec2 text_coord;
layout (location = 3) in vec3 vert_color;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


uniform float v_float_aux;
uniform vec3 v_vec_aux;


out vec3 frag_color;
out vec3 camera_position;
out vec4 frag_coord;


vec3 rgb2hsv(vec3 c)
{
	vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
	vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
	vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

	float d = q.x - min(q.w, q.y);
	float e = 1.0e-10;

	return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}


vec3 hsv2rgb(vec3 c)
{
	vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);

	return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{
	vec3 hsv_color = rgb2hsv(vert_color);
	vec3 higher = vec3(hsv_color.x, hsv_color.y, clamp(hsv_color + 0.3, 0.0, 1.0));
	vec3 lower = vec3(hsv_color.x, hsv_color.y, clamp(hsv_color - 0.1, 0.0, 1.0));

	higher = hsv2rgb(higher);
	lower = hsv2rgb(lower);

	frag_color = step(0, vert_position.y) * (1 - step(2.001, vert_position.y)) * higher
		+ (1 - step(0, vert_position.y)) * lower + step(2.001, vert_position.y) * vert_color;

	vec4 new_pos = vec4(vert_position, 1.0);
	gl_Position = Projection * View * Model * new_pos;

	camera_position = v_vec_aux;
	frag_coord = Model * new_pos;
}