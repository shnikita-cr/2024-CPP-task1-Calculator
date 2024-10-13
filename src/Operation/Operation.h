#pragma once

#include <string>
#include "OperationType/OperationType.h"

class Operation {
public:
    virtual std::string getName() const { return ""; }

    virtual std::string getSymbol() const { return ""; }

    virtual OperationType getType() const { return OperationType::ABSTRACT; }
};
