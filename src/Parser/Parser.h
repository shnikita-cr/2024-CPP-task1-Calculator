#ifndef TASK1_PARSER_H
#define TASK1_PARSER_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "Token.h"
#include "../Operation/Operation.h"

class Parser {
private:
    Token currentToken;
    Token previousToken;
    Operation *currentOperationP;
    double numberValue;
    std::stringstream ss;
    std::vector<Operation *> operations;

    Token getToken();

    double expr();

    double term();

    double primary();

    Token processPlugin(char ch);

public:
    Parser() {
        currentToken = NONE;
        previousToken = NONE;
        numberValue = 0;
        currentOperationP = nullptr;
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
