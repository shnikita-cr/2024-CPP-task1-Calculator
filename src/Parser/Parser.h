#pragma once

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

    Token processOperation(char ch);

    int checkCurrentTokens();
public:
    Parser()
        : currentToken(NONE),
        previousToken(NONE),
        currentOperationP(nullptr),
        numberValue(0.0) {}

    void setOperations(std::vector<Operation*>&& _operations) {
        operations = _operations;
    }

    double parse(const std::string &_expr) {
        ss.clear(); //in case it has smth old/incorrect
        ss.str(_expr);
        getToken();
        if(currentToken == END)
            return 0;
        return expr();
    }
};
