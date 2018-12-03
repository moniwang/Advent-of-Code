#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Claim {
    int claimNum;
    int col;
    int row;
    int sizeX;
    int sizeY;
};

int main() {

    // PART ONE
    // Reading in claims and making the fabric

    string claim;

    vector<Claim> claims;
    vector<int> v (1000, 0);
    vector<vector<int>> fabric(1000, v);

    while (getline(cin, claim)) {
        
        size_t findAt = claim.find("@");
        size_t findCom = claim.find(",");
        size_t findCol = claim.find(":");
        size_t findX = claim.find("x");

        int claimNum = stoi(claim.substr(1, findAt-2));
        int col = stoi(claim.substr(findAt+2, findCom-findAt+2));
        int row = stoi(claim.substr(findCom+1, findCol-findCom+1));
        int sizeX = stoi(claim.substr(findCol+2, findX-findCol+2));
        int sizeY = stoi(claim.substr(findX+1));

        claims.push_back({claimNum, col, row, sizeX, sizeY});
    }

    for (int i = 0; i < (int)claims.size(); ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (j >= claims[i].row && j < (claims[i].row+claims[i].sizeY)) {
                for (int k = 0; k < 1000; ++k) {
                    if (k >= claims[i].col && k < (claims[i].col+claims[i].sizeX)) {
                        ++fabric[j][k];
                    }
                }
            }
        }
    }

    int sum = 0;
    for (int j = 0; j < 1000; ++j) {
        for (int k = 0; k < 1000; ++k) {
            if (fabric[j][k] >= 2) {
                ++sum;
            }
        }
    }

    cout << "Sum: " << sum << endl;

    // PART TWO
    // Checking for a non overlap claim

    for (int i = 0; i < (int) claims.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < 1000; ++j) {
            if (j >= claims[i].row && j < (claims[i].row+claims[i].sizeY)) {
                for (int k = 0; k < 1000; ++k) {
                    if (k >= claims[i].col && k < (claims[i].col+claims[i].sizeX)) {
                        if (fabric[j][k] >= 2) {
                            flag = false;
                        }
                    }
                }
            }
        }
        if (flag) {
            cout << "Does not overlap: " << claims[i].claimNum << endl;
        }
    }
}

