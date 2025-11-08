// TODO: Create a prototype
// - [x] Triangle
// - [ ] Create a default shader loaded by an initializer
//   - [ ] Shader that loads right after calling an init function from the engine
// - [ ] Line
//   - [ ] 3d Line
// - [ ] Primitive Outline
//   - [ ] Animatable / Paramerized Outline
// - [ ] Animated Triangle
//     - [ ] Animation Handler
//     - [ ] Splines
//       - [ ] Bezier Curve
//     - [ ] Value Updater
// - [ ] Circle
// - [ ] Animated circle

#include "Primitives/Lines.hpp"
#define SDL_MAIN_USE_CALLBACKS 1

#include "Primitives/Triangle.hpp"
#include "Utils/Preproc.hpp"
#include "Render/Shader.hpp"
#include "Math/Camera.hpp"
#include "Math/Bezier.hpp"

#include <glad/gl.h>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


SDL_Window *mainWindow;
SDL_GLContext mainGLContext;

Shader *shader0;
Shader *shader1;
Triangle *triangle0;
LineSegment *line0;
Camera<Projection::Perspective> *camera;

CubicBezier<3> *bezier;

unsigned long currentTime;

inline void init() {
  shader0 = new Shader();
  shader1 = new Shader(DEFAULT_2D_VSH, DEFAULT_3D_FSH);

  triangle0 = new Triangle(glm::vec3(1, 0, 1), std::array<glm::vec3, 3>{
    glm::vec3{0, 0.5, 0}, 
    glm::vec3{-0.5, -0.5, 0}, 
    glm::vec3{0.5, -0.5, 0}
  });
  camera = new Camera<Projection::Perspective>();

  bezier = new CubicBezier<3>(std::array<glm::vec3, 4>{
    glm::vec3(0),
    glm::vec3(0),
    glm::vec3(0),
    glm::vec3(0)
  });

  line0 = new LineSegment(glm::vec3(1, 0, 1), glm::vec3{1, 1, 0}, glm::vec3{0, 0, 0}, Caps::CCircle, 0.1);

  camera->position.z = -3;
  camera->field_of_view = glm::radians(45.f);
}

inline void cleanUp() {
  delete line0;
  delete shader0;
  delete shader1;
  delete triangle0;
  delete camera;
}

inline void render() {
  currentTime = SDL_GetTicks();

  glm::mat4x4 v = camera->calculateViewMatrix();
  glm::mat4x4 p = camera->calculateProjectionMatrix();

  shader0->uniform("view", v);
  shader0->uniform("projection", p);

  triangle0->transformation = glm::rotate(triangle0->transformation, glm::radians(90 * currentTime / 1000.f * 3), glm::vec3(1, 0, 0));
  triangle0->transformation = glm::rotate(glm::mat4x4(1), glm::radians(90 * currentTime / 1000.f), glm::vec3(0, 1, 0));
  triangle0->drawOutline(shader0);
  line0->draw(shader0);
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  mainWindow = SDL_CreateWindow("ganim", 1280, 720, SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(mainWindow);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJ_VER);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MIN_VER); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    std::cout << "Failed to load OpenGL\n";
    return SDL_APP_FAILURE;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

  init();

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  cleanUp();

  SDL_GL_DestroyContext(mainGLContext);
  SDL_DestroyWindow(mainWindow);
  SDL_Quit();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  switch (event->type) {
    case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
      break;
    default: break;
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render();

  SDL_GL_SwapWindow(mainWindow);
  return SDL_APP_CONTINUE;
}
