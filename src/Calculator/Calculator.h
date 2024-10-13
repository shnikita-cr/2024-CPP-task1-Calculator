#pragma once

#include <vector>
#include <iomanip>
#include "OperationLibrary.h"
#include "../Operation/Operation.h"
#include "../Parser/Parser.h"
#include "../Tech/tech.h"

class Calculator {
private:
    std::vector<Operation *> operations;
    std::vector<OperationLibrary> OperationLibraries;
    Parser parser;

    int loadOperations();

public:
    Calculator() {
        if (loadOperations()) {
            err("no operations loaded. exit");
            exit(1);
        }
        parser.setOperations(std::move(operations));
    };

    double calculate(const std::string &expression) {
        return parser.parse(expression);
    }

    void printOperations();

    ~Calculator() {
        for (auto &ol: OperationLibraries) {
            ol.destroyF(ol.op);
            FreeLibrary(ol.hDll);
        }
    }
};