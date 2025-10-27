project(
  'ganim',
  ['cpp', 'c'],
  version: '1.0',
  default_options: [
    'cpp_std=c++23'
  ]
)

cc = meson.get_compiler('cpp')

sdl_dep = dependency('sdl3', required: true)

include_dirs = include_directories('src', 'glad/include')

executable(
  'manim',
  'src/main.cpp',
  'glad/src/gl.c',
  include_directories: include_dirs,
  dependencies: sdl_dep
)
