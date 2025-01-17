#version 330


layout (location = 0) out vec4 out_color;


in vec3 frag_color;
in float aux;


void main()
{
	float alpha = fract(aux);
	out_color = vec4(frag_color, alpha);
}