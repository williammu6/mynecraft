#version 330 core

out vec4 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec2 position;
uniform vec2 rayOrigin;
uniform vec2 rayDirection;

void main() {
  vec2 endpoint = rayOrigin + rayDirection;
  // gl_Position = projection * view * model * vec4(position, 1.0);
  gl_Position = vec4(position == vec2(0.0) ? rayOrigin : endpoint, 0.0, 1.0);
  FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color for the ray, adjust as needed
}
