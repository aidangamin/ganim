#pragma once

#include "Utils/Preproc.hpp"

#include <format>
#include <glad/gl.h>
#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>


inline const std::string DEFAULT_2D_VSH =  GLSL_VERSION_STRING "\n"
                                        "layout (location = 0) in vec2 aPos;\n"
                                        "void main() {\n"
                                          "gl_Position = vec4(aPos, 0, 1);\n"
                                        "}";

inline const std::string DEFAULT_3D_VSH =  GLSL_VERSION_STRING "\n"
                                        "layout (location = 0) in vec4 aPos;\n"
                                        "uniform mat4 projection = mat4(1);\n"
                                        "uniform mat4 transform = mat4(1);\n"
                                        "uniform mat4 view = mat4(1);\n"
                                        "void main() {\n"
                                          "gl_Position = projection * view * transform * aPos;\n"
                                        "}";

inline const std::string DEFAULT_FSH =  GLSL_VERSION_STRING "\n"
                                        "uniform vec4 color;\n"
                                        "out vec4 fragColor;\n"
                                        "void main() {\n"
                                          "fragColor = color;\n"
                                        "}" ;

template <typename T>
struct is_glm_vec : std::false_type {};

template <glm::length_t L, typename T, glm::qualifier Q>
struct is_glm_vec<glm::vec<L, T, Q>> : std::true_type {};

template <typename T>
concept UniformConcept1D = std::same_as<T, float> || std::same_as<T, double> || std::same_as<T, int> || std::same_as<T, unsigned int>;

template <typename T>
concept UniformConceptVec = is_glm_vec<T>::value;

class Shader {
private:
  unsigned int m_vertex_shader, m_fragment_shader, m_program;

public:
  /**
   * Create a shader using the default shader
  */
  Shader();
  ~Shader();

  /**
   * Create a shader from two source strings
   *
   * @param vert_shader_source Source file for the vertex shader
   * @param frag_shader_source Source file for the fragment shader
  */
  Shader(const std::string& vert_shader_source, const std::string& frag_shader_source);

  /**
   * Load a manifest file that contains the shader source files
   *
   * @param shader_manifest_path Path to a shader manifest file
  */
  Shader(const std::string& shader_manifest_path);

  /**
   * Use the shader program 
  */
  inline void use() {
    glUseProgram(this->m_program);
  }

  /**
   * Set the uniform of a vector
   *
   * @param name Name of the uniform
   * @param vec  Any supported glm::vec
  */
  template<glm::length_t L, typename T, glm::qualifier Q>
  void uniform(const std::string& name, const glm::vec<L, T, Q> &vec) {
    this->use();

    const unsigned int location = glGetUniformLocation(this->m_program, name.c_str());

    if constexpr (std::is_same_v<T, float>) {
      if constexpr (L == 1) glUniform1f(location, vec.x);
      else if constexpr (L == 2) glUniform2f(location, vec.x, vec.y);
      else if constexpr (L == 3) glUniform3f(location, vec.x, vec.y, vec.z);
      else if constexpr (L == 4) glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    } else if constexpr (std::is_same_v<T, int>) {
      if constexpr (L == 1) glUniform1i(location, vec.x);
      else if constexpr (L == 2) glUniform2i(location, vec.x, vec.y);
      else if constexpr (L == 3) glUniform3i(location, vec.x, vec.y, vec.z);
      else if constexpr (L == 4) glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
    } else if constexpr (std::is_same_v<T, double>) {
      if constexpr (L == 1) glUniform1d(location, vec.x);
      else if constexpr (L == 2) glUniform2d(location, vec.x, vec.y);
      else if constexpr (L == 3) glUniform3d(location, vec.x, vec.y, vec.z);
      else if constexpr (L == 4) glUniform4d(location, vec.x, vec.y, vec.z, vec.w);
    } else {
      static_assert(false, "Unsupported uniform type");
    }
  }

  /**
   * Set the uniform of a matrix
   *
   * @param name Name of the uniform
   * @param mat  Any supported glm::mat
  */
  template <glm::length_t C, glm::length_t R, typename T>
  void uniform(const std::string& name, const glm::mat<C, R, T> &mat) {
    this->use();
    const unsigned int location = glGetUniformLocation(this->m_program, name.c_str());

    if constexpr (std::is_same_v<T, float>) {
      if constexpr (C == 2 && R == 2)      glUniformMatrix2fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 3) glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 4) glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 2 && R == 3) glUniformMatrix2x3fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 2) glUniformMatrix3x2fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 2 && R == 4) glUniformMatrix2x4fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 2) glUniformMatrix4x2fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 4) glUniformMatrix3x4fv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 3) glUniformMatrix4x3fv(location, 1, GL_FALSE, &mat[0][0]);
      else static_assert(false, "Unsupported float matrix size");
    } else if constexpr (std::is_same_v<T, double>) {
      if constexpr (C == 2 && R == 2)      glUniformMatrix2dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 3) glUniformMatrix3dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 4) glUniformMatrix4dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 2 && R == 3) glUniformMatrix2x3dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 2) glUniformMatrix3x2dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 2 && R == 4) glUniformMatrix2x4dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 2) glUniformMatrix4x2dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 3 && R == 4) glUniformMatrix3x4dv(location, 1, GL_FALSE, &mat[0][0]);
      else if constexpr (C == 4 && R == 3) glUniformMatrix4x3dv(location, 1, GL_FALSE, &mat[0][0]);
      else static_assert(false, "Unsupported double matrix size");
    } else {
      static_assert(false, "Unsupported matrix type");
    }
  }

  /**
   * Set the uniform of a one-dimensional value
   *
   * @param name  Name of the uniform
   * @param value Value
  */
  template <UniformConcept1D T>
  void uniform(const std::string& name, const T &value) {
    this->use();
    const unsigned int location = glGetUniformLocation(this->m_program, name.c_str());

    if constexpr (std::is_same_v<T, float>) {
      glUniform1f(location, value);
    } else if constexpr (std::is_same_v<T, double>) {
      glUniform1d(location, value);
    } else if constexpr (std::is_same_v<T, unsigned int>) {
      glUniform1ui(location, value); 
    } else if constexpr (std::is_same_v<T, int>) {
      glUniform1i(location, value);
    } else {
      static_assert(false, "Unsupported uniform type");
    }
  }

  /**
   * Set the uniform of an array
   *
   * @param name Name of the uniform
   * @param list An iterable
  */
  template<glm::length_t L, typename T, glm::qualifier Q, std::size_t N>
  void uniform(const std::string& name, const std::array<glm::vec<L, T, Q>, N> &list) {
    this->use();

    std::size_t i = 0;
    for (const T &item : list) {
      this->uniform(name + std::format("[{}]", i++), item);
    }
  }

  /**
   * Set the uniform of a vector
   *
   * @param name Name of the uniform
   * @param list An iterable
  */
  template<glm::length_t L, typename T, glm::qualifier Q>
  void uniform(const std::string& name, const std::vector<glm::vec<L, T, Q>> &list) {
    this->use();

    std::size_t i = 0;
    for (const T &item : list) {
      this->uniform(name + std::format("[{}]", i++), item);
    }
  }

  // TODO: Uniform Texture
  // void uniform_tex(Texture &texture);
};
