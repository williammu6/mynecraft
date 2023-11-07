#version 330 core

out vec4 FragColor;

uniform sampler2D ourTexture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

void main() {
  vec4 tex = texture(ourTexture, TexCoord);

  if (tex.a < 0.9) discard;

  FragColor = tex;
}
