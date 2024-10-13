#ifndef POW_LIBRARY_H
#define POW_LIBRARY_H

#ifdef POWDLL_EXPORTS
#define POWDLL_API __declspec(dllexport)
#else
#define POWDLL_API __declspec(dllimport)
#endif

#include <cmath>
#include "D:/data/c++/Polytech_university/2024_C++ pro/task1/src/Operation/ArityOperation/BinaryOperation.h"

class Pow : public BinaryOperation {
public:
    Pow() = default;

    double getResult(double base, double exponent) const override {
        return std::pow(base, exponent);
    }

    std::string getName() const override {
        return "Exponentiation";
    }

    std::string getSymbol() const override {
        return "^";
    }

    OperationType getType() const override {
        return OperationType::BINARY_INFIX;
    }
};

extern "C" POWDLL_API Operation * create();
extern "C" POWDLL_API void destroy(Operation * obj);

#endif //POW_LIBRARY_H