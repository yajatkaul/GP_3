#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"

using namespace std;

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

static void GLCheckError()
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << ")" << endl;
    }
}

int main(void)
{
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Hello xx", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int version = gladLoadGL();
    if (version == 0)
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    float positions[] = {
        -0.5f,
        -0.5f, // 0
        0.5f,
        -0.5f, // 1
        0.5f,
        0.5f, // 2
        -0.5f,
        0.5f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    unsigned int buffer;
    // Create buffer returns the id and assings it to buffer
    glGenBuffers(1, &buffer);
    // Bind current array buffer array here
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Add data in there
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    unsigned int ibo;
    // this time creates an index buffer
    glGenBuffers(1, &ibo);
    // binds a current array buffer here
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // puts index data in there
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Shader shader = Shader("./shaders/vertex.shader", "./shaders/fragment.shader");
    shader.SetUnifrom1i("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLClearError();
        // From the index buffer gets the position data and draws them
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCheckError();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}