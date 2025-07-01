#include "filesys.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <spdlog/spdlog.h>

namespace Puffy::Engine::fs {
    std::string readFile(const std::string& path){
        std::ifstream input(path);
        if(!input.is_open()){
            spdlog::error("File in ({}) cannot be opened.", path);
            return "";
        }
        std::stringstream ss;
        ss << input.rdbuf();

        return ss.str();
    }

    void deleteFile(const std::string& path){
        if(!std::filesystem::exists(path)){
            spdlog::error("Path ({}) doesn't exist.", path);
            return;
        }
        
        std::filesystem::remove(path);
    }
    
    void createFile(const std::string& path, const std::string& content){
        std::ofstream output(path);
        if(!output.is_open()){
            spdlog::error("File in ({}) cannot be opened.", path);
            return;
        }

        output << content;
    }
};