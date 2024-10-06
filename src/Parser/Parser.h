#ifndef TASK1_PARSER_H
#define TASK1_PARSER_H

#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include "Token.h"
#include "../Tech/tech.h"
#include "../Operation/Operation.h"

class Parser {
private:
    Token currentToken;
    double numberValue;
    std::stringstream ss;
    std::vector<Operation *> operations;

    Token getToken();

    double expr();

    double term();

    double primary();

    int processPlugin(char ch) {
        if (std::isalpha(ch)) {
            std::string functionName;
            functionName.push_back(ch);
            while (ss.get(ch) && isalnum(ch))
                functionName.push_back(ch);
            ss << functionName;
            currentToken = LINE_FUNCTION;
            std::cout << "function " << functionName << std::endl;
//            for (auto &o: operations) {
//                if (o.getSymbol() == functionName) {
//                    if (o.getType()=)
//                }
//            }
            return 0;
        } else {
            currentToken = LINE_FUNCTION;
        }
        return 1;
    }

public:
    Parser() {
        currentToken = NONE;
        numberValue = 0;
    }

    void setOperations(const std::vector<Operation *> &_operations) {
        operations = _operations;
    }

    double parse(const std::string &_expr) {
        ss.clear();
        ss.str(_expr);
        getToken();
        return expr();
    }
};


#endif //TASK1_PARSER_H
