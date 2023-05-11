#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n, set_number = 1;
    while (std::cin >> n && n != 0) {
        std::vector<int> stacks(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> stacks[i];
        }

        int total_bricks = std::accumulate(stacks.begin(), stacks.end(), 0);
        int target_height = total_bricks / n;
        int moves = 0;

        for (int i = 0; i < n; ++i) {
            if (stacks[i] > target_height) {
                moves += stacks[i] - target_height;
            }
        }

        std::cout << "Set #" << set_number++ << std::endl;
        std::cout << "The minimum number of moves is " << moves << "." << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
