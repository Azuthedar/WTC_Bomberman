#version 330 core

out vec4 colour;

in vec2 text_coords;

uniform sampler2D texture_bck;

void main()
{
    colour = texture( texture_bck, text_coords );
}
