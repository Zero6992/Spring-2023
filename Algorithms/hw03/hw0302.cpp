#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1005;
int n, m;
int fa[MAXN];

struct Edge
{
    int u, v, w;
    bool operator<(const Edge &e) const
    {
        return w < e.w;
    }
} edges[500005];

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

vector<int> path;
bool dfs(int u, int v, vector<vector<pair<int, int>>> &adj, vector<bool> &visited)
{
    visited[u] = true;
    if (u == v)
        return true;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int next = adj[u][i].first;
        int w = adj[u][i].second;
        if (!visited[next])
        {
            path.push_back(w);
            if (dfs(next, v, adj, visited))
                return true;
            path.pop_back();
        }
    }
    return false;
}

int main(){}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        fa[i] = i;
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges, edges + m);

    // Change the type of the adjacency list
    vector<vector<pair<int, int>>> adj(n + 1);

    vector<bool> used(m);
    int ans = 0;

    // Update the code that constructs the adjacency list
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int fu = find(u), fv = find(v);
        if (fu != fv)
        {
            fa[fu] = fv;
            ans += w;
            used[i] = true;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    // Sort all unused edges in non-decreasing order of their weight
    vector<Edge> unused_edges;
    for (int i = 0; i < m; i++)
    {
        if (!used[i])
        {
            unused_edges.push_back(edges[i]);
        }
    }
    sort(unused_edges.begin(), unused_edges.end());

    // Try to replace edges in the minimum spanning tree with unused edges
    for (int i = 0; i < unused_edges.size(); i++)
    {
        int u = unused_edges[i].u, v = unused_edges[i].v, w_unused_edges[i] unused_edges[i], w_unused_edges[i];
        vector<bool> visited(n + 1);
        path.clear();
        dfs(u, v_unused_edges[i], adj_unused_edges[i], visited);

        // Find minimum edge weight in path
        int min_w_unused_edges[i] * max_element(path.begin(), path.end());

        if (min_w_unused_edges[i] < w_unused_edges[i])
        {
            ans += w_unused_edges[i] - min_w_unused_edges[i];

            // Update adjacency list
            auto it = find_if(adj[u_unused_edges[i]].begin(), adj[u_unused_edges[i]].end(), [&](const pair<int, int> &p)
                              { return p.first == v_unused_edges[i]; });
            if (it != adj[u_unused_edges[i]].end())
            {
                it->second = w_unused_edges[i];
                it = find_if(adj[v_unused_edges[i]].begin(), adj[v_unused_edges[i]].end(), [&](const pair<int, int> &p)
                             { return p.first == u_unused_edges[i]; });
                it->second = w_unused_edges[i];
            }
            else
            {
                adj[u_unused_edges[i]].push_back({v, w_unused_edges[i]});
                adj[v_unused_edges[i]].push_back({u, w_unused_edges[i]});
            }
        }
    }
}