#include "shapes.hpp"
#include "chunk.hpp"
#include "imgui.hpp"
#include "input.hpp"
#include "Camera.hpp"
#include "Holder.hpp"

#include <shaders.hpp>
#include <texsys.hpp>
#include <renderer.hpp>
#include <vertexbuf.hpp>
#include <indexbuf.hpp>
#include <vertexarray.hpp>
#include <vertexlayout.hpp>
#include <window.hpp>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <print>

using namespace Puffy;

Camera cam({0, 20.0f, 30.0f});
Camera* getCam() {
    return &cam;
}

class MVP {
public:
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    void Reset(){
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
    }

    void setM(const glm::mat4& matrix){
        model = matrix;
    }
    void setV(const glm::mat4& matrix){
        view = matrix;
    }
    void setP(const glm::mat4& matrix){
        projection = matrix;
    }

    void ResetM(){
        model = glm::mat4(1.0f);
    }
    void ResetV(){
        view = glm::mat4(1.0f);
    }
    void ResetP(){
        projection = glm::mat4(1.0f);
    }
};

int main(){
    TextureManager textures;
    Engine::Renderer renderer;
    
    Window window(720, 450, "Hey");
    if(!window.isReady()){ // hello
        return window.currentError();//<3
    }
    
    DearImGUI imgui(window.getWindow());
    
    Texture2D texture = textures.LoadTexture("no", "textures/hi.png");
    
    Engine::Shader shader("shaders/basic.vert", "shaders/basic.pix");
    
    Holder lightCube;
    
    lightCube.vbo.Initialize(cubeVertices, sizeof(cubeVertices));
    lightCube.ibo.Initialize(cubeIndices, sizeof(cubeIndices));
    lightCube.GenerateSelf();
        
    shader.bind();
    while (window.running()) {
        MVP mvp;
        //VSYNC(window);

        processInput(&window);
        
        renderer.Clear();
        
        mvp.setV(cam.getView());
        mvp.setP(glm::perspective(glm::radians(cam.fov), window.getAspect(), 0.1f, 100.0f));
        mvp.setM(glm::translate(mvp.model, imgui.utility.v1));

        { // MVP Shader setter
            shader.set<glm::mat4>("u_model", mvp.model);
            shader.set<glm::mat4>("u_view", mvp.view);
            shader.set<glm::mat4>("u_projection", mvp.projection);
        }

        { // Texture Setter
            texture.bind(0);
            shader.set<int>("u_Texture", (int)0);
        }

        { // Position Setter
            shader.set<glm::vec3>("viewPos", cam.getPosition());
            shader.set<glm::vec3>("lightPos", imgui.utility.v1);
        }

        { // Shader Values
            shader.set<float>("material.shininess", 128.0f);
            shader.set<float>("pix_enabled", 1.0f);
        }

        { // Colors
            shader.set<glm::vec3>("pix_objectColor", glm::vec3(153.0f / 255.0f, 51.0f / 255.0f, 51.0f / 255.0f)); // glm::vec3(static_cast<float>(153 / 255), static_cast<float>(51 / 255), static_cast<float>(51 / 255))
            shader.set<glm::vec3>("pix_lightColor", imgui.utility.v2);
	        shader.set<glm::vec3>("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	        shader.set<glm::vec3>("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	        shader.set<glm::vec3>("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        }
        
        lightCube.Draw(renderer, shader);
        window.flip();
    }

    return Error::None;
}
