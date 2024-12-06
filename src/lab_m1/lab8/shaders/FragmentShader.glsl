#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform bool is_spotlight;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


vec3 point_light_contribution(vec3 light_pos, vec3 light_color)
{
	vec3 color = vec3(1.0f);

	return color;
}


vec3 spot_light_contribution(vec3 light_pos, vec3 light_color,
	vec3 spot_direction, float cutoff_angle)
{
	vec3 color = vec3(1.0f);

	return color;
}


void main()
{
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	float recv_light = float(dot(world_normal, V) > 0);

	// TODO(student): Define ambient, diffuse and specular light components

	float ambient_light = material_kd * 0.25f;
	float diffuse_light = material_kd * max(dot(world_normal, L), 0);
	float specular_light = material_ks * recv_light * pow(max(dot(world_normal, H), 0), material_shininess);

	float dist = distance(world_position, light_position);
	float attenuation = 1.0f / pow(dist, 2);

	// TODO(student): If (and only if) the light is a spotlight, we need to do
	// some additional things.

	float cutoff_angle = radians(30.0);
	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cutoff_angle);

	float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
	float spot_attenuation = 1.0f;

	if (is_spotlight)
	{
		if (spot_light > cos(cutoff_angle))
		{
			spot_attenuation = pow(linear_att, 2);
		}
		else
		{
			spot_attenuation = 0.0f;
		}
	}

	// TODO(student): Compute the total light. You can just add the components
	// together, but if you're feeling extra fancy, you can add individual
	// colors to the light components. To do that, pick some vec3 colors that
	// you like, and multiply them with the respective light components.

	float light_sum = ambient_light + diffuse_light * attenuation + specular_light * attenuation;
	light_sum *= spot_attenuation;
	vec3 temp_color = object_color;

	// TODO(student): Write pixel out color
	out_color = light_sum * vec4(temp_color, 1.0f);
}
