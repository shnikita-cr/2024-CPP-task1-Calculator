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
            std::cout << "\tName: " << std::setw(20) << std::left << o->getName()
                      << " Symbol: " << std::setw(7) << std::left << o->getSymbol()
                      << " Type: ";
            switch (t) {
                case OperationType::BINARY_INFIX:
                    std::cout << "BINARY_INFIX" << std::endl;
                    break;
                case OperationType::UNARY_POSTFIX:
                    std::cout << "UNARY_POSTFIX" << std::endl;
                    break;
                case OperationType::UNARY_FUNCTION:
                    std::cout << "UNARY_FUNCTION" << std::endl;
                    break;
                case OperationType::BINARY_FUNCTION:
                    std::cout << "BINARY_FUNCTION" << std::endl;
                    break;
                default:
                    std::cout << "ABSTRACT" << std::endl;
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
