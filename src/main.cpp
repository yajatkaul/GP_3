#include <glad/glad.h>
#include <SDL.h>
#undef main
#include <iostream>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("SDL2 OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_MakeCurrent(window, context);

    int version = gladLoadGL();
    if (version == 0)
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    // Lock the cursor and hide it
    SDL_SetRelativeMouseMode(SDL_TRUE); // locks the cursor to window
    SDL_ShowCursor(SDL_DISABLE);        // hide cursor

    Camera camera = Camera(window);

    // Cube
    float positions[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VertexBuffer vb = VertexBuffer(positions, sizeof(positions));
    vb.Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
    glEnableVertexAttribArray(0);

    // IndexBuffer ib = IndexBuffer(indices, sizeof(indices));
    // ib.Bind();

    Shader shader = Shader("./shaders/vertex.shader", "./shaders/fragment.shader");
    shader.SetUnifrom1i("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)SDL_GetTicks() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    shader.SetUnifromMatrix4fv("projection", 1, false, glm::value_ptr(projection));
    shader.SetUnifromMatrix4fv("model", 1, false, glm::value_ptr(model));

    bool running = true;
    SDL_Event event;

    glEnable(GL_DEPTH_TEST);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            camera.processInput(event);
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLClearError();

        // From the index buffer gets the position data and draws them
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)SDL_GetTicks() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUnifromMatrix4fv("model", 1, false, glm::value_ptr(model));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        view = camera.GetView();
        projection = glm::perspective(glm::radians(camera.fov), 800.0f / 600.0f, 0.1f, 100.0f);

        shader.SetUnifromMatrix4fv("view", 1, false, glm::value_ptr(view));
        shader.SetUnifromMatrix4fv("projection", 1, false, glm::value_ptr(projection));

        GLCheckError();

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
