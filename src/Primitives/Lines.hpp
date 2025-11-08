#pragma once

#include "Render/Shader.hpp"
#include "Types/Color.hpp"
#include <glad/gl.h>
#include <glm/glm.hpp>

// Goal:
//  - Create a line and then transform them before the vertex shader (make sure the thickness stays consistent)

enum Joints {
  JRound,
  JBevel,
  JMiter
};

enum Caps {
  CCircle,
  CTriangle,
  CSquare,
  CNone,
};

class LineSegment {
private:
  unsigned int vao, pos_vbo;

public:
  std::array<glm::vec3, 2> points;
  float radius;
  // Joints joint;
  Caps cap;
  rgb_t color;
  
  LineSegment(glm::vec3 color, const glm::vec3 &p1, const glm::vec3 &p2, Caps cap = Caps::CCircle, float radius = 3);
  ~LineSegment();

  void draw(Shader *shader);
};
