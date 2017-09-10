#version 330 core

layout ( location = 0 )  in vec3 position;

uniform mat4 model; // converts locall co-ordinates to camera co-ordinates
uniform mat4 view;	// converts normalized co-ordinates to window co-ordinates

void main()
{
    gl_Position = view * model * vec4( position, 1.0f );
}
