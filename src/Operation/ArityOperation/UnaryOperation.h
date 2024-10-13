#pragma once

#include "../Operation.h"

class UnaryOperation : public Operation {
public:
    virtual double getResult(double a) const = 0;

    std::string getName() const override { return "UnaryOperation"; }

    std::string getSymbol() const override { return "u"; }

    OperationType getType() const override { return OperationType::ABSTRACT; }

    virtual ~UnaryOperation() = 0;

};

UnaryOperation::~UnaryOperation() = default;
