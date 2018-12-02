#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Given a list of strings as from cin

int main() {

    // PART ONE
    // Finds the number of strings that have exactly two of a letter
    // Finds the number of string that have exactly three of a letter
    // Multiplies the two and prints to output
    string boxID;
    vector<string> allIDs;

    double hadTwo = 0;
    double hadThree = 0;

    while (cin >> boxID) {
        allIDs.push_back(boxID);
        
        bool flagTwo = false;
        bool flagThree = false;

        unordered_map<char, double> chars;

        for (int i = 0; i < (int) boxID.size(); ++i) {
            ++chars[boxID[i]];
        }

        auto it = chars.begin();

        while (it != chars.end()) {
            if(it->second == 2) {
                flagTwo = true;
            }
            else if (it->second == 3) {
                flagThree = true;
            }
            if (flagTwo && flagThree) {
                break;
            }
            ++it;
        }

        if (flagTwo) hadTwo++;
        if (flagThree) hadThree++;
    }

    cout << hadTwo*hadThree << endl;

    // PART TWO
    // Finds two strings that have one differing character
    for (int j = 0; j < (int)allIDs.size(); ++j) {
        for (int k = 0; k < (int)allIDs.size(); ++k) {
            int diff = 0;
            for (int l = 0; l < (int)allIDs[j].size(); ++l) {
                if (allIDs[j][l] != allIDs[k][l]) {
                    ++diff;
                }
                if (diff == 2) {
                    break;
                }
            }
            if (diff == 1) {
                cout << allIDs[j] << endl;
                cout << allIDs[k] << endl;
                return 0;
            }
        }
    }
}

