#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>

int main() {
    int C;
    std::cin >> C;

    for (int t = 0; t < C; ++t) {
        int N;
        std::cin >> N;
        std::vector<int> grades(N);

        for (int i = 0; i < N; ++i) {
            std::cin >> grades[i];
        }

        double average = static_cast<double>(std::accumulate(grades.begin(), grades.end(), 0)) / N;
        int above_average_count = std::count_if(grades.begin(), grades.end(), [&](int grade) {
            return grade > average;
        });

        double percentage = static_cast<double>(above_average_count) * 100 / N;
        std::cout << std::fixed << std::setprecision(3) << percentage << "%\n";
    }

    return 0;
}
