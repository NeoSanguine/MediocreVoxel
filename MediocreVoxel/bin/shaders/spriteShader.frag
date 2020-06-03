#version 430


in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;
uniform sampler2D mySampler;
uniform int hit;

void main() {
  
	ivec2 texSize = textureSize(mySampler, 0);
	//float s_offset = (1.0 / (texSize.x));
	//float t_offset = (1.0 / (texSize.y));
	vec2 frag = vec2(fragmentUV.x,fragmentUV.y);
	vec4 textureColor = texture(mySampler,frag);
	color = fragmentColor * textureColor;

	
}