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


out vec3 camera_position;
out vec4 frag_coord;


void main()
{
	vec4 new_pos = vec4(vert_position, 1.0);
	gl_Position = Projection * View * Model * new_pos;

	camera_position = v_vec_aux;
	frag_coord = Model * new_pos;
}