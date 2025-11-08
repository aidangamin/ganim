#include "Render/Shader.hpp"
#include "Utils/logging.h"

#include "glad/gl.h"

#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>

Shader::~Shader() {
  glDeleteShader(this->m_vertex_shader);
  glDeleteShader(this->m_fragment_shader);
  glDeleteProgram(this->m_program);
}

Shader::Shader() {
  int success = 0;
  char status[512];
  this->m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  const char *vertex_shader_cstr = DEFAULT_3D_VSH.c_str();
  glad_glShaderSource(this->m_vertex_shader, 1, &vertex_shader_cstr, NULL);
  glCompileShader(this->m_vertex_shader);

  glGetShaderiv(this->m_vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->m_vertex_shader, sizeof(status), NULL, status);
    log_error("Failed to compile vertex shader:\n%s", status);
  }

  const char *fragment_shader_cstr = DEFAULT_3D_FSH.c_str();
  this->m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->m_fragment_shader, 1, &fragment_shader_cstr, NULL);
  glCompileShader(this->m_fragment_shader);

  glGetShaderiv(this->m_fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->m_fragment_shader, sizeof(status), NULL, status);
    log_error("Failed to compile fragment shader:\n%s", status);
  }

  this->m_program = glCreateProgram();
  glAttachShader(this->m_program, this->m_vertex_shader);
  glAttachShader(this->m_program, this->m_fragment_shader);

  glLinkProgram(this->m_program);

  glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_program, sizeof(status), NULL, status);
    log_error("Failed to link shader program:\n%s", status);
  }
}

Shader::Shader(const std::string& vert_shader_source, const std::string& frag_shader_source) {
  int success = 0;
  char status[512];
  this->m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);

  const char *vertex_shader_cstr = vert_shader_source.c_str();
  glad_glShaderSource(this->m_vertex_shader, 1, &vertex_shader_cstr, NULL);
  glCompileShader(this->m_vertex_shader);

  glGetShaderiv(this->m_vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->m_vertex_shader, sizeof(status), NULL, status);
    log_error("Failed to compile vertex shader:\n%s", status);
  }

  const char *fragment_shader_cstr = frag_shader_source.c_str();
  this->m_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->m_fragment_shader, 1, &fragment_shader_cstr, NULL);
  glCompileShader(this->m_fragment_shader);

  glGetShaderiv(this->m_fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(this->m_fragment_shader, sizeof(status), NULL, status);
    log_error("Failed to compile fragment shader:\n%s", status);
  }

  this->m_program = glCreateProgram();
  glAttachShader(this->m_program, this->m_vertex_shader);
  glAttachShader(this->m_program, this->m_fragment_shader);

  glLinkProgram(this->m_program);

  glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(this->m_program, sizeof(status), NULL, status);
    log_error("Failed to link shader program:\n%s", status);
  }
}
