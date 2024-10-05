#ifndef TASK1_CALCULATOR_H
#define TASK1_CALCULATOR_H

#include <vector>
#include <string>
#include "../Operations/Operation/Operation.h"
#include "../Token.h"
#include "../Parser/Parser.h"


class Calculator {
private:
    std::vector<Operation> operations;

    int loadOperations() {
        //open folder plugins
        //read every file dll
        //check if all is ok
        return 0;
    }

public:
    Calculator() {
        if (loadOperations()) {
            err("no operations provided in default folder. exit");
        }
    };

    std::string calculate(const std::string &expression) {
        Parser parser(expression);
        parser.parse();
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
