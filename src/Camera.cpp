#include "Camera.h"

Camera::Camera(SDL_Window *window)
{
    // camera
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // mouse control
    yaw = -90.0f; // yaw is initialized to -90.0 degrees to look along -Z by default
    pitch = 0.0f;
    lastX = 800.0f / 2.0f;
    lastY = 600.0f / 2.0f;
    firstMouse = true;
    fov = 45.0f;

    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);
}

Camera::~Camera()
{
}

void Camera::mouse_callback(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::scroll_callback(double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::processInput(SDL_Event event)
{
    const float cameraSpeed = 0.05f;
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W])
        cameraPos += cameraSpeed * cameraFront;
    if (state[SDL_SCANCODE_S])
        cameraPos -= cameraSpeed * cameraFront;
    if (state[SDL_SCANCODE_A])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (state[SDL_SCANCODE_D])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (event.type == SDL_MOUSEMOTION)
    {
        float xpos = (float)event.motion.x;
        float ypos = (float)event.motion.y;

        mouse_callback(xpos, ypos);
    }
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}