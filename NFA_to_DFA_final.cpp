// C++ Program to convert e-nfa to DFA

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#define MAX_LEN 100

using namespace std;


struct DFA {
    string states;
    int count;
};

int last_index = 0;
int symbols = 2;
vector<DFA> dfa_states;
vector<vector<string>> NFA_TABLE(MAX_LEN, vector<string>(symbols + 1));
vector<vector<string>> DFA_TABLE(MAX_LEN, vector<string>(symbols));


void reset(vector<int>& ar, int size) {
    fill(ar.begin(), ar.end(), 0);
}


void check(vector<int>& ar, const string& S) {
    for (char c : S) {
        ar[c - 65]++;
    }
}


void state(const vector<int>& ar, int size, string& S) {
    for (int i = 0; i < size; i++) {
        if (ar[i] != 0) {
            S += (char)(65 + i);
        }
    }
}


int closure(const vector<int>& ar, int size) {
    for (int i = 0; i < size; i++) {
        if (ar[i] == 1) return i;
    }
    return 100;
}


int indexing(const vector<DFA>& dfa) {
    for (size_t i = 0; i < dfa.size(); i++) {
        if (dfa[i].count == 0) return 1;
    }
    return -1;
}


void display_closure(int states, vector<int>& closure_ar, vector<string>& closure_table,
                     const vector<vector<string>>& NFA_TABLE) {
    for (int i = 0; i < states; i++) {
        reset(closure_ar, states);
        closure_ar[i] = 2;

        if (NFA_TABLE[i][symbols] != "-") {
            string buffer = NFA_TABLE[i][symbols];
            check(closure_ar, buffer);
            int z = closure(closure_ar, states);

            while (z != 100) {
                if (NFA_TABLE[z][symbols] != "-") {
                    buffer = NFA_TABLE[z][symbols];
                    check(closure_ar, buffer);
                }
                closure_ar[z]++;
                z = closure(closure_ar, states);
            }
        }

        string S;
        state(closure_ar, states, S);
        closure_table[i] = S;
        cout << "\n e-Closure (" << (char)(65 + i) << ") :\t" << closure_table[i] << "\n";
    }
}


int new_states(vector<DFA>& dfa, const string& S) {
    for (size_t i = 0; i < dfa.size(); i++) {
        if (dfa[i].states == S) return 0;
    }
    dfa.push_back(DFA{S, 0});
    return 1;
}


void trans(const string& S, int M, const vector<string>& clsr_t, int st,
           const vector<vector<string>>& NFT, string& TB) {
    vector<int> arr(st, 0);
    string temp, temp2;

    for (char c : S) {
        int j = c - 65;
        string temp = NFT[j][M];

        if (temp != "-") {
            for (char g : temp) {
                int k = g - 65;
                temp2 = clsr_t[k];
                check(arr, temp2);
            }
        }
    }

    state(arr, st, temp);
    TB = temp.empty() ? "-" : temp;
}


void display_DFA(int last_index, const vector<DFA>& dfa_states, const vector<vector<string>>& DFA_TABLE) {
    cout << "\n\n********************************************************\n\n";
    cout << "\t\t DFA TRANSITION STATE TABLE \t\t \n\n";
    cout << "\n STATES OF DFA :\t\t";
    for (int i = 1; i < last_index; i++) {
        cout << dfa_states[i].states << ", ";
    }
    cout << "\n\n GIVEN SYMBOLS FOR DFA: \t";
    for (int i = 0; i < symbols; i++) {
        cout << i << ", ";
    }
    cout << "\n\nSTATES\t";
    for (int i = 0; i < symbols; i++) {
        cout << "| " << i << "\t";
    }
    cout << "\n--------+-----------------------\n";
    for (int i = 0; i < last_index; i++) {
        cout << dfa_states[i].states << "\t";
        for (int j = 0; j < symbols; j++) {
            cout << "| " << DFA_TABLE[i][j] << "\t";
        }
        cout << "\n";
    }
}


int main() {
    int states = 6;

    cout << "\n STATES OF NFA :\t\t";
    for (int i = 0; i < states; i++) {
        cout << (char)(65 + i) << ", ";
    }
    cout << "\n\n GIVEN SYMBOLS FOR NFA: \t";
    for (int i = 0; i < symbols; i++) {
        cout << i << ", ";
    }
    cout << "eps\n\n";


    NFA_TABLE[0] = {"FC", "-", "BF"};
    NFA_TABLE[1] = {"-", "C", "-"};
    NFA_TABLE[2] = {"-", "-", "D"};
    NFA_TABLE[3] = {"E", "A", "-"};
    NFA_TABLE[4] = {"A", "-", "BF"};
    NFA_TABLE[5] = {"-", "-", "-"};


    cout << "\n NFA STATE TRANSITION TABLE \n\n\n";
    cout << "STATES\t";
    for (int i = 0; i < symbols; i++) {
        cout << "| " << i << "\t";
    }
    cout << "eps\n";
    cout << "--------+------------------------------------\n";
    for (int i = 0; i < states; i++) {
        cout << (char)(65 + i) << "\t";
        for (int j = 0; j <= symbols; j++) {
            cout << "| " << NFA_TABLE[i][j] << "\t";
        }
        cout << "\n";
    }

    vector<int> closure_ar(states);
    vector<string> closure_table(states);


    display_closure(states, closure_ar, closure_table, NFA_TABLE);

    dfa_states.push_back(DFA{"-", 1});
    dfa_states[last_index++].count = 1;

    string buffer = closure_table[0];
    dfa_states.push_back(DFA{buffer, 0});

    int Sm = 1, ind = 1;
    int start_index = 1;


    while (ind != -1) {
        dfa_states[start_index].count = 1;
        Sm = 0;
        for (int i = 0; i < symbols; i++) {
            string T_buf;
            trans(buffer, i, closure_table, states, NFA_TABLE, T_buf);

            DFA_TABLE[last_index][i] = T_buf;
            Sm += new_states(dfa_states, T_buf);
        }

        ind = indexing(dfa_states);
        if (ind != -1)
            buffer = dfa_states[++start_index].states;

        last_index++;
    }


    display_DFA(last_index, dfa_states, DFA_TABLE);

    return 0;
}
