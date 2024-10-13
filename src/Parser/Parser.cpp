#include "Parser.h"
#include "../Tech/tech.h"
#include "../Operation/ArityOperation/BinaryOperation.h"
#include "../Operation/ArityOperation/UnaryOperation.h"

/*
* expression:
*   expr + term
*   expr - term
*   term
* term:
*   term * primary
*   term / primary
*   BINARY_INFIX a&b
*   UNARY_POSTFIX a!
*   primary
* primary;
*   NUMBER
*   + primary
*   - primary
*   LINE_FUNCTION f()
*   ( expression )
*
* BINARY_INFIX has 1 symbol only
*
*/

Token Parser::getToken() {
    char ch = '\0';
    do {
        if(!ss.get(ch)) {
            return currentToken = END;
        }
    } while((ch != '\n') && isspace(ch)); // get rid of spaces and \n

    switch(ch) {
        case '\n':
        case '\0':
            previousToken = currentToken;
            return currentToken = END;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
            ss << ch;
            previousToken = currentToken;
            currentToken = (Token)ch;
            if(checkCurrentTokens()) {
                err("wrong input!");
                return currentToken = END;
            } else {
                return currentToken;
            }
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
            previousToken = currentToken;
            currentToken = NUMBER;
            if(checkCurrentTokens()) {
                err("wrong input!");
                return currentToken = END;
            } else {
                return currentToken;
            }
        default:
            return processOperation(ch);
    }
}

double Parser::expr() {
    double left = term();
    while(true) {
        switch(currentToken) {
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
    while(true) {
        switch(currentToken) {
            case MUL:
                getToken();
                left *= primary();
                break;
            case DIV:
                getToken();
                left /= primary();
                break;
            case BINARY_INFIX:
                getToken();
                const BinaryOperation *b;
                b = dynamic_cast<BinaryOperation *>(currentOperationP);
                try {
                    if(b)
                        left = b->getResult(left, primary());
                    else {
                        err("operation not loaded or was used in composition and deleted ");
                    }
                }
                catch(std::runtime_error e) {
                    err(e.what());
                    left = 0;
                    currentToken = END;
                    return left;
                }
                currentOperationP = nullptr;
                break;
            case UNARY_POSTFIX:
                getToken();
                const UnaryOperation *u;
                u = dynamic_cast<UnaryOperation *>(currentOperationP);
                try {
                    if(u)
                        left = u->getResult(left);
                    else {
                        err("operation not loaded or was used in composition and deleted ");
                    }
                }
                catch(std::runtime_error e) {
                    err(e.what());
                    left = 0;
                    currentToken = END;
                    return left;
                }
                currentOperationP = nullptr;
                break;
            default:
                return left;
        }
    }
}

double Parser::primary() {
    switch(currentToken) {
        case NUMBER:
            getToken();
            return numberValue;
        case PLUS:
            getToken();
            return expr();
        case MINUS:
            getToken();
            return -expr();
        case LINE_FUNCTION:
            getToken();
            return primary();
        case LP:
            if(previousToken == LINE_FUNCTION) {
                getToken();
                double e;
                e = expr();
                if(currentToken != RP) {
                    err(") expected");
                    return 0;
                }
                UnaryOperation *u;
                u = dynamic_cast<UnaryOperation *>(currentOperationP);
                try {
                    if(u)
                        e = u->getResult(e);
                    else {
                        err("operation not loaded or was used in composition and deleted ");
                    }
                }
                catch(std::runtime_error er) {
                    err(er.what());
                    e = 0;
                    currentToken = END;
                    return e;
                }
                currentOperationP = nullptr;
                getToken();
                return e;
            } else {
                getToken();
                double e;
                e = expr();
                if(currentToken != RP) {
                    err(") expected");
                    return 0;
                }
                getToken();
                return e;
            }
        case END:
            return 0;
        default:
            err("primary expected");
            return 0;
    }
}

Token Parser::processOperation(char ch) {
    std::string functionSymbol;
    if(std::isalpha(ch)) {
        functionSymbol.push_back(ch);
        while(ss.get(ch) && isalnum(ch)) // function name may consist of letters and numbers 
            functionSymbol.push_back(ch); //starting from letter
        ss << functionSymbol;
        ss.putback(ch);
        std::string ss_ = ss.str();
    } else {
        functionSymbol = ch;
    }
    for(const auto &o : operations) {
        if(o->getSymbol() == functionSymbol) {
            currentOperationP = o;
            break;
        }
    }
    if(!currentOperationP) {
        err("can not find given function!");
        return END;
    }
    switch(currentOperationP->getType()) {
        case OperationType::BINARY_INFIX:
            previousToken = currentToken;
            return currentToken = BINARY_INFIX;
            break;
        case OperationType::UNARY_POSTFIX:
            previousToken = currentToken;
            return currentToken = UNARY_POSTFIX;
            break;
        case OperationType::UNARY_FUNCTION:
            previousToken = currentToken;
            return currentToken = LINE_FUNCTION;
            break;
        default:
            break;
    }
    return END;
}

int Parser::checkCurrentTokens() {
    return 0;
}