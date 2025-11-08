#include "Render/Shader.hpp"
#include "glad/gl.h"
#include <Primitives/Triangle.hpp>

Triangle::Triangle(rgb_t color, const std::array<glm::vec3, 3> &points) : points(points) {
  this->color = color;
  // this->points = points;
  this->transformation = glm::mat4x4(1);

  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->pos_vbo);

  glBindVertexArray(this->vao);

  glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
  glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(glm::vec3), this->points.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Triangle::~Triangle() {
  glDeleteBuffers(1, &this->pos_vbo);
  glDeleteVertexArrays(1, &this->vao);
}

void Triangle::drawFilled(Shader *shader) {
  shader->uniform("color", glm::vec4(this->color, 0.25f));
  shader->uniform("transform", this->transformation);
  glBindVertexArray(this->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::drawOutline(Shader *shader) {
  shader->uniform("color", glm::vec4(this->color, 1));
  shader->uniform("transform", this->transformation);
  glBindVertexArray(this->vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
