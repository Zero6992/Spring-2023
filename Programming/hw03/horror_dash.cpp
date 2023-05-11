#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        int N;
        std::cin >> N;
        std::vector<int> speeds(N);

        for (int i = 0; i < N; ++i) {
            std::cin >> speeds[i];
        }

        int max_speed = *std::max_element(speeds.begin(), speeds.end());
        std::cout << "Case " << t << ": " << max_speed << std::endl;
    }

    return 0;
}
