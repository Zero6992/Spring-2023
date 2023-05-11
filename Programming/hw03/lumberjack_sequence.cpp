#include <iostream>
#include <vector>
#include <algorithm>

bool check_lumberjacks(const std::vector<int>& beards) {
    return std::is_sorted(beards.begin(), beards.end()) || std::is_sorted(beards.rbegin(), beards.rend());
}

int main() {
    int n;
    std::cin >> n;

    std::cout << "Lumberjacks:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::vector<int> beards(10);
        for (int j = 0; j < 10; ++j) {
            std::cin >> beards[j];
        }

        if (check_lumberjacks(beards)) {
            std::cout << "Ordered" << std::endl;
        } else {
            std::cout << "Unordered" << std::endl;
        }
    }

    return 0;
}
