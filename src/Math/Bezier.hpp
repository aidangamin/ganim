#pragma once

#include <array>
#include <glm/detail/qualifier.hpp>


template <typename T, glm::length_t D>
concept GVec = requires {
  typename glm::vec<D, typename T::value_type, T::qualifier>;
  requires std::same_as<T, glm::vec<D, float, T::qualifier>>;
};

template <glm::length_t D, int L>
class NthBezier {
public:
  std::array<glm::vec<D, float>, L> points;

  NthBezier(const std::array<glm::vec<D, float>, L> &p) : points(p) {}

  glm::vec<D, float> evaluate(float t) const {
    std::array<glm::vec<D, float>, L> temp = points;
    for (int k = 1; k < L; ++k)
      for (int i = 0; i < L - k; ++i)
        temp[i] = (1.0f - t) * temp[i] + t * temp[i + 1];
    return temp[0];
  }
};


template <glm::length_t D>
class CubicBezier : public NthBezier<D, 4> {
  glm::vec<D, float> evaluate(float t) const {
    return this->points[0] * ( -(t*t*t) + 3*(t*t) - 3*t + 1 ) +
           this->points[1] * (  3*(t*t*t) - 6*(t*t) + 3*t   ) +
           this->points[2] * ( -3*(t*t*t) + 3*(t*t)         ) +
           this->points[3] * (  (t*t*t)                     );
  }
};

template <glm::length_t D>
class QuadraticBezier : public NthBezier<D, 3> {
};
