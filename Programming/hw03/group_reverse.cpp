#include <iostream>
#include <string>
#include <algorithm>

void group_reverse(std::string &str, int group_size) {
    int n = str.size() / group_size;
    for (int i = 0; i < str.size(); i += n) {
        std::reverse(str.begin() + i, str.begin() + i + n);
    }
}

int main() {
    int group_count;
    std::string input;

    while (std::cin >> group_count && group_count != 0) {
        std::cin >> input;
        group_reverse(input, group_count);
        std::cout << input << std::endl;
    }

    return 0;
}
