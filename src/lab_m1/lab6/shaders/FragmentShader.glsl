#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_normal;
in vec2 frag_coord;
in vec3 frag_color;
in vec4 frag_cycle;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
	// TODO(student): Write pixel out color
	out_color = vec4(frag_normal.x * frag_cycle.x, frag_normal.y * frag_cycle.y, frag_normal.z * frag_cycle.z, 1.0f);
	// out_color = vec4(frag_normal, 1.0f);
	// out_color = vec4(frag_position, 1.0f);
	// out_color = vec4(abs(frag_normal, 1.0f));
}
