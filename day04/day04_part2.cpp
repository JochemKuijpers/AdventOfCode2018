#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

struct line_info {
    int date; // yyyymmdd   (decimal concatenation)
    int time; // minutes since 0:00
    int guard; // guard ID
    int type; // 0: start, 1: wake, 2: sleep
};

int main() {
    std::fstream input("input");
    std::string line;
    std::vector<line_info> lines;
    
    while(std::getline(input, line)) {
        if (line.empty()) { break; }
        
        char _;
        int year, month, day, hour, minute, guard, type;
        bool wake;
        std::string what;
        guard = -1;
        type = -1;

        std::stringstream ss(line);

        ss >> _ >> year >> _ >> month >> _ >> day >> _ >> hour >> _ >> minute >> _ >> what;
        if (what == "Guard") {
            ss >> _;
            ss >> guard; // guard number
            type = 0;
        }
        if (what == "wakes") {
            type = 1;
        }
        if (what == "falls") {
            type = 2;
        }

        lines.push_back((line_info){
                year * 10000 + month * 100 + day,
                hour * 60 + minute, 
                guard,
                type
            }
        );
    }
    std::sort(lines.begin(), lines.end(), [](line_info a, line_info b) {
        if (a.date < b.date) return true;
        if (a.date > b.date) return false;
        return (a.time < b.time);
    });

    int minutes_per_guard[10000 * 60] = {0};

    {
        int guard = -1;
        int fall_asleep_time = -1;
        for (const line_info &x : lines) {
            switch (x.type) {
                case 0:
                    guard = x.guard;
                    break;
                case 1:
                    for (int m = fall_asleep_time; m < x.time % 60; m++) {
                        minutes_per_guard[guard * 60 + m] += 1;
                    }
                    break;
                case 2:
                    fall_asleep_time = x.time % 60;
                    break;
            }
        }
    }
    
    // find which guard+minute is the max.
    int max = -1;
    int max_guard = -1;
    int max_minute = -1;
    for (int guard = 0; guard < 10000; guard++) {
        for (int m = 0; m < 60; m++) {
            if (minutes_per_guard[guard * 60 + m] > max) {
                max = minutes_per_guard[guard * 60 + m];
                max_guard = guard;
                max_minute = m;
            }
        }
    }

    std::cout << max_guard * max_minute << "\n";

    return 0;
}