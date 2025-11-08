project(
  'ganim',
  ['cpp', 'c'],
  version: '1.0',
  default_options: [
    'cpp_std=c++23'
  ]
)

defines = [
  '-DLOGGING_COLOR',
]

cc = meson.get_compiler('cpp')

glad_source = 'glad/src/gl.c'
main_source = 'src/main.cpp'
framework_sources = [
  'src/Render/Shader.cpp',
  'src/Primitives/Triangle.cpp',
  'src/Primitives/Lines.cpp',
  'src/Math/Camera.cpp',
  'src/Utils/logging.c',
]

sdl_dep = dependency('sdl3', required: true)
glm_dep = dependency('glm', required: true)

include_dirs = include_directories('src', 'glad/include')

executable(
  'manim',

  main_source,
  framework_sources,
  glad_source,

  include_directories: include_dirs,

  dependencies: [
    sdl_dep, 
    glm_dep,
  ],

  cpp_args: defines,
  c_args: defines,
)
