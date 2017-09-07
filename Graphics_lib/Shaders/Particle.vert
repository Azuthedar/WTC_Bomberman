#version 330 core

in vec2 position;

uniform mat4 projection_matrix;
uniform mat4 mv;

void main()
{
    gl_Position = projection_matrix * mv * vec4( position, 0.0f, 1.0f );
}
