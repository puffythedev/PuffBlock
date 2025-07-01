#include "window.hpp"
#include <spdlog/spdlog.h>
#include <glad/gl.h>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
int sWidth, sHeight;

void aCB(GLFWwindow* window, int width, int height){
    sWidth = width;
    sHeight = height;
    glViewport(0, 0, width, height);
}

namespace Puffy {

    void error_callback(int error, const char* description) {
        spdlog::error("Error: {}\n", description);
    }

    Window::Window(int width, int height, const std::string& name){
        if(!glfwInit()){
            error = Error::InitializationFailed;
            return;
        }
        glfwSetErrorCallback(error_callback);
        
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        
        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        
        if(!window){
            spdlog::info("Window sadly didn't initialize...");
            error = Error::WindowFail;
            return;
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetFramebufferSizeCallback(window, aCB);

        glfwGetFramebufferSize(window, &sWidth, &sHeight);

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        // glfwSwapInterval(1);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ready = true;
    }

    Window::~Window(){
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool Window::isReady() const{
        return ready;
    }

    Error Window::currentError() const {
        return error;
    }

    GLFWwindow* Window::getWindow() const {
        return window;
    }

    bool Window::running() {
        return !glfwWindowShouldClose(window);
    }

    Window::WindowDims Window::getDimensions() const {
        return WindowDims { sWidth, sHeight };
    }
    
    float Window::getAspect() const {
        return static_cast<float>(sWidth) / static_cast<float>(sHeight);
    }

    float Window::getFrameTime() const {
        return deltaTime;
    }
    
    void Window::flip() {
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        deltaTime = static_cast<float>(glfwGetTime() - lastTime);
        lastTime = glfwGetTime();
    }

    int Window::getRefreshRate() const {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        float refreshRate = 1 / mode->refreshRate;
        return refreshRate;
    }
} // namespace Puffy