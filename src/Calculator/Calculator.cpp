#include <filesystem>
#include <string>
#include "Calculator.h"

namespace fs = std::filesystem;

int Calculator::loadOperations() {
    std::string path = "..\\plugins";
    std::vector<fs::path> pluginsPaths;
    if (fs::is_empty(path)) {
        err("plugins path " + path + " is empty!");
        return 1;
    }
    fs::path currentPath;
    for (const auto &entry: fs::directory_iterator(path)) {
        currentPath = entry.path();
        if (currentPath.extension() == ".dll") {
            std::cout << currentPath << std::endl;
            pluginsPaths.emplace_back(currentPath);
        } else {
            err("wrong file extension for Plugin " + currentPath.extension().string());
        }
    }

    Plugin plugin{};
    Operation *op;
    for (const auto &pth: pluginsPaths) {
        std::string currentPth = pth.string();
        plugin.hDll = LoadLibraryW(reinterpret_cast<LPCWSTR>(pth.c_str()));
        if (!plugin.hDll) {
            err("Failed to load DLL!");
            err(currentPth);
            return -1;
        }
        plugin.createF = (CreateOpFunc) GetProcAddress(plugin.hDll, "create");
        plugin.destroyF = (DestroyOpFunc) GetProcAddress(plugin.hDll, "destroy");

        if (!plugin.destroyF || !plugin.createF) {
            err("Failed to find factory functions!");
            FreeLibrary(plugin.hDll);
            return -1;
        }
        op = plugin.createF();
        plugin.op = op;

        plugins.emplace_back(plugin);
        operations.emplace_back(op);
    }
    return 0;
}

namespace fs = std::filesystem;

