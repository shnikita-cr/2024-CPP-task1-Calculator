#ifndef TASK1_CALCULATOR_H
#define TASK1_CALCULATOR_H

#include <vector>
#include <iomanip>
#include "Plugin.h"
#include "../Operation/Operation.h"
#include "../Parser/Parser.h"
#include "../Tech/tech.h"

class Calculator {
private:
    std::vector<Operation *> operations;
    std::vector<Plugin> plugins;
    Parser parser;

    int loadOperations();

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
        OperationType t;
        for (Operation *o: operations) {
            t = o->getType();
            switch (t) {
                case OperationType::BINARY_INFIX:
                    std::cout << "\tName: " << o->getName() << " Type: " << "BINARY_INFIX" << std::endl;
                    break;
                case OperationType::UNARY_POSTFIX:
                    std::cout << "\tName: " << o->getName() << " Type: " << "UNARY_POSTFIX" << std::endl;
                    break;
                case OperationType::UNARY_FUNCTION:
                    std::cout << "\tName: " << o->getName() << " Type: " << "UNARY_FUNCTION" << std::endl;
                    break;
                case OperationType::BINARY_FUNCTION:
                    std::cout << "\tName: " << o->getName() << " Type: " << "BINARY_FUNCTION" << std::endl;
                    break;
                case OperationType::ABSTRACT:
                    std::cout << "\tName: " << o->getName() << " Type: " << "ABSTRACT" << std::endl;
                    break;
            }
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
