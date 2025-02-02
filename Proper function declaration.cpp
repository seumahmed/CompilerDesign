/*Write a program that would analyze the followings : -
b.	Proper function declaration
c.	Proper function definition
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


bool isFunctionDeclaration(const string& line) {

    return line.find("int") != string::npos && line.find("(") != string::npos;
}

bool isFunctionDefinition(const string& line) {

    return line.find("int") != string::npos && line.find("{") != string::npos;
}

int main() {
    string code = "int CDLab(int a,int b)\n"
                      "{\n"
                      "   cout<<\"Hello Everyone!!\";\n"
                      "   return a+b;\n"
                      "}";

    istringstream codeStream(code);
    string line;

    bool hasDeclaration = false;
    bool hasDefinition = false;

    while (getline(codeStream, line)) {
        if (isFunctionDeclaration(line)) {
            hasDeclaration = true;
        }
        if (isFunctionDefinition(line)) {
            hasDefinition = true;
        }
    }

    if (hasDeclaration && hasDefinition) {
        cout << "The function is not properly declared and defined." << std::endl;
    } else {
        cout << "The function is properly declared and defined." << std::endl;
    }

    return 0;
}


