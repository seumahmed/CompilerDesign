#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

int main() {
    string reg;
    vector<vector<int>> q(20, vector<int>(5, 0));
    int i = 0, j = 1, len;

    cout << "Enter the regular expression: ";
    cin >> reg;
    cout << "Given regular expression: " << reg << "\n";

    len = reg.length();

    while (i < len) {
        if (reg[i] == 'a' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][0] = j + 1;
            j++;
        } else if (reg[i] == 'b' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][1] = j + 1;
            j++;
        } else if (reg[i] == 'c' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][2] = j + 1;
            j++;
        } else if (reg[i] == 'd' && reg[i + 1] != '|' && reg[i + 1] != '*') {
            q[j][3] = j + 1;
            j++;
        } else if (reg[i] == 'a' && reg[i + 1] == '|' && reg[i + 2] == 'b') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][4] = j + 3;
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][4] = j + 1;
            j++;
            i += 2;
        } else if (reg[i] == 'b' && reg[i + 1] == '|' && reg[i + 2] == 'a') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][4] = j + 3;
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][4] = j + 1;
            j++;
            i += 2;
        } else if (reg[i] == 'a' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][0] = j + 1;
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1);
            j++;
        } else if (reg[i] == 'b' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][1] = j + 1;
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1);
            j++;
        } else if (reg[i] == 'c' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][2] = j + 1;
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1);
            j++;
        } else if (reg[i] == 'd' && reg[i + 1] == '*') {
            q[j][4] = ((j + 1) * 10) + (j + 3);
            j++;
            q[j][3] = j + 1;
            j++;
            q[j][4] = ((j + 1) * 10) + (j - 1);
            j++;
        } else if (reg[i] == ')' && reg[i + 1] == '*') {
            q[0][4] = ((j + 1) * 10) + 1;
            q[j][4] = ((j + 1) * 10) + 1;
            j++;
        }
        i++;
    }

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
