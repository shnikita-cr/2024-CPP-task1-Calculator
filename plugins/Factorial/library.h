#ifndef POW_LIBRARY_H
#define POW_LIBRARY_H

#ifdef POWDLL_EXPORTS
#define POWDLL_API __declspec(dllexport)
#else
#define POWDLL_API __declspec(dllimport)
#endif

#include <cmath>
#include <stdexcept>
#include "D:/data/c++/Polytech_university/2024_C++ pro/task1/src/Operation/ArityOperation/UnaryOperation.h"

class Factorial : public UnaryOperation {
public:
    Factorial() = default;

    double getResult(double a) const override {
        double c = trunc(a);
        if(c == a && a >= 0) {
            if(a == 0)
                return 1;
            if(a >= 20) {
                throw std::runtime_error("given num is TOO MUCH for factorial stored in double");
            }
            long int b = 1;
            for(long int i = 1; i <= (long int)c; i++) {
                b *= i;
            }
            return b;
        } else {
            throw std::runtime_error("given num is not +int");
        }
        return 0;
    }

    std::string getName() const override {
        return "Factorial";
    }

    std::string getSymbol() const override {
        return "!";
    }

    OperationType getType() const override {
        return OperationType::UNARY_POSTFIX;
    }
};

extern "C" POWDLL_API Operation * create();
extern "C" POWDLL_API void destroy(Operation * obj);

#endif //POW_LIBRARY_H