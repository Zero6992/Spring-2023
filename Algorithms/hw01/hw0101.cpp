#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int n, Q;
    cin >> n >> Q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<pair<int, int>> sorted_restaurants;
    for (int i = 0; i < n; i++) {
        sorted_restaurants.insert({a[i], i});
    }

    for (int i = 0; i < Q; i++) {
        int operation_type;
        cin >> operation_type;

        if (operation_type == 1) {
            int x, v;
            cin >> x >> v;
            x--; // convert to 0-based index

            sorted_restaurants.erase({a[x], x});
            a[x] = v;
            sorted_restaurants.insert({v, x});
        } else if (operation_type == 2) {
            int x;
            cin >> x;
            x--; // convert to 0-based index

            auto it = sorted_restaurants.lower_bound({a[x], x});
            cout << distance(sorted_restaurants.begin(), it) + 1 << endl;
        }
    }

    return 0;
}
