#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_set>

int main() {
    std::fstream input("input");
    std::string line;
    std::unordered_set<u_int64_t> claims;
    std::unordered_set<u_int64_t> duplicates;
    int numDuplicate = 0;

    while (std::getline(input, line)) {
        if (line.empty()) { break; }
        std::stringstream ss(line);
        char pound, at, comma, colon, times;
        int n, x, y, w, h;
        ss >> pound >> n >> at >> x >> comma >> y >> colon >> w >> times >> h;

        for (int i = x; i < x + w; i++) {
            for (int j = y; j < y + h; j++) {
                auto key = (((u_int64_t)i) << 32) | (u_int64_t) j;
                if (claims.find(key) != claims.end()) {
                    if (duplicates.find(key) == duplicates.end()) {
                        duplicates.insert(key);
                        numDuplicate++;
                    }
                } else {
                    claims.insert(key);
                }
            }
        }
    }

    std::cout << numDuplicate << "\n";

    return 0;
}