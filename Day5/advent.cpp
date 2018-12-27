#include <iostream>
#include <algorithm>
#include <stack>
#include <stdio.h>
#include <ctype.h>
#include <vector>

using namespace std;

bool check (char letter, char checkWith) {
    char change;
    if (islower(letter)) {
        change = (char)toupper(letter);
    }
    else {
        change = (char)tolower(letter);
    }
    if (checkWith == change) {
        return true;
    }
    else {
        return false;
    }
}

int react(vector<char> polymers) {

    stack<char> letters;

    char polymer;

    for (int i = 0; i < (int) polymers.size(); ++i) {
        polymer = polymers[i];
        if (letters.empty()) {
            letters.push(polymer);
        }
        else {
            if (check(letters.top(), polymer)) {
                letters.pop();
            }
            else {
                letters.push(polymer);
            }
        }
    }

    return (int) letters.size();

}

int main() {

    vector<char> polymers;

    char polymer;

    while (cin >> polymer) {
        polymers.push_back(polymer);
    }

    cout << react(polymers) << " polymers remain.\n";

    // Part Two

    int minLength = 1000000000;

    for( char character = 'a'; character <= 'z' ; ++character) {
        vector<char> tempVec;
        for (int i = 0; i < (int) polymers.size(); ++i) {
            if (polymers[i] != character && polymers[i] != toupper(character)) {
                tempVec.push_back(polymers[i]);
            }
        }
        if (react(tempVec) < minLength) {
            minLength = react(tempVec);
        }
    }

    cout << "The shortest polymer is " << minLength << ".\n";
}

