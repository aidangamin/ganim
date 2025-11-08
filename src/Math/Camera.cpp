#include "Math/Camera.hpp"
#include "Types/Angles.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

template <>
Camera<Projection::Orthographic>::Camera
(glm::vec3 pos, glm::vec3 rot, RotationOrder order, glm::ivec2 frame, float near, float far)
  : position(pos), rotation(rot), rot_order(order), frame_size(frame), clip_near(near), clip_far(far)
{
  this->m_proj_matrix = this->m_view_matrix = glm::mat4x4(1);
  this->scale = 1.f;
}

template <>
Camera<Projection::Perspective>::Camera
(glm::vec3 pos, glm::vec3 rot, RotationOrder order, glm::ivec2 frame, float near, float far)
  : position(pos), rotation(rot), rot_order(order), frame_size(frame), clip_near(near), clip_far(far)
{
  this->m_proj_matrix = this->m_view_matrix = glm::mat4x4(1);
  this->field_of_view = glm::radians(90.f);
}

template <>
const glm::mat4x4 &Camera<Projection::Orthographic>::calculateProjectionMatrix() {
  this->m_proj_matrix = glm::mat4x4(1);
  const float aspect_ratio = (float)this->frame_size.x / this->frame_size.y;

  const float rprism_w_2 = aspect_ratio / this->scale * 0.5f;
  const float rprism_h_2 = -0.5f / this->scale;
  this->m_proj_matrix = glm::ortho(-rprism_w_2, rprism_w_2, rprism_h_2, -rprism_h_2, this->clip_near, this->clip_far);

  return this->m_proj_matrix;
}

template <>
const glm::mat4x4 &Camera<Projection::Perspective>::calculateProjectionMatrix() {
  this->m_proj_matrix = glm::mat4x4(1);
  const float aspect_ratio = (float)this->frame_size.x / this->frame_size.y;

  if (aspect_ratio > 1) {
    this->m_proj_matrix = glm::perspectiveFov(
      this->field_of_view, 
      (float)this->frame_size.x, 
      (float)this->frame_size.y, 
      this->clip_near, 
      this->clip_far
    );
  } else {
    this->m_proj_matrix = glm::perspective(
      this->field_of_view, 
      aspect_ratio,
      this->clip_near, 
      this->clip_far
    );
  }

  return this->m_proj_matrix;
}
