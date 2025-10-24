#pragma once

#include "Renderer.h"

class Camera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float yaw;
    float pitch;
    float lastX;
    float lastY;
    bool firstMouse;
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void keyboard_callback(const Uint8 *state, float deltaTime);

public:
    Camera(SDL_Window *window);
    ~Camera();
    void processInput(SDL_Event event, float deltaTime);
    glm::mat4 GetView();
    float fov;
};
