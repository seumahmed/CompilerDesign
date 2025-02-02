//Write a C++ program to identify numerical, alphabet & also vowel, logical operator and special character from ASCII table.

#include <iostream>
#include <vector>

using namespace std;

int main() {
    char arr[5];
for (int i = 0; i < 5; i++) {
    cout << "Enter a input: ";

        cin >> arr[i];
    }

    for (int i = 0; i < 5; i++) {
        char ch = arr[i];

        if (isdigit(ch)) {
            cout << ch << " is a numerical digit." << endl;
        } else if (isalpha(ch)) {
            cout << ch << " is an alphabet." << endl;

            if (tolower(ch) == 'a' || tolower(ch) == 'e' || tolower(ch) == 'i' || tolower(ch) == 'o' || tolower(ch) == 'u') {
                cout << ch << " is a vowel." << endl;
            } else {
                cout << ch << " is a consonant." << endl;
            }
        } else if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~') {
            cout << ch << " is a logical operator." << endl;
        } else {
            cout << ch << " is a special character." << endl;
        }
    }

    return 0;
}
