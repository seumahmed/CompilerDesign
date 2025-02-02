//Detect whether the given mathematical expression is valid or not:

#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to calculate the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to evaluate a postfix expression
int evaluatePostfix(string exp) {
    stack<int> st;

    for (int i = 0; i < exp.length(); i++) {
        if (isdigit(exp[i])) {
            st.push(exp[i] - '0');
        } else {
            int val1 = st.top();
            st.pop();
            int val2 = st.top();
            st.pop();

            switch (exp[i]) {
                case '+':
                    st.push(val2 + val1);
                    break;
                case '-':
                    st.push(val2 - val1);
                    break;
                case '*':
                    st.push(val2 * val1);
                    break;
                case '/':
                    st.push(val2 / val1);
                    break;
            }
        }
    }
    return st.top();
}

// Function to convert infix expression to postfix
string infixToPostfix(string exp) {
    stack<char> st;
    string result;

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];

        if (isdigit(c)) {
            result += c;
        } else if (c == '(') {
            st.push('(');
        } else if (c == ')') {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop();
        } else {
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

int main() {
    string expr1 = "1+2*3";
    string postfix1 = infixToPostfix(expr1);
    int result1 = evaluatePostfix(postfix1);
    cout << "Value of " << expr1 << " is " << result1 << endl;

    string expr2 = "(1+2)*3";
    string postfix2 = infixToPostfix(expr2);
    int result2 = evaluatePostfix(postfix2);
    cout << "Value of " << expr2 << " is " << result2 << endl;

    return 0;
}
