#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::ostringstream oss;
        for (int i = 1; i <= n; ++i) {
            oss << i;
        }

        std::string str = oss.str();
        std::string output = "";
        for (int i = 0; i <= 9; ++i) {
            int count = std::count(str.begin(), str.end(), '0' + i);
            output += std::to_string(count) + (i == 9 ? "\n" : " ");
        }
        std::cout << output;
    }

    return 0;
}
