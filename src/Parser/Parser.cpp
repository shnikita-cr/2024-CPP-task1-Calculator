#include "Parser.h"

Token Parser::getToken() {
    char ch = '\0';
    do {
        if (!ss.get(ch)) {
            return currentToken = END;
        }
    } while ((ch != '\n') && isspace(ch));

    switch (ch) {
        case '\n':
        case '\0':
            return currentToken = END;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
            ss << ch;
            return currentToken = (Token) ch;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '.':
            ss.putback(ch);
            ss >> numberValue;
            ss << numberValue;
            return currentToken = NUMBER;
        default:
            err("bad token");
            return END;
    }
}

double Parser::expr() {
    double left = term();
    while (true) {
        switch (currentToken) {
            case PLUS:
                getToken();
                left += term();
                break;
            case MINUS:
                getToken();
                left -= term();
                break;
            default:
                return left;
        }
    }
}

double Parser::term() {
    double left = primary();
    while (true) {
        switch (currentToken) {
            case MUL:
                getToken();
                left *= primary();
                break;
            case DIV:
                getToken();
                left /= primary();
                break;
            default:
                return left;
        }
    }
}

double Parser::primary() {
    switch (currentToken) {
        case NUMBER:
            getToken();
            return numberValue;
        case MINUS:
            getToken();
            return -primary();
        case LP:
            getToken();
            double e;
            e = expr();
            if (currentToken != RP) {
                err(") expected");
                return 0;
            }
            getToken();
            return e;
//            case NONE:
//                return 1;
        default:
            err("primary expected");
            return 0;
    }
}
