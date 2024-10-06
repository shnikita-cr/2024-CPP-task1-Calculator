#ifndef TASK1_BINARYOPERATION_H
#define TASK1_BINARYOPERATION_H

#include "../Operation.h"

class BinaryOperation : public Operation {
public:
    BinaryOperation() {
        name = "BinaryOperation";
        symbol = "b";
    }

    virtual double getResult(double a, double b) = 0;

    virtual ~BinaryOperation() = 0;
};

#endif //TASK1_BINARYOPERATION_H

BinaryOperation::~BinaryOperation() = default;