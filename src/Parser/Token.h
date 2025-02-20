#ifndef TASK1_TOKEN_H
#define TASK1_TOKEN_H

enum Token {
    NONE = '0',
    END = 'E',
    NUMBER = 'N',
    LP = '(', RP = ')',
    PLUS = '+', MINUS = '-', MUL = '*', DIV = '/',
    LINE_FUNCTION = 'P',
    BINARY_INFIX = 'B',
    UNARY_POSTFIX
};

#endif //TASK1_TOKEN_H
