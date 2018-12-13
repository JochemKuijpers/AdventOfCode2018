#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>
#include<unordered_set>

int main() {
    std::fstream input("input");
    std::string line;
    std::unordered_map<u_int64_t, int> claims;
    std::unordered_set<int> untouchedIds;
    int numDuplicate = 0;

    while (std::getline(input, line)) {
        if (line.empty()) { break; }
        std::stringstream ss(line);
        char pound, at, comma, colon, times;
        int n, x, y, w, h;
        ss >> pound >> n >> at >> x >> comma >> y >> colon >> w >> times >> h;

        untouchedIds.insert(n);

        for (int i = x; i < x + w; i++) {
            for (int j = y; j < y + h; j++) {
                auto key = (((u_int64_t)i) << 32) | (u_int64_t) j;
                auto el = claims.find(key);

                if (el != claims.end()) {
                    untouchedIds.erase(el->second);
                    untouchedIds.erase(n);
                }
                claims[key] = n;
            }
        }
    }

    for (const int &x : untouchedIds) {
        std::cout << "claim " << x << " is untouched.\n";
    }

    return 0;
}