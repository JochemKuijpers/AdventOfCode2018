#include<iostream>
#include<string>
#include<fstream>

int main()
{
    std::ifstream input("input");
    std::string line;
    int total = 0;
    while (std::getline(input, line)) {
        if (line.empty()) break;
        int diff = std::stoi(line, nullptr);
        total += diff;
    }
    std::cout << total << "\n";
}
