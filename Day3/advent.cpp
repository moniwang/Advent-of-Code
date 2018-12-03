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
    char info;

    vector<Claim> claims;
    vector<int> v (1000, 0);
    vector<vector<int>> fabric(1000, v);

    int claimNum, col, row, sizeX, sizeY;
    while (cin >> info >> claimNum >> info >> col >> info 
           >> row >> info >> sizeX >> info >> sizeY) {
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

