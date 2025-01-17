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
out float aux;


void main()
{
	gl_Position = Projection * View * Model * vec4(vert_position, 1.0);

	frag_color = vec3(1.0);
	aux = v_float_aux;
}
