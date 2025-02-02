//Write a c++ program to identify keywords and identifiers

#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool isKeyword(const string& word) {
    vector<string> keywords = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
        "union", "unsigned", "void", "volatile", "while"
    };

    for (const string& keyword : keywords) {
        if (word == keyword) {
            return true;
        }
    }

    return false;
}

int main() {
    string input;
    cout << "Enter a input: ";
    getline(cin, input);


    vector<string> words;
    string word;
    for (char c : input) {
        if (isalnum(c)) {
            word += c;
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }


    vector<string> keywords, identifiers;
    for (const string& word : words) {
        if (isKeyword(word)) {
            keywords.push_back(word);
        } else {
            identifiers.push_back(word);
        }
    }


    cout << "Keywords: ";
    for (const string& keyword : keywords) {
        cout << keyword << " ";
    }
    cout << endl;

    cout << "Identifiers: ";
    for (const string& identifier : identifiers) {
        cout << identifier << " ";
    }
    cout << endl;

    return 0;
}
