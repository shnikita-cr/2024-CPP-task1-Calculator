#pragma once

#include "../Operation.h"

class BinaryOperation : public Operation {
public:
    virtual double getResult(double a, double b) const = 0;

    std::string getName() const override { return "BinaryOperation"; }

    std::string getSymbol() const override { return "b"; }

    OperationType getType() const override { return OperationType::ABSTRACT; }

    virtual ~BinaryOperation() = 0;
};

BinaryOperation::~BinaryOperation() = default;