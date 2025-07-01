#include <GLFW/glfw3.h>
#include "imgui.hpp"

ImGuiIO& InitImGUI(GLFWwindow* window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    return io;
}

UtilityWindow::UtilityWindow(){
    v1 = glm::vec3(1.2f, 1.0f, 2.0f);
    v2 = glm::vec3(1.0, 1.0, 1.0);
}

UtilityWindow::~UtilityWindow(){

}

void UtilityWindow::Render() {
    ImGui::Begin("Utility");
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    // ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", pos.x, pos.y, pos.z);
	// ImGui::Text("Draw Calls Per Second: %d", callspers);
	ImGui::InputFloat3("Light Position", &v1[0]);
	ImGui::ColorPicker3("Light Color", &v2[0]);
    
    ImGui::End();
}

DearImGUI::DearImGUI(GLFWwindow* winptr){
    InitImGUI(winptr);
}

DearImGUI::~DearImGUI(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DearImGUI::Render(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    utility.Render();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}