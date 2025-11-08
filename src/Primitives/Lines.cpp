#include "Lines.hpp"
#include "glad/gl.h"
#include <glm/geometric.hpp>

// Goal:
//  - Create a line and then transform them before the vertex shader (make sure the thickness stays consistent)

LineSegment::LineSegment(glm::vec3 color, const glm::vec3 &p1, const glm::vec3 &p2, Caps cap, float radius) : points({p1, p2}), radius(radius), cap(cap), color(color)
{
  this->color = color;

  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->pos_vbo);

  glBindVertexArray(this->vao);

  glm::vec3 tangent = glm::normalize(p2 - p1);
  glm::vec3 up = (fabs(tangent.z) < 0.999f) ? glm::vec3(0, 0, 1) : glm::vec3(0, 1, 0);
  glm::vec3 normal = glm::normalize(glm::cross(up, tangent));
  glm::vec3 bitangent = glm::cross(tangent, normal);

  std::array<glm::vec3, 4> vertData = {
    p1 - radius * normal - radius * bitangent,
    p1 + radius * normal - radius * bitangent,
    p2 + radius * normal + radius * bitangent,
    p2 - radius * normal + radius * bitangent,
  };


  glBindBuffer(GL_ARRAY_BUFFER, this->pos_vbo);
  glBufferData(GL_ARRAY_BUFFER, vertData.size() * sizeof(glm::vec3), vertData.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

LineSegment::~LineSegment() {
  glDeleteBuffers(1, &this->pos_vbo);
  glDeleteVertexArrays(1, &this->vao);
}

void LineSegment::draw(Shader *shader) {
  shader->uniform("color", glm::vec4(this->color, 1));
  glBindVertexArray(this->vao);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
