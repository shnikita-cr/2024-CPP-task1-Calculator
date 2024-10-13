#ifndef LOG10_LIBRARY_H
#define LOG10_LIBRARY_H

#ifdef LOG10DLL_EXPORTS
#define LOG10DLL_API __declspec(dllexport)
#else
#define LOG10DLL_API __declspec(dllimport)
#endif

#include <cmath>
#include <stdexcept>
#include "D:/data/c++/Polytech_university/2024_C++ pro/task1/src/Operation/ArityOperation/UnaryOperation.h"

class Log10 : public UnaryOperation {
public:
    Log10() = default;

    double getResult(double a) const override {
        if(a > 0)
            return std::log10(a);
        else
            throw std::runtime_error("given num is not +double");
    }

    std::string getName() const override {
        return "Decimal logarithm";
    }

    std::string getSymbol() const override {
        return "log10";
    }

    OperationType getType() const override {
        return OperationType::UNARY_FUNCTION;
    }

};

extern "C" LOG10DLL_API Operation * create();
extern "C" LOG10DLL_API void destroy(Operation * obj);

#endif //LOG10_LIBRARY_H
