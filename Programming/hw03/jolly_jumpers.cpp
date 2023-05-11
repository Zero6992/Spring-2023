#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> sequence(n);
        for (int i = 0; i < n; ++i) {
            cin >> sequence[i];
        }

        if(n == 1) {
            cout << "Jolly" << endl;
            continue;
        }

        vector<int> diff(n);
        adjacent_difference(sequence.begin(), sequence.end(), diff.begin());

        for(int i = 1; i < n; ++i) {
            diff[i] = abs(diff[i]);
        }

        sort(diff.begin()+1, diff.end());

        if (all_of(diff.begin()+1, diff.end(), [n = 1](int x) mutable { return x == n++; })) {
            cout << "Jolly" << endl;
        }
        else {
            cout << "Not jolly" << endl;
        }
    }

    return 0;
}
