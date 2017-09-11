#version 330 core

layout ( location = 0 ) in vec2 position;

out vec2 Texture_Coordinates;

uniform mat4 model; // converts locall co-ordinates to camera co-ordinates
uniform mat4 view;	// converts normalized co-ordinates to window co-ordinates

uniform mat4 projection; // converts camera co-ordinates to normalized co-ordinates ( 0 - 1 )

void main()
{
    vec4 world_pos = view * model * vec4( position, 0.0f, 1.0f );
    gl_Position = projection * world_pos;

    Texture_Coordinates = position + vec2(0.5f, 0.5f);
    Texture_Coordinates.y = 1.0f - Texture_Coordinates.y;
}
