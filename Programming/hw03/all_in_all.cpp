#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s, t;
    while (cin >> s >> t) {
        auto it = t.begin();
        bool isSubsequence = true;
        for (char c : s) {
            it = find(it, t.end(), c);
            if (it == t.end()) {
                isSubsequence = false;
                break;
            }
            ++it;  // Move iterator to next position for the next find operation
        }
        if (isSubsequence)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
