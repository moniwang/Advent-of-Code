#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void add(double& sum, char sign, double num) {
    switch(sign) {
        case '-':
            sum -= num;
            break;
        case '+':
            sum += num;
            break;
    }
}

int main() {

    vector<char> signs;
    vector<double> list;

    char sign;
    double num = 0;

    unordered_set<double> nums;
    double sum = 0;

    bool flag = false;

    while (cin >> sign >> num) {
        add(sum, sign, num);
        signs.push_back(sign);
        list.push_back(num);

        if (!flag) {
            if (nums.find(sum) != nums.end()) {
                cout << "Repeated: " << sum << "\n";
                flag = true;
            }
            else
                nums.insert(sum);
        }
    }

    cout << "Sum: " << sum << "\n";

    int index = 0;
    int size = (int) list.size();

    while (!flag) {
        
        add(sum, signs[index], list[index]);

        if (nums.find(sum) != nums.end()) {
            cout << "Repeated: " << sum << "\n";
            flag = true;
        }
        else
            nums.insert(sum);
            index = (index+1) % size;
    }
}

