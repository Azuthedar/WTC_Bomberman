#version 330 core

out vec4 colour;

in vec2 Texture_Coordinates;

uniform sampler2D particle_texture;

void main()
{
    colour = texture(particle_texture, Texture_Coordinates);
    //colour = vec4( 1.0f );
}
