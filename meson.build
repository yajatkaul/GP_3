project(
    'graphics_engine', 
    'cpp',
    default_options : ['cpp_std=c++20']
)

inc = include_directories('include')

src = ['src/main.cpp', 'src/Shader.cpp', 'src/Renderer.cpp','src/VertexBuffer.cpp','src/IndexBuffer.cpp']

glfw_dep = dependency('glfw3', required: true, static: true)
glad_dep = subproject('glad').get_variable('glad_dep')
glm_dep = dependency('glm', required: true, static: true)

link_args = ['-lopengl32']

executable(
    'release/Engine', 
    src, 
    include_directories: [inc],
    dependencies: [glfw_dep, glad_dep, glm_dep],
    link_args: link_args
)