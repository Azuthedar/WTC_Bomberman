#version 330 core

layout ( location = 0 ) in vec2 position;

out vec2 Texture_Coordinates_one;
out vec2 Texture_Coordinates_two;
out float blend;

uniform mat4 model; // converts locall co-ordinates to camera co-ordinates
uniform mat4 view;	// converts normalized co-ordinates to window co-ordinates

uniform mat4 projection; // converts camera co-ordinates to normalized co-ordinates ( 0 - 1 )

uniform float NumRows;
uniform float blend_value;
uniform vec2 Offset_vals_one;
uniform vec2 Offset_vals_two;

void main()
{
    vec4 world_pos = view * model * vec4( position, 0.0f, 1.0f );
    gl_Position = projection * world_pos;

    vec2 Texture_Coordinates = position + vec2(0.5f, 0.5f);
    Texture_Coordinates.y = 1.0f - Texture_Coordinates.y;
    Texture_Coordinates /= NumRows;

    Texture_Coordinates_one = Texture_Coordinates + Offset_vals_one;
    Texture_Coordinates_two = Texture_Coordinates + Offset_vals_two;
    blend = blend_value;
}
