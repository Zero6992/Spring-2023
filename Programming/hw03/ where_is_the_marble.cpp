#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, q, query, case_number = 1;

    while (std::cin >> n >> q && n != 0 && q != 0) {
        std::vector<int> marbles(n);

        for (int i = 0; i < n; ++i) {
            std::cin >> marbles[i];
        }

        std::sort(marbles.begin(), marbles.end());

        std::cout << "CASE# " << case_number++ << ":" << std::endl;

        for (int i = 0; i < q; ++i) {
            std::cin >> query;
            auto found = std::lower_bound(marbles.begin(), marbles.end(), query);

            if (found != marbles.end() && *found == query) {
                std::cout << query << " found at " << (found - marbles.begin() + 1) << std::endl;
            } else {
                std::cout << query << " not found" << std::endl;
            }
        }
    }

    return 0;
}
