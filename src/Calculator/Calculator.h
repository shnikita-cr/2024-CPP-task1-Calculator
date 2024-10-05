#ifndef TASK1_CALCULATOR_H
#define TASK1_CALCULATOR_H

#include <vector>
#include <string>
#include "../Operations/Operation/Operation.h"

class Calculator {
private:
    std::vector<Operation> operations;

    int loadOperations() {
        return 0;
    }

public:
    Calculator() {
        if (!loadOperations()) {
            std::cerr << "No operations provided in default folder. Exit." << std::endl;
        }
    };

    std::string calculate(const std::string &expression) {
        return "";
    }

    void printOperations() {
        std::cout << "Operations list:";
        for (auto o: operations) {
            std::cout << " " << o.getName();
        }
        std::cout << std::endl;
    }
};


#endif //TASK1_CALCULATOR_H
