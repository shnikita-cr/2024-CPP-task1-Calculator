#ifndef TASK1_OPERATION_H
#define TASK1_OPERATION_H

#include <string>

class Operation {
protected:
    std::string name;
public:
    Operation() = default;
    virtual std::string getName(){return "";}
};

#endif