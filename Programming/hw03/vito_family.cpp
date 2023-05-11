#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int r;
        cin >> r;
        vector<int> s(r);
        for (int i = 0; i < r; ++i) {
            cin >> s[i];
        }
        // The optimal Vito's house would be the one located at the median of the relatives' houses
        nth_element(s.begin(), s.begin() + r / 2, s.end());
        int vitoHouse = s[r / 2];
        int totalDistance = accumulate(s.begin(), s.end(), 0, [vitoHouse](int a, int b) {
            return a + abs(b - vitoHouse);
        });
        cout << totalDistance << endl;
    }
    return 0;
}
