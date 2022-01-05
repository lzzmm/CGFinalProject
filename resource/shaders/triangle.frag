#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    //FragColor = texture(ourTexture, TexCoord) * vec4(0.4f,0.48f,0.6f,0.8f);
    FragColor = texture(ourTexture, TexCoord) * vec4(0.8f,0.77f,0.45f,0.7f);
}     
