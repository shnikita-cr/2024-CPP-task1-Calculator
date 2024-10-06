#include "Parser.h"
#include "../Tech/tech.h"
#include "../Operation/ArityOperation/BinaryOperation.h"
#include "../Operation/ArityOperation/UnaryOperation.h"

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
            previousToken = currentToken;
            return currentToken = NUMBER;
        default:
            return processPlugin(ch);
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
            case UNARY_POSTFIX:
                getToken();
                UnaryOperation *u;
                u = dynamic_cast<UnaryOperation *>(currentOperationP);
                left = u->getResult(left);
                currentOperationP = nullptr;
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
            case BINARY_INFIX:
                getToken();
                BinaryOperation *b;
                b = dynamic_cast<BinaryOperation *>(currentOperationP);
                left = b->getResult(left, primary());
                currentOperationP = nullptr;
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
        default:
            err("primary expected");
            return 0;
    }
}

Token Parser::processPlugin(char ch) {
    std::string functionSymbol;
    if (std::isalpha(ch)) {
        functionSymbol.push_back(ch);
        while (ss.get(ch) && isalnum(ch))
            functionSymbol.push_back(ch);
        ss << functionSymbol;
    } else {
        functionSymbol = ch;
    }
    std::cout << "function " << functionSymbol << std::endl;
    for (auto o: operations) {
        if (o->getSymbol() == functionSymbol) {
            std::cout << "found function!" << std::endl;
            currentOperationP = o;
        }
    }
    if (!currentOperationP) {
        err("can not find given function!");
        return END;
    }
    auto ot = currentOperationP->getType();
    switch (ot) {
        case OperationType::BINARY_INFIX:
            previousToken = currentToken;
            currentToken = BINARY_INFIX;
            break;
        case OperationType::UNARY_POSTFIX:
            previousToken = currentToken;
            currentToken = UNARY_POSTFIX;
            break;
        case OperationType::UNARY_FUNCTION:
        case OperationType::BINARY_FUNCTION:
            previousToken = currentToken;
            currentToken = LINE_FUNCTION;
            break;
        default:
            break;
    }
    return END;
}
