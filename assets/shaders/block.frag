#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
  float opacity;
};

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
  vec3 direction;
  float constant;
  float linear;
  float quadratic;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;

void main() {
  vec4 tex = texture(material.diffuse, TexCoord);
  if (tex.a < 0.1) discard;
  // ambient
  vec3 ambient = light.ambient * tex.rgb;

  // diffuse
  vec3 norm = normalize(Normal);
  //vec3 lightDir = normalize(light.position - FragPos);
  vec3 lightDir = normalize(light.direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

  // specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular =
      light.specular * spec * texture(material.specular, TexCoord).rgb;

  vec3 result = ambient + diffuse + specular;
  // FragColor = vec4(result, material.opacity);
  FragColor = vec4(tex.rgb, material.opacity);
}
