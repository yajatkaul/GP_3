project(
  'glad',
  'c',
  version: '1',
  license: 'MIT AND BSD-3-Clause',
  meson_version: '>= 0.49.0',
)

inc = include_directories('include')

libglad = static_library(
    'glad', 
    'src/glad.c', 
    include_directories: [inc]
)

glad_dep = declare_dependency(
    include_directories: inc,
    link_with: libglad
)