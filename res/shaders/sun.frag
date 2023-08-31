#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
  vec4 ambient = texture(ourTexture, TexCoord);
  if (ambient.a < 0.1) discard;

  vec3 color = ambient.rgb;
  FragColor = vec4(color, 1.0);
}
