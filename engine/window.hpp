#pragma once

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

enum Error {
    None = 0,
    InitializationFailed,
    WindowFail
};

inline int accumulator = 0;

#define VSYNC(window) accumulator += window.getFrameTime(); \
    if(accumulator < window.getRefreshRate()){ \
        continue; \
    } else { \
        accumulator = 0; \
        if (glfwGetWindowAttrib(window.getWindow(), GLFW_ICONIFIED) != 0) { \
            ImGui_ImplGlfw_Sleep(10); \
            continue; \
        } \
    }

namespace Puffy {
    class Window {
        public:
            struct WindowDims { int w, h; };
            Window(int width, int height, const std::string& name);
            ~Window();
            bool isReady() const;
            Error currentError() const;
            GLFWwindow* getWindow() const;
            WindowDims getDimensions() const;
            float getAspect() const;
            float getFrameTime() const;
            int getRefreshRate() const;

            void flip();
            
            bool running();
        private:
            double lastTime;
            float deltaTime = 0;
            bool ready = false;
            Error error = None;
            GLFWwindow* window;
            int width, height;
    };
} // namespace Puffy
