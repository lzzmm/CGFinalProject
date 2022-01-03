#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);// * vec4(ourColor, 1.0f);
    //FragColor = vec4(1.0f,0.5f,0.7f,0.8f);
}     
