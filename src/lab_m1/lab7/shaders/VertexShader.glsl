#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;


void main()
{
	// TODO(student): Compute world space vectors
	vec3 world_pos = (Model * vec4(v_position, 1)).xyz;
	vec3 world_normal = normalize(mat3(Model) * v_normal);

	vec3 L = normalize(light_position - world_pos);
	vec3 V = normalize(eye_position - world_pos);
	vec3 H = normalize(L + V);
	vec3 R = reflect(-L, world_normal);

	// TODO(student): Define ambient light component
	float ambient_light = 0.25 * material_kd;

	// TODO(student): Compute diffuse light component
	float diffuse_light = material_kd *	max(dot(world_normal, L), 0);

	// TODO(student): Compute specular light component
	// float specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
	float specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);

	if (dot(world_normal, V) <= 0)
	{
		specular_light = 0;
	}

	// TODO(student): Compute light
	float dist = distance(world_pos, light_position);
	float attenuation_factor = 1 / (dist * dist);

	// TODO(student): Send color light output to fragment shader
	color = (ambient_light + attenuation_factor * diffuse_light + attenuation_factor * specular_light) * object_color;

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
