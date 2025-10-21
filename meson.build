project(
    'graphics_engine', 
    'cpp',
    default_options : ['cpp_std=c++20']
)

inc = include_directories('include')

glfw_dep = dependency('glfw3', required: true, static: true)

link_args = ['-lopengl32']

executable(
    'release/Engine', 
    'src/main.cpp', 
    include_directories: [inc],
    dependencies: [glfw_dep],
    link_args: link_args
)