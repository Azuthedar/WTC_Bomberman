#version 330 core

in vec2 Texture_Coordinates_one;
in vec2 Texture_Coordinates_two;
in float blend;

out vec4 colour;

uniform sampler2D particle_texture;

void main()
{
    vec4 colour_one = texture(particle_texture, Texture_Coordinates_one);
    vec4 colour_two = texture(particle_texture, Texture_Coordinates_two);

    colour = mix( colour_one, colour_two, blend );
}
