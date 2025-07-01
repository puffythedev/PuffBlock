#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera(glm::vec3 position) : m_position(position) {
            m_front = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            m_right = glm::normalize(glm::cross(m_front, worldUp));
            m_up = glm::normalize(glm::cross(m_right, m_front));
        }

        glm::mat4 getView() {
            return glm::lookAt(m_position, m_position + m_front, m_up);
        }

        glm::vec3 getPosition(){
            return m_position;
        }

        void setPosition(glm::vec3 position){
            m_position = position;
        }

        glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_up;
        float yaw = -90.0f;
        float pitch = 0.0f;
        float fov = 45.0f;

    private:
        glm::vec3 m_position;
        glm::vec3 m_target;         
        glm::vec3 m_direction;
        glm::vec3 m_right;
};