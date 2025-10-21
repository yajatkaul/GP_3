#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

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

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f};

    unsigned int buffer;
    // Create buffer returns the id and assings it to buffer
    glGenBuffers(1, &buffer);
    // Purpose of buffer array here
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Add data in there
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}