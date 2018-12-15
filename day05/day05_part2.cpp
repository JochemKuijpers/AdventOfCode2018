#include<iostream>
#include<fstream>
#include<vector>
#include<string>

int react_polymer(std::vector<char> sequence) {
    bool changes;
    int length, skipped;

    do {
        length = 0;
        skipped = 0;
        changes = false;
        char prev = -1, curr = -1;
        for (int i = 0; i < sequence.size(); i++) {
            if (sequence[i] == 0) { 
                skipped++;
                continue;
            }
            curr = sequence[i];
            if (prev != -1 && (curr-prev)*(curr-prev) == 32*32) {
                sequence[i] = 0;
                sequence[i-1-skipped] = 0;
                curr = -1;
                prev = -1;
                changes = true;
            } else {
                length++;
            }
            skipped = 0;
            prev = curr;
        }
    } while (changes);

    return length;
}

int main() {
    std::fstream input("input");
    std::vector<char> sequence;
    std::string line;

    while (std::getline(input, line)) {
        for (int i = 0; i < line.length(); i++) {
            sequence.push_back(line.at(i));
        }
    }

    int min_length = 13371337, length;
    for (int c = 'A'; c < 'Z'; c++) {
        std::vector<char> altered_sequence = sequence;
        for (int i = 0; i < altered_sequence.size(); i++) {
            if (altered_sequence[i] == c || altered_sequence[i] == c + 32) { 
                altered_sequence[i] = 0;
            }
        }
        length = react_polymer(altered_sequence);
        if (length < min_length) {
            min_length = length;
        }
    }

    std::cout << min_length << "\n";
    return 0;
}
