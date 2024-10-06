#ifndef TASK1_UNARYOPERATION_H
#define TASK1_UNARYOPERATION_H

#include "../Operation.h"

class UnaryOperation : public Operation {
public:
    UnaryOperation() {
        name = "UnaryOperation";
        symbol = "u";
    }

    virtual double getResult(double a) = 0;

    virtual ~UnaryOperation() = 0;

};

#endif //TASK1_UNARYOPERATION_H

UnaryOperation::~UnaryOperation() = default;
