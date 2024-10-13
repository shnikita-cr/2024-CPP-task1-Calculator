#ifndef LOG10_LIBRARY_H
#define LOG10_LIBRARY_H

#ifdef LOG10DLL_EXPORTS
#define LOG10DLL_API __declspec(dllexport)
#else
#define LOG10DLL_API __declspec(dllimport)
#endif

#include <cmath>
#include "../../task1/src/Operation/Operation.h"
#include "../../task1/src/Operation/ArityOperation/UnaryOperation.h"

class Sin : public UnaryOperation {
public:
    double getResult(double a) const override {
        return std::sin(a);
    }

    std::string getName() const override {
        return "Radian Sinus";
    }

    std::string getSymbol() const override {
        return "sin";
    }

    OperationType getType() const override {
        return OperationType::UNARY_FUNCTION;
    }

};

extern "C" LOG10DLL_API Operation * create();
extern "C" LOG10DLL_API void destroy(Operation * obj);

#endif //LOG10_LIBRARY_H
