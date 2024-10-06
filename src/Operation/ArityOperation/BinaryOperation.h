#ifndef TASK1_BINARYOPERATION_H
#define TASK1_BINARYOPERATION_H

#include "../Operation.h"

class BinaryOperation : public Operation {
public:
    virtual double getResult(double a, double b) = 0;

    std::string getName() override { return "BinaryOperation"; }

    std::string getSymbol() override { return "b"; }

    OperationType getType() override { return OperationType::ABSTRACT; }

    virtual ~BinaryOperation() = 0;
};

#endif //TASK1_BINARYOPERATION_H

BinaryOperation::~BinaryOperation() = default;