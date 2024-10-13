#include <filesystem>
#include <string>
#include "Calculator.h"

namespace fs = std::filesystem;

int Calculator::loadOperations() {
    fs::path operationsLibrariesPathRoot = "plugins";
    try { 
        if(fs::is_empty(operationsLibrariesPathRoot)) {
            err("plugins path '" + fs::absolute(operationsLibrariesPathRoot).string() + "' is empty!");
            return 0;
        }

        std::vector<fs::path> operationsLibrariesPaths;
        for(const auto &entry : fs::directory_iterator(operationsLibrariesPathRoot)) {
            if(entry.path().extension() == ".dll") {
                operationsLibrariesPaths.emplace_back(entry.path());
            } else {
                err("Wrong file extension for Plugin: " + entry.path().extension().string());
            }
        }

        OperationLibrary currentOL{};
        Operation *op;
        for(const auto &pth : operationsLibrariesPaths) {
            std::string currentPth = pth.string();
            currentOL.hDll = LoadLibraryW(reinterpret_cast<LPCWSTR>(pth.c_str()));
            if(!currentOL.hDll) {
                DWORD errorCode = GetLastError();
                err("Failed to load DLL: '" + fs::absolute(currentPth).string() + "' Error code: " + std::to_string(errorCode));
                continue; //try next dll
            }
            currentOL.createF = (CreateOpFunc)GetProcAddress(currentOL.hDll, "create");
            currentOL.destroyF = (DestroyOpFunc)GetProcAddress(currentOL.hDll, "destroy");

            if(!currentOL.destroyF || !currentOL.createF) {
                err("Failed to find factory functions!");
                FreeLibrary(currentOL.hDll);
                return 1;
            }
            op = currentOL.createF();
            currentOL.op = op;

            OperationLibraries.emplace_back(currentOL);
            operations.emplace_back(op);
        }
    }
    catch(fs::filesystem_error e) {
        err(e.what());
    }
    return 0;
}

void Calculator::printOperations() {
    if(operations.size() != 0) {
        std::cout << "Operations list:" << std::endl;
        for(const Operation *o : operations) {
            std::cout << "\tName: " << std::setw(20) << std::left << o->getName()
                << " Symbol: " << std::setw(7) << std::left << o->getSymbol()
                << " Type: ";
            switch(o->getType()) {
                case OperationType::BINARY_INFIX:
                    std::cout << "BINARY_INFIX" << std::endl;
                    break;
                case OperationType::UNARY_POSTFIX:
                    std::cout << "UNARY_POSTFIX" << std::endl;
                    break;
                case OperationType::UNARY_FUNCTION:
                    std::cout << "UNARY_FUNCTION" << std::endl;
                    break;
                default:
                    std::cout << "DEFAULT" << std::endl;
                    break;
            }
        }
    } else {
        std::cout << "Operations list: empty." << std::endl;
    }
}
