#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int s[MAXN], maxNum[MAXN], maxPos[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> s[i];
        maxPos[s[i]] = i;
    }

    int ans = 0, curMax = 0;
    for (int i = 1; i <= M; i++) {
        if (s[i] > curMax){
            curMax = s[i];
            maxNum[s[i]] = ++ans;
        } 
        else {
            maxNum[s[i]] = max(maxNum[s[i]], maxNum[curMax]);
        }
    }

    cout << ans << "\n";

    return 0;
}
