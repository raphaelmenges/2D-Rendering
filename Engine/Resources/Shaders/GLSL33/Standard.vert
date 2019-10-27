#version 330 core

#custom_defines

uniform mat4 modelMatrix;
uniform mat4 projectionViewMatrix;
in vec3 vertex;
in vec2 textureCoordinate;
out vec2 uv;
out vec2 pos;

void main ()
{
	uv = textureCoordinate;
	pos = vertex.xy;
	gl_Position = projectionViewMatrix * modelMatrix * vec4(vertex, 1.0);
}