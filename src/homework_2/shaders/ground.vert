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


out float rand_value;
out vec3 camera_position;
out vec4 frag_coord;


// "Random" value generator
float random(in vec2 st)
{
	return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}


void main()
{
	// Generate a random value
	vec2 seed = vert_position.xz; // * fract(v_float_aux);
	float rand_val = random(seed); // (0; 1)

	// Compute the new vertex position
	vec4 new_pos = vec4(vert_position.x, rand_val * 2.0, vert_position.z, 1.0);

	// Send the random value and position to the fragment shader
	rand_value = rand_val;
	camera_position = v_vec_aux;
	frag_coord = Model * new_pos;

	gl_Position = Projection * View * Model * new_pos;
}