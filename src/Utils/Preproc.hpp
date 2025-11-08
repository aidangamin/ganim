#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

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

#define GLSL_VERSION_STRING "#version " STR(GL_MAJ_VER) STR(GL_MIN_VER) "0"
