#ifndef TASK1_PARSER_H
#define TASK1_PARSER_H

#include <string>
#include <sstream>
#include <iostream>
#include "../Token.h"
#include "../tech.h"

class Parser {
private:
    Token currentToken;
    double numberValue;
    std::stringstream ss;

    Token getToken();

    double expr();

    double term();

    double primary();

public:
    explicit Parser(const std::string &_expr) {
        ss.str(_expr);
        currentToken = NONE;
        numberValue = 0;
    }

    void parse() {
        getToken();
        std::cout << "expr value: " << expr() << std::endl;
        std::cout << "token: " << static_cast<char>(currentToken) << std::endl;
    }
};


#endif //TASK1_PARSER_H
