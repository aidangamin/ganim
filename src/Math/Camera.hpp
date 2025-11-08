#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <Types/Angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

enum Projection {
  Orthographic,
  Perspective,
};

template <Projection P>
struct CameraProjectionParamAlias;

template <> struct 
CameraProjectionParamAlias<Projection::Perspective> {
  radians_t field_of_view = glm::degrees(60.0f);
};

template <> struct 
CameraProjectionParamAlias<Projection::Orthographic> {
  float scale = 1.0f;
};

template <Projection P>
class Camera: public CameraProjectionParamAlias<P> {
private:
  glm::mat4x4 m_view_matrix;
  glm::mat4x4 m_proj_matrix;

public:
  glm::vec3 position;
  glm::vec3 rotation;
  RotationOrder rot_order;

  glm::ivec2 frame_size;
  float clip_near, clip_far;

  Camera(glm::vec3 pos = glm::vec3(0), glm::vec3 rot = glm::vec3(0), RotationOrder order = RotationOrder::XYZ, glm::ivec2 frame = glm::ivec2(800, 600), float near = 0.1f, float far = 100.f);
  ~Camera() {}

  const glm::mat4x4 &calculateViewMatrix() {
    this->m_view_matrix = glm::mat4x4(1);

    switch (this->rot_order) {
      case RotationOrder::XYZ:
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.x, glm::vec3(1, 0, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.y, glm::vec3(0, 1, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.z, glm::vec3(0, 0, 1));
        break;
      case RotationOrder::YXZ:
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.y, glm::vec3(0, 1, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.x, glm::vec3(1, 0, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.z, glm::vec3(0, 0, 1));
        break;
      case RotationOrder::ZXY:
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.z, glm::vec3(0, 0, 1));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.x, glm::vec3(1, 0, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.y, glm::vec3(0, 1, 0));
        break;
      case RotationOrder::ZYX:
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.z, glm::vec3(0, 0, 1));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.y, glm::vec3(0, 1, 0));
        this->m_view_matrix = glm::rotate(this->m_view_matrix, -this->rotation.x, glm::vec3(1, 0, 0));
        break;
    }

    this->m_view_matrix = glm::translate(this->m_view_matrix, this->position);
    return this->m_view_matrix;
  }

  const glm::mat4x4 &calculateProjectionMatrix();
};
