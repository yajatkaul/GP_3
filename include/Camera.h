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

public:
    Camera(GLFWwindow *window);
    ~Camera();
    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    void processInput(GLFWwindow *window);
    glm::mat4 GetView();
    float fov;
};