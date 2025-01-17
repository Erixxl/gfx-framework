#version 330


layout (location = 0) out vec4 out_color;


in vec3 frag_color;
in vec4 frag_coord;
in float dist;


const int indexMatrix8x8[64] = int[](0,  32, 8,  40, 2,  34, 10, 42,
									 48, 16, 56, 24, 50, 18, 58, 26,
									 12, 44, 4,  36, 14, 46, 6,  38,
									 60, 28, 52, 20, 62, 30, 54, 22,
									 3,  35, 11, 43, 1,  33, 9,  41,
									 51, 19, 59, 27, 49, 17, 57, 25,
									 15, 47, 7,  39, 13, 45, 5,  37,
									 63, 31, 55, 23, 61, 29, 53, 21);


float indexValue()
{
	int x = int(mod(gl_FragCoord.x, 8));
	int y = int(mod(gl_FragCoord.y, 8));

	return indexMatrix8x8[(x + y * 8)] / 64.0;
}


void main()
{
	vec4 transparent = vec4(frag_color, 0);

	out_color = (indexValue() >= clamp(dist, 0.0, 200.0) / 200.0) ? vec4(frag_color, 1) : transparent;
}