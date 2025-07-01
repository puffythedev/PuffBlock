#pragma once
#include <string>
#include <unordered_map>
#include <glad/gl.h>
#include <glm/glm.hpp>

namespace Puffy::Engine {
    class Shader {
        public:
            Shader(const std::string& vpath, const std::string& ppath);
            Shader(int vpath, const std::string& ppath);
            Shader(const std::string& vpath, int ppath);
            ~Shader();
            bool isBuilt();
            void bind() const;
            void unbind() const;

            template<typename T>
            void set(const std::string& str, T type) {
                // do nothing
            }

            template<>
            void set<int>(const std::string& str, int type) {
                glUniform1i(getLocation(str), type);
            }
            
            template<>
            void set<float>(const std::string& str, float type) {
                glUniform1f(getLocation(str), type);
            }
        
            template<>
            void set<glm::mat4>(const std::string& str, glm::mat4 type) {
                glUniformMatrix4fv(getLocation(str), 1, GL_FALSE, &type[0][0]);
            }
            
            template<>
            void set<const glm::mat4&>(const std::string& str, const glm::mat4& type) {
                glUniformMatrix4fv(getLocation(str), 1, GL_FALSE, &type[0][0]);
            }
            
            template<>
            void set<glm::vec3>(const std::string& str, glm::vec3 vector) {
                glUniform3fv(getLocation(str), 1, &vector[0]);
            }

            template<>
            void set<glm::vec4>(const std::string& str, glm::vec4 vector) {
                glUniform4fv(getLocation(str), 1, &vector[0]);
            }

        private:
            unsigned int program = 0;
            unsigned int vertex = 0;
            unsigned int pixel = 0;
            int  success;
            bool errored = false;
            std::unordered_map<std::string, int> cache;
            bool buildVertex(const std::string& vpath);
            bool buildPixel(const std::string& ppath);
            bool linkProgram();
            void cleanUp();
            int getLocation(const std::string& str);
    };
};