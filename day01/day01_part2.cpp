#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

int n = 0;

bool scan_file(int* total, std::vector<int>* freqs)
{
    std::ifstream input("input");
    std::string line;

    while (std::getline(input, line))
    {
        if (line.empty()) break;

        int diff = std::stoi(line, nullptr);
        *total += diff;

        for (int &a : *freqs) 
        {
            if (a == *total) 
            { 
                return true; 
            }
        }
        freqs->push_back(*total);
        
    }

    std::cout << "iter " << n++ << "\n";
    return false;
}

int main()
{
    std::vector<int> freqs;
    int total = 0;

    freqs.push_back(total);
    while (!scan_file(&total, &freqs));

    std::cout << total << "\n";
}
