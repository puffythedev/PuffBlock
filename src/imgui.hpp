#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <glm/glm.hpp>

ImGuiIO& InitImGUI(GLFWwindow* window);


class ImGUIFrame {
public:
    ImGUIFrame() {}
    ~ImGUIFrame() {}
    
    void Render();
};

class UtilityWindow : public ImGUIFrame {
    public:
    UtilityWindow();
    ~UtilityWindow();
    
    void Render();
    
    glm::vec3 v1;
    glm::vec3 v2;
};

class DearImGUI {
public:
    DearImGUI(GLFWwindow* winptr);
    ~DearImGUI();

    void Render();

    UtilityWindow utility;
};