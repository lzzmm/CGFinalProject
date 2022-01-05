#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float shininess = 32.0;
uniform float ambientStrength = 0.2;
uniform float diffuseStrength = 1.0;
uniform float specularStrength = 0.5;
uniform float constant = 1.0;
uniform float linear = 0.0014;
uniform float quadratic = 0.000007;

void main()
{
    // ambient
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseStrength * lightColor;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); // Phong
    vec3 halfDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(halfDir, norm), 0.0), shininess); // Blinn Phong
    vec3 specular = specularStrength * spec * lightColor;
    
    float distance = length(FragPos - lightPos);
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    vec3 result = ambient + diffuse * attenuation + specular * attenuation;
    FragColor = vec4(result, 1.0) * texture(ourTexture, TexCoord);
}