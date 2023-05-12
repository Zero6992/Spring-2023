#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <cctype>

std::string toLower(const std::string& str) {
    std::string lowerCaseStr;
    std::transform(str.begin(), str.end(), std::back_inserter(lowerCaseStr), ::tolower);
    return lowerCaseStr;
}

int main() {
    std::vector<std::string> words;
    std::map<std::string, int> sortedWords;

    std::string line;
    while (std::getline(std::cin, line) && line != "#") {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            std::string sortedWord = toLower(word);
            std::sort(sortedWord.begin(), sortedWord.end());
            words.push_back(word);
            sortedWords[sortedWord]++;
        }
    }

    std::vector<std::string> ananagrams;
    for (const auto &word : words) {
        std::string sortedWord = toLower(word);
        std::sort(sortedWord.begin(), sortedWord.end());
        if (sortedWords[sortedWord] == 1) {
            ananagrams.push_back(word);
        }
    }

    std::sort(ananagrams.begin(), ananagrams.end());
    for (const auto &word : ananagrams) {
        std::cout << word << '\n';
    }

    return 0;
}
