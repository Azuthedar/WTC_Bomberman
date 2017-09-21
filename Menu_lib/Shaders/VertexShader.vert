#version 330 core

layout ( location = 0 ) in vec2 position;

out vec2 text_coords;

uniform mat4 transform_mat;

void main()
{
    text_coords = vec2( (position.x + 1.0) / 2.0, 1.0 - (position.y + 1.0) / 2.0 );
    gl_Position = transform_mat * vec4( position, 0.0, 1.0 );
}
