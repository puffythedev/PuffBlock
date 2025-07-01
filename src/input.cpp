#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.hpp"
#include "input.hpp"

unsigned int type = GLFW_CURSOR_DISABLED;

Camera* getCam();

bool isKeyPressed(GLFWwindow* window, unsigned int key){
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void processInput(Puffy::Window* window) {
    Camera* cam = getCam();
    float cameraSpeed = static_cast<float>(8 * window->getFrameTime());
    
    GLFWwindow* winptr = window->getWindow();
    if(glfwGetKey(winptr, GLFW_KEY_SPACE) == GLFW_PRESS){
        glfwSetInputMode(winptr, GLFW_CURSOR, type == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	type = type == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    }
    if (isKeyPressed(winptr, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(winptr, GLFW_TRUE);
    if (isKeyPressed(winptr, GLFW_KEY_W))
        cam->setPosition(cam->getPosition() + cameraSpeed * cam->m_front);
    if (isKeyPressed(winptr, GLFW_KEY_S))
        cam->setPosition(cam->getPosition() - cameraSpeed * cam->m_front);
    if (isKeyPressed(winptr, GLFW_KEY_A))
        cam->setPosition(cam->getPosition() - glm::normalize(glm::cross(cam->m_front, cam->m_up)) * cameraSpeed);
    if (isKeyPressed(winptr, GLFW_KEY_D))
        cam->setPosition(cam->getPosition() + glm::normalize(glm::cross(cam->m_front, cam->m_up)) * cameraSpeed);
}

bool firstMouse = false;
float lastX = 0, lastY = 0;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera *cam = getCam();
    cam->fov -= (float)yoffset;
    if (cam->fov < 1.0f)
    cam->fov = 1.0f;
    if (cam->fov > 45.0f)
    cam->fov = 45.0f;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    Camera *cam = getCam();
    float xpos1 = static_cast<float>(xpos);
    float ypos1 = static_cast<float>(ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    cam->yaw   += xoffset;
    cam->pitch += yoffset;

    if(cam->pitch > 89.0f)
        cam->pitch =  89.0f;
    if(cam->pitch < -89.0f)
        cam->pitch =  89.0f;
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    direction.y = sin(glm::radians(cam->pitch));
    direction.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    cam->m_front = glm::normalize(direction);
}