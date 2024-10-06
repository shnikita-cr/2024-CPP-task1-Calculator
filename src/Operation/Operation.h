#ifndef TASK1_OPERATION_H
#define TASK1_OPERATION_H

#include <string>
#include "OperationType/OperationType.h"

class Operation {
protected:
    std::string name;
    std::string symbol;
    OperationType type;
public:
    Operation() { type = OperationType::ABSTRACT; };

    virtual std::string getName() { return name; }

    virtual std::string getSymbol() { return symbol; }

    virtual OperationType getType() { return type; }
};

#endif