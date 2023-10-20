#version 440 core

out vec4 FragColor;
in vec2 fragTexCoord;
uniform sampler2D sampleTexture;
uniform vec2 offset;

void main()
{
	vec4 textColor = texture(sampleTexture, fragTexCoord + offset);
	if (textColor.a < 0.1)
		discard;
	FragColor = textColor;
}
