#include "shaders.hpp"
#include "filesys.hpp"
#include <spdlog/spdlog.h>

namespace Puffy::Engine {
    Shader::Shader(const std::string& vpath, const std::string& ppath){
        bool built = buildVertex(vpath);
        bool built1 = buildPixel(ppath);
        
        bool linked = linkProgram();
        
        if(!built && !built1 && !linked){
            errored = true;
        }

        if(!errored){
            spdlog::info("Built Shader (ID {}) Successfully!\n- Vertex Shader Path: {}\n- Pixel Shader Path: {}\n", program, vpath, ppath);
        }
    }
    
    Shader::Shader(int vpath, const std::string& ppath){
        bool built = buildPixel(ppath);

        bool linked = linkProgram();
        
        if(!built && !linked){
            errored = true;
        }
    }
    
    Shader::Shader(const std::string& vpath, int ppath){
        bool built = buildVertex(vpath);

        bool linked = linkProgram();
        
        if(!built && !linked){
            errored = true;
        }
    }

    bool Shader::isBuilt(){
        return errored;
    }

    void Shader::bind() const {
        glUseProgram(program);
    }
    
    void Shader::unbind() const {
        glUseProgram(0);
    }

    int Shader::getLocation(const std::string& str){
        if(cache.contains(str)){
            return cache[str];
        }

        int val = glGetUniformLocation(program, str.c_str());
        if(val == -1)
            spdlog::error("Cannot find shader location [{}]", str);
        cache[str] = val;
        
        spdlog::info("Loaded '{}' (Location {}) into cache", str, val);
        return val;
    }

    bool Shader::buildVertex(const std::string& vpath){
        const std::string& vert = Engine::fs::readFile(vpath);
        const char* vertcode = vert.c_str();
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertcode, NULL);
        glCompileShader(vertex);
        
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

        if(!success) {
            int length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            char infoLog[512];
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            spdlog::error("Vertex shader failed to compile: {}\n", infoLog);
            return false;
        }
        return true;
    }

    bool Shader::buildPixel(const std::string& ppath){
        const std::string& pix = Engine::fs::readFile(ppath);
        const char* pixcode = pix.c_str();

        pixel = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(pixel, 1, &pixcode, NULL);
        glCompileShader(pixel);

        glGetShaderiv(pixel, GL_COMPILE_STATUS, &success);

        if(!success) {
            int length;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
            char infoLog[512];
            glGetShaderInfoLog(pixel, 512, nullptr, infoLog);
            spdlog::error("Pixel shader failed to compile: {}\n", infoLog);
            return false;
        }
        return true;
    }

    Shader::~Shader(){
        glDeleteProgram(program);
    }

    bool Shader::linkProgram(){
        program = glCreateProgram();
        
        glAttachShader(program, vertex);
        glAttachShader(program, pixel);
        glLinkProgram(program);
        glValidateProgram(program);
        
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if(!success) {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            char* infoLog = (char*)alloca(length * sizeof(char));
            glGetProgramInfoLog(program, length, &length, infoLog);
            spdlog::error("Program failed to link: {}\n", infoLog);
            return false;
        }
        return true;
    }
     
    void Shader::cleanUp(){
        glDeleteShader(vertex);
        glDeleteShader(pixel);
    }
}