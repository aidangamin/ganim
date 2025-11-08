#pragma once

#include <array>
#include <glad/gl.h>
#include <glm/ext/vector_float3.hpp>

#include "Primitives/Primitive.hpp"
#include "Render/Shader.hpp"

class Triangle: public Primitive {
private:
  unsigned int vao, pos_vbo;
public:
  std::array<glm::vec3, 3> points;

  Triangle(glm::vec3 color, const std::array<glm::vec3, 3>& points);
  ~Triangle();

  void drawFilled(Shader *shader);
  void drawOutline(Shader *shader);
};
