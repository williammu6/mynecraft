#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in float LightLevel;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
  float opacity;
};

struct Light {
  vec3 ambient;
  vec3 diffuse;
  vec3 direction;
  vec3 position;
  vec3 specular;
};

uniform vec3 cameraPosition;
uniform vec3 viewPos;
uniform Light light;
uniform Material material;

const vec3 ambientColor = vec3(0.3, 0.3, 0.3);

void main() {
  vec4 tex = texture(material.diffuse, TexCoord);
  if (tex.a < 0.01)
    discard;

  vec3 lightDir = vec3(0.5, -0.5, 0.0);
  vec3 lightColor = vec3(1.0, 1.0, 1.0) * LightLevel;
  // Ambient lighting
  vec3 ambient = ambientColor;

  // Diffuse lighting
  vec3 norm = normalize(-Normal);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  // Specular lighting
  float specularStrength = 1.0;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 result = (ambient + diffuse + specular) * tex.rgb;
  FragColor = vec4(result, material.opacity);
}
