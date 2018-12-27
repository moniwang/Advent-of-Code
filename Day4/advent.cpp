#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

struct Schedule {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int ID;
};

struct ScheduleCompare {
  bool operator() (const Schedule& lhs, const Schedule& rhs) const{
    if (lhs.month < rhs.month) {
        return true;
    }
    else if (lhs.month == rhs.month) {
        if (lhs.day < rhs.day) {
            return true;
        }
        else if (lhs.day == rhs.day) {
            if (lhs.hour < rhs.hour) {
                return true;
            }
            else if (lhs.hour == rhs.hour) {
                if (lhs.minute < rhs.minute) {
                    return true;
                }
            }
        }
    }
    return false;
  }
};


int main() {
    set<Schedule, ScheduleCompare> calendar;
    unordered_map<int, int> sleep;
    unordered_map<int, vector<int> > guards;

    string info;
    char trash;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int ID;

    while (cin >> trash >> year >> trash >> month >> trash >> day >> hour
           >> trash >> minute >> trash >> info) {
        switch(info[0]) {
            case 'G':
                cin >> trash >> ID;
                getline(cin, info);
                break;
            case 'f':
                ID = -1;
                getline(cin, info);
                break;
            case 'w':
                ID = -2;
                getline(cin, info);
                break;
        }
        calendar.insert({year, month, day, hour, minute, ID});
    }


    auto it = calendar.begin();

    int currentID = it->ID;
    int sleptMin = 0;
    int wokeMin = 0;

    it++;

    bool slept = false;
    for (; it != calendar.end(); it++) {
        if (it->ID == -1) {
            slept = true;
            if (it->hour == 23) {
                sleptMin = it->minute - 60;
            }
            else {
                sleptMin = it->minute;
            }
            guards[currentID].push_back(sleptMin);
        }
        else if (it->ID == -2) {
            wokeMin = it->minute;
            guards[currentID].push_back(wokeMin);
        }
        else {
            if (slept) {
                sleep[currentID] += (wokeMin - sleptMin);
                slept = false;
            }
            currentID = it->ID;
        }
    }

    int currMaxSleep = 0;
    int currID;
    for (auto it = sleep.begin(); it != sleep.end(); ++it) {
        if (it->second > currMaxSleep) {
            currID = it->first;
            currMaxSleep = it->second;
        }
    }

    cout << "Guard #" << currID << " slept for " << currMaxSleep
         << " minutes.\n";
    
    map<int, int> minutes;

    for (int i = 0; i < (int) guards[currID].size(); i++) {
        for (int j = guards[currID][i]; j < guards[currID][i+1]; j++) {
            minutes[j]++;
        }
        i++;
    }

    int maxTimes = 0;
    int currMin = 0;
    for (auto it = minutes.begin(); it != minutes.end(); ++it) {
        if (it->second > maxTimes) {
            currMin = it->first;
            maxTimes = it->second;
        }
    }

    cout << "He slept the most at minute " << currMin << ".\n";

    // PART 2

    map<int, unordered_map<int, int> > allMinutes;

    for (auto it = guards.begin(); it != guards.end(); it++) {
        for (int i = 0; i < (int) it->second.size(); i++) {
            for (int j = it->second[i]; j < it->second[i+1]; j++) {
                allMinutes[j][it->first]++;
            }
            i++;
        }
    }

    int guardNum = 0;
    int minNum = 0;
    int diff = 0;

    for (auto it = allMinutes.begin(); it != allMinutes.end(); ++it) {
        map<int, int> minutesCheck;
        for (auto ti = it->second.begin(); ti != it->second.end(); ++ti) {
            minutesCheck[ti->second] = ti->first;
        }
        auto iter = minutesCheck.end();
        iter--;
        if (iter->first > diff) {
            diff = iter->first;
            guardNum = iter->second;
            minNum = it->first;
        }
    }

    cout << "Guard #" << guardNum << " slept at minute " << minNum << ".\n";

}

