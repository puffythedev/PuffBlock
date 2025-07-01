#pragma once
#include <string>

namespace Puffy::Engine::fs {
    std::string readFile(const std::string& path);
    void deleteFile(const std::string& path);
    void createFile(const std::string& path, const std::string& content);
};