#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string word;
        bool isFirstWord = true;
        while (iss >> word) {
            std::reverse(word.begin(), word.end());
            if (!isFirstWord) {
                std::cout << " ";
            }
            std::cout << word;
            isFirstWord = false;
        }
        std::cout << "\n";
    }
    return 0;
}
