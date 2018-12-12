#include<iostream>
#include<unordered_set>
#include<fstream>

int main() {
    std::fstream input("input");
    int numTwice = 0;
    int numTrice = 0;

    std::string line;

    while(std::getline(input, line)) {
        const char* str = line.c_str();

        std::unordered_set<char> foundDouble;
        std::unordered_set<char> foundTriple;
        std::unordered_set<char> foundMoreThanThat;

        for (int i = 0; i < line.length(); i++) {
            for (int j = i+1; j < line.length(); j++) {
                if (str[i] != str[j]) { continue; }
                foundDouble.insert(str[i]);
                for (int k = j+1; k < line.length(); k++) {
                    if (str[i] != str[k]) { continue; }
                    foundTriple.insert(str[i]);
                    for (int l = k+1; l < line.length(); l++) {
                        if (str[i] != str[l]) { continue; }
                        foundMoreThanThat.insert(str[i]);
                    }
                }
            }
        }

        for (const char &x : foundMoreThanThat) {
            foundDouble.erase(x);
            foundTriple.erase(x);
        }

        for (const char &x : foundTriple) {
            foundDouble.erase(x);
        }

        if (foundDouble.size()) { numTwice++; }
        if (foundTriple.size()) { numTrice++; }
    }

    std::cout << numTwice << " × " << numTrice << " = ";

    std::cout << numTwice * numTrice << "\n";

    return 0;
}