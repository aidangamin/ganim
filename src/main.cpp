#define SDL_MAIN_USE_CALLBACKS 1

#if !defined (DEFAULT_WINDOW_WIDTH)
#define DEFAULT_WINDOW_WIDTH 800
#endif

#if !defined (DEFAULT_WINDOW_HEIGHT)
#define DEFAULT_WINDOW_HEIGHT 600
#endif

#if !defined (GL_MAJ_VER)
#define GL_MAJ_VER 4
#endif

#if !defined (GL_MIN_VER)
#define GL_MIN_VER 3
#endif

#include <glad/gl.h>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_surface.h>

SDL_Window *mainWindow;
SDL_GLContext mainGLContext;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  mainWindow = SDL_CreateWindow("ganim", 800, 600, SDL_WINDOW_OPENGL);
  SDL_GL_CreateContext(mainWindow);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJ_VER);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MIN_VER); 
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
    std::cout << "Failed to load OpenGL\n";
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
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
  SDL_GL_SwapWindow(mainWindow);
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  SDL_GL_DestroyContext(mainGLContext);
  SDL_DestroyWindow(mainWindow);
  SDL_Quit();
}
