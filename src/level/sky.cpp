// #include "sky.hpp"

// void Sky::init() {
//   // glGenVertexArrays(1, &VAO);
//   // glGenBuffers(1, &VBO);
//   // glGenBuffers(1, &EBO);
// }

// void Sky::render() {
//   float vertices[] = {
//       -0.5f, -0.5f, 0.0f,
//       0.5f, -0.5f, 0.0f,
//       0.0f, 0.5f, 0.0f};

//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//   glEnableVertexAttribArray(0);

//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//   // 1. then set the vertex attributes pointers
//   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//   glEnableVertexAttribArray(0);
//   glBindVertexArray(VAO);

//   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
// }

// void Sky::update() {

// }