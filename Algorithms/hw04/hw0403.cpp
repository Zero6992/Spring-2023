#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1e5 + 5;
vector<pii> graph[MAXN];
priority_queue<pii, vector<pii>, greater<pii>> pq;
int N, M;
ll dist[MAXN];
bool visited[MAXN];

void Dijkstra() {
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (auto &p : graph[u]) {
            int v = p.first, w = p.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    Dijkstra();

    ll minCost = dist[N];
    int maxFlight = 0, partyCities = 0;
    int u = N;
    while (u != 1) {
        for (auto &p : graph[u]) {
            int v = p.first, w = p.second;
            if (dist[u] == dist[v] + w) {
                u = v;
                maxFlight = max(maxFlight, w);
                if (v != 1 && v != N) partyCities++;
                break;
            }
        }
    }
    minCost -= maxFlight;
    cout << minCost << " " << partyCities << "\n";
    return 0;
}
