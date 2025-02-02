#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int main() {
    string reg; // To store the input regular expression
    vector<vector<int>> q(20, vector<int>(5, 0)); // Transition table for NFA with 5 columns (a, b, c, d, epsilon)
    int i = 0, j = 1, len; // `i` is the index for processing the regex, `j` tracks the current state, `len` stores the length of the regex

    // Input the regular expression
    cout << "Enter the regular expression: ";
    cin >> reg;
    cout << "Given regular expression: " << reg << "\n";

    len = reg.length();

    // Process each character of the regular expression
    while (i < len) {
        // Handle single characters (a, b, c, d) that are not part of alternation (`|`) or repetition (`*`)
        if (reg[i] == 'a' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][0] = j + 1; // Transition on 'a' to the next state
            j++;
        } else if (reg[i] == 'b' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][1] = j + 1; // Transition on 'b' to the next state
            j++;
        } else if (reg[i] == 'c' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][2] = j + 1; // Transition on 'c' to the next state
            j++;
        } else if (reg[i] == 'd' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][3] = j + 1; // Transition on 'd' to the next state
            j++;
        }
        // Handle alternation (`a|b`)
        else if (reg[i] == 'a' && reg[i + 1] == '|' && reg[i + 2] == 'b') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transition to two branches
            j++;
            q[j][0] = j + 1; // First branch handles 'a'
            j++;
            q[j][4] = j + 3; // Epsilon transition to the final state
            j++;
            q[j][1] = j + 1; // Second branch handles 'b'
            j++;
            q[j][4] = j + 1; // Epsilon transition to the final state
            j++;
            i += 2; // Skip '|' and the next character
        }
        // Handle alternation (`b|a`)
        else if (reg[i] == 'b' && reg[i + 1] == '|' && reg[i + 2] == 'a') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transition to two branches
            j++;
            q[j][1] = j + 1; // First branch handles 'b'
            j++;
            q[j][4] = j + 3; // Epsilon transition to the final state
            j++;
            q[j][0] = j + 1; // Second branch handles 'a'
            j++;
            q[j][4] = j + 1; // Epsilon transition to the final state
            j++;
            i += 2; // Skip '|' and the next character
        }
        // Handle Kleene star (`a*`)
        else if (reg[i] == 'a' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transitions for zero or more repetitions
            j++;
            q[j][0] = j + 1; // Transition on 'a' to the next state
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1); // Epsilon transition back to the start of the loop
            j++;
        }
        // Handle Kleene star (`b*`)
        else if (reg[i] == 'b' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transitions for zero or more repetitions
            j++;
            q[j][1] = j + 1; // Transition on 'b' to the next state
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1); // Epsilon transition back to the start of the loop
            j++;
        }
        // Handle Kleene star (`c*`)
        else if (reg[i] == 'c' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transitions for zero or more repetitions
            j++;
            q[j][2] = j + 1; // Transition on 'c' to the next state
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1); // Epsilon transition back to the start of the loop
            j++;
        }
        // Handle Kleene star (`d*`)
        else if (reg[i] == 'd' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3); // Epsilon transitions for zero or more repetitions
            j++;
            q[j][3] = j + 1; // Transition on 'd' to the next state
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1); // Epsilon transition back to the start of the loop
            j++;
        }
        // Handle other patterns like `)*`
        else if (reg[i] == ')' && reg[i + 1] == '*') {
            q[0][4] = ((j + 1) * 10) + 1; // Epsilon transition to loop back to the start
            q[j][4] = ((j + 1) * 10) + 1;
            j++;
        }
        i++;
    }

    // Display the transition table
    cout << "\n\tTransition Table \n";
    cout << "____________________________________\n";
    cout << "Current State |\tInput |\tNext State";
    cout << "\n____________________________________\n";

    for (i = 0; i <= j; i++) {
        if (q[i][0] != 0) cout << "\n  q[" << i << "]\t      |   a   |  q[" << q[i][0] << "]";
        if (q[i][1] != 0) cout << "\n  q[" << i << "]\t      |   b   |  q[" << q[i][1] << "]";
        if (q[i][2] != 0) cout << "\n  q[" << i << "]\t      |   c   |  q[" << q[i][2] << "]";
        if (q[i][3] != 0) cout << "\n  q[" << i << "]\t      |   d   |  q[" << q[i][3] << "]";
        if (q[i][4] != 0) {
            if (q[i][4] < 10)
                cout << "\n  q[" << i << "]\t      |   e   |  q[" << q[i][4] << "]";
            else
                cout << "\n  q[" << i << "]\t      |   e   |  q[" << q[i][4] / 10 << "] , q[" << q[i][4] % 10 << "]";
        }
    }

    cout << "\n____________________________________\n";
    return 0;
}
