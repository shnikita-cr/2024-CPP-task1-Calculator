#ifndef TASK1_CALCULATOR_H
#define TASK1_CALCULATOR_H

#include <vector>
#include <string>
#include <filesystem>
#include "../Operation/Operation.h"
#include "../Parser/Token.h"
#include "../Parser/Parser.h"
#include "Plugin.h"

namespace fs = std::filesystem;

class Calculator {
private:
    std::vector<Operation *> operations;
    std::vector<Plugin> plugins;
    Parser parser;

    int loadOperations() {
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
//                std::cout << entry.path() << std::endl;
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
                std::cerr << "Failed to load DLL!" << std::endl;
                return -1;
            }
            plugin.createF = (CreateOpFunc) GetProcAddress(plugin.hDll, "create");
            plugin.destroyF = (DestroyOpFunc) GetProcAddress(plugin.hDll, "destroy");

            if (!plugin.destroyF || !plugin.createF) {
                std::cerr << "Failed to find factory functions!" << std::endl;
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

public:
    Calculator() {
        if (loadOperations()) {
            err("no operations provided in default folder. exit");
            exit(1);
        }
        parser.setOperations(operations);
    };

    double calculate(const std::string &expression) {
        return parser.parse(expression);
    }

    void printOperations() {
        std::cout << "Operations list:" << std::endl;
        for (auto o: operations) {
            std::cout << "\t" << o->getName() << " symbol: " << o->getSymbol() << std::endl;
        }
    }

    ~Calculator() {
        for (auto &p: plugins) {
            p.destroyF(p.op);
            FreeLibrary(p.hDll);
        }
    }
};


#endif //TASK1_CALCULATOR_H
