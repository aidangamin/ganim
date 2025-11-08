#pragma once

#include "Types/Color.hpp"
#include <glm/glm.hpp>

// TODO: Implement me (in outline)

struct Outline {
  float progress;
  float radius;
};

class Primitive {
public:
  rgb_t color;
  glm::mat4x4 transformation;
  Outline outline;
};
