#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int timer;
vector<vector<int>> adj;
vector<pair<int,int>> bridges;
vector<int> vis, in, low;

void dfs(int node, int par) {
    vis[node] = 1;
    in[node] = low[node] = timer++;
    for(int child : adj[node]) {
        if(child == par) continue;
        if(vis[child]) {
            low[node] = min(low[node], in[child]);
        }
        else {
            dfs(child, node);
            if(low[child] > in[node]) {
                bridges.push_back({min(node, child), max(node, child)});
            }
            low[node] = min(low[node], low[child]);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    timer = 0;
    adj.resize(N);
    vis.resize(N, 0);
    in.resize(N, 0);
    low.resize(N, 0);

    for(int i=0; i<M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i=0; i<N; i++) {
        if(!vis[i]) {
            dfs(i, -1);
        }
    }

    sort(bridges.begin(), bridges.end());

    if(bridges.empty()) {
        cout << "No Critical Road" << endl;
    } else {
        for(auto bridge : bridges) {
            cout << bridge.first << " " << bridge.second << endl;
        }
    }

    return 0;
}
