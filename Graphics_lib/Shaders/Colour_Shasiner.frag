#version 330 core

in vec2 textures;
in vec3 surface_normal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 colour;

uniform sampler2D Texture_;
uniform vec3 light_colour;
uniform float shine_damper;
uniform float reflection;

void main( )
{
	vec3 unit_normal = normalize(surface_normal);
	vec3 unit_light_vect = normalize(toLightVector);

	float nDot1 = dot( unit_normal, unit_light_vect );
	float Brightness = max( nDot1, 0.2);
	vec3 diffuse = Brightness * light_colour;

	vec3 unit_camera_vect = normalize(toCameraVector);
	vec3 light_dir = -unit_light_vect;
	vec3 reflected_light = reflect( light_dir, unit_normal );

	float specular_factor = dot( reflected_light, unit_camera_vect );
	specular_factor = max( specular_factor, 0.0f );
	float damp_factor = pow( specular_factor, shine_damper );
	vec3 final_specular = damp_factor * reflection * light_colour;

	colour = vec4( diffuse, 1.0f)  * texture( Texture_ , textures ) + vec4( final_specular, 1.0f );
}
