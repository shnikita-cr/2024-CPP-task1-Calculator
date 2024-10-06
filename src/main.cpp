#include <iostream>
#include <string>
#include "Calculator/Calculator.h"

using namespace std;

int main() {
    Calculator calculator;
    string expression;
    double result;
    calculator.printOperations();
    cout << "Calculator start." << endl;
    cout << "To stop calculator type STOP." << endl;
    while (true) {
        cout << " Input: ";
        cin >> expression;
        if (expression != "STOP") {
            result = calculator.calculate(expression);
            cout << "Result: " << result << endl;
        } else {
            cout << "Calculator stop." << endl;
            break;
        }
    }
    return 0;
}
