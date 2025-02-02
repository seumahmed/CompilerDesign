/*Write a C++ program that would analyses the following:
Justify the variable is properly declared or not.
Detect whether the given mathematical expression is properly parenthesized or not.
for example: ((x+y)*5)
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isParenthesisBalanced(string expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty() || s.top() != '(') {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    string expr;

    cout << "Enter a mathematical expression: ";
    getline(cin, expr);


    if (expr[0] >= 'a' && expr[0] <= 'z' || expr[0] >= 'A' && expr[0] <= 'Z') {
        cout << "Variable is properly declared.\n";
    } else {
        cout << "Variable is not properly declared.\n";
    }


    if (isParenthesisBalanced(expr)) {
        cout << "Parentheses are balanced.\n";
    } else {
        cout << "Parentheses are not balanced.\n";
    }

    return 0;
}
