#version 330 core

#custom_defines

uniform sampler2D diffuse;
uniform vec4 diffuseMultiplier;
in vec2 uv;
in vec2 pos;
out vec4 frag_colour;

void main ()
{
	vec4 color = diffuseMultiplier * texture(diffuse, uv);
	
	#if defined(USE_DISCARD)
		if((color.a-0.25) < 0)
		{
			discard;
		}
	#endif
	
	frag_colour = color;
}