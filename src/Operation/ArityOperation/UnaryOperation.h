#ifndef TASK1_UNARYOPERATION_H
#define TASK1_UNARYOPERATION_H

#include "../Operation.h"

class UnaryOperation : public Operation {
public:
    virtual double getResult(double a) = 0;

    std::string getName() override { return "UnaryOperation"; }

    std::string getSymbol() override { return "u"; }

    OperationType getType() override { return OperationType::ABSTRACT; }

    virtual ~UnaryOperation() = 0;

};

#endif //TASK1_UNARYOPERATION_H

UnaryOperation::~UnaryOperation() = default;
