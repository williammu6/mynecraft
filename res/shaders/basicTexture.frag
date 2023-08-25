# version 330 core

out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;

uniform sampler2D ourTexture;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main()
{
    vec4 ambient = vec4(light.ambient, 1.0) * texture(ourTexture, TexCoord);
    if (ambient.a < 0.1)
        discard;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.3f);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;  

    vec3 ambientColor = ambient.rgb;
    FragColor = vec4(ambientColor + diffuse + specular, 1.0);
}
