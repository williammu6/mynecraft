#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragPos;  
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection;

void main() {
  TexCoord = aTexCoord;
  gl_Position = model * projection *  vec4(aPos.x, aPos.y, 0.0, 1.0);
  // Normal = aNormal;
}