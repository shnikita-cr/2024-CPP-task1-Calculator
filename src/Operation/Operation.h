#ifndef TASK1_OPERATION_H
#define TASK1_OPERATION_H

#include <string>
#include "OperationType/OperationType.h"

class Operation {
public:
    virtual std::string getName() { return ""; }

    virtual std::string getSymbol() { return ""; }

    virtual OperationType getType() { return OperationType::ABSTRACT; }
};

#endif