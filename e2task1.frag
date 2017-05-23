// according GLSL version to OpenGL 3.2 core profile
#version 150 core

uniform sampler2D sprites;

in vec2 v_uv1a;
in vec2 v_uv1b;
in vec2 v_uv2a;
in vec2 v_uv2b;
in float dFrame;
in float dMove;

out vec4 out_color;

void main()
{
	vec4 color1 = mix(texture(sprites, v_uv1a), texture(sprites, v_uv1b), dMove);
	vec4 color2 = mix(texture(sprites, v_uv2a), texture(sprites, v_uv2b), dMove);

    out_color = mix(color1, color2, dFrame);
}
