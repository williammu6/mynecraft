#version 330 core

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
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main() {
  // ambient
  vec4 ambient = vec4(light.ambient, 1.0) * texture(ourTexture, TexCoord);
  if (ambient.a < 0.2)
    discard;

  // diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

  // specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.3f);
  vec3 specular =
      light.specular * spec * texture(material.specular, TexCoord).rgb;
  // attenuation
  float distance = length(light.position - FragPos) / 750;
  float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  vec3 ambientColor = ambient.rgb;
  FragColor = vec4(ambientColor + diffuse + specular, 1.0);
}
