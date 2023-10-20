#version 440 core

out vec4 FragColor;
in vec2 fragTexCoord;
uniform sampler2D sampleTexture;

void main()
{
	vec4 textureColor = texture(sampleTexture, fragTexCoord);

	if (textureColor.a < 0.1)
		discard;

	FragColor = textureColor; 
}
