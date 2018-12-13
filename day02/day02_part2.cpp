#include<iostream>
#include<vector>
#include<set>
#include<fstream>

bool compare_strings(std::string a, std::string b) {
    int missed = -1;
    bool found = false;
    
    for (int i = 0; i < a.length(); i++) {
        if (a.at(i) != b.at(i)) {
            if (missed != -1) {
                missed = -1;
                break;
            }
            missed = i;
        }

        if (i == a.length() - 1) {
            found = true;
            std::cout << a << " matches\n" << b << " except on pos " << missed << "\n";
            break;
        }
    }

    if (!found) { 
        return false;
    }

    std::cout << "Matching characters: ";

    for (int i = 0; i < a.length(); i++) {
        if (i != missed) {
            std::cout << a.at(i);
        }
    }
    std::cout << "\n";
    return true;
}

int main() {
    std::fstream input("input");
    int numTwice = 0;
    int numTrice = 0;

    std::string line;
    std::vector<std::string> lines;

    while(std::getline(input, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            if (compare_strings(lines.at(i), lines.at(j))) {
                goto dn; // :o
            }
        }
    }
dn:

    return 0;
}