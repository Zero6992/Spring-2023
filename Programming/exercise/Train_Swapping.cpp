#include <iostream>
#include <vector>
using namespace std;

int count_swaps(vector<int>& carriages) {
    int swaps = 0;
    bool swapped;
    int n = carriages.size();

    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (carriages[j] > carriages[j + 1]) {
                swap(carriages[j], carriages[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return swaps;
}

int main() {
    int n, l;
    cin >> n;

    while (n--) {
        cin >> l;
        vector<int> carriages(l);

        for (int i = 0; i < l; i++) {
            cin >> carriages[i];
        }

        int swaps = count_swaps(carriages);
        cout << "Optimal train swapping takes " << swaps << " swaps." << endl;
    }

    return 0;
}
