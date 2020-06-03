#version 430

uniform vec4 vertexColor;

out vec4 color;

void main() {
	vec4 textureColor = vec4(1.0,1.0,1.0,1.0);
	color =  textureColor * vertexColor;
	
}