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
out vec4 frag_coord;
out float dist;


void main()
{
	float x_pos = vert_position.x;
	float y_pos = vert_position.y;
	float z_pos = vert_position.z;

	// Check if the vertex belongs to a spinning blade
	float is_blade = step(1.01, y_pos) * (1 - step(2, y_pos));

	// Rotation angle and translation steps
	float alpha = v_float_aux;

	float tx = step(-4.5, z_pos) * (1 - step(4.5, z_pos))
		* (-9 * step(4.49, x_pos) + 9 * (1 - step(-4.49, x_pos)));
	float tz = step(-4.5, x_pos) * (1 - step(4.5, x_pos))
		* (-9 * step(4.49, z_pos) + 9 * (1 - step(-4.49, z_pos)));

	// Blade rotation matrix - rotation around the y axis
	mat4 blade_rotation;
	blade_rotation[0] = vec4(cos(alpha * is_blade), 0, sin(alpha * is_blade), 0);
	blade_rotation[1] = vec4(0, 1, 0, 0);
	blade_rotation[2] = vec4(-sin(alpha * is_blade), 0, cos(alpha * is_blade), 0);
	blade_rotation[3] = vec4(0, 0, 0, 1);
	blade_rotation = transpose(blade_rotation);

	// Translation matrix - move the blade vertices to the model origin before rotation
	mat4 blade_translation;
	blade_translation[0] = vec4(1, 0, 0, tx * is_blade);
	blade_translation[1] = vec4(0, 1, 0, 0);
	blade_translation[2] = vec4(0, 0, 1, tz * is_blade);
	blade_translation[3] = vec4(0, 0, 0, 1);
	blade_translation = transpose(blade_translation);

	mat4 blade_inverse = inverse(blade_translation);

	mat4 blade_tr = blade_inverse * blade_rotation * blade_translation;

	// Final position
	vec4 new_pos = vec4(vert_position, 1.0);
	new_pos = ((1 - is_blade) * mat4(1) + is_blade * blade_tr) * new_pos;

	gl_Position = Projection * View * Model * new_pos;

	dist = v_vec_aux.x;
	frag_color = vert_color;
	frag_coord = Model * new_pos;
}