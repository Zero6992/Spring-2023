#include<bits/stdc++.h>
using namespace std;

typedef pair<double, int> pi;

vector<vector<pair<int, double>>> adj;
vector<double> prob;
vector<bool> visited;

void solve(int start) {
    priority_queue<pi> q;
    q.push({0, start});
    prob[start] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            double p = edge.second;

            if (prob[u] + p > prob[v]) {
                prob[v] = prob[u] + p;
                q.push({prob[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    adj.assign(n, vector<pair<int, double>>());
    prob.assign(n, -1e9);
    visited.assign(n, false);

    for (int i = 0; i < m; i++) {
        int a, b;
        double p;
        cin >> a >> b >> p;

        adj[a].push_back({b, log(p)});
        adj[b].push_back({a, log(p)});
    }

    int start, end;
    cin >> start >> end;

    solve(start);

    cout << fixed << setprecision(3) << exp(prob[end]) << '\n';

    return 0;
}
