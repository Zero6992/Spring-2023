// Consider the following question: What are some good algorithms that can handle this? Just describe your strategy, don't write the code yet

// description
// One day, Jason has nightmare that he wakes up and finds part of bedroom has been burned out with lava. Fortunately, due to the slow flow of lava, Jason has some time to escape from bed to door.
// There are five types of floor in Jason's bedroom, sizing N x M. Moreover, Jason wants to know that how long he can escape from bedroom.

// Input:
// The first line contains two space-seperated integer N,M, which indicate the height, width of Jason bedroom. For next N×M consisting of type L,O,C floor indicates the initial status of the bedroom.

// For all test data, it is guaranteed:
// • type L: Lava, and there may be a lot of lava. Lava will flow out 1 unit per second(the available direction are up, left, right, and down)
// • type O: Obstalcle, where lava cannot flow, and Jason can not go through.
// • type C: Common floor, where lava can flow.
// • type B: Bed, where lava cannot flow, and exists only one time.
// • type D: Door, where lava cannot flow, and exists only one time.

// Please tell Jason the latest time he can escape bedroom from B to D safely.

// Input:
// The first line contains two space-seperated integer N, M, which indicate the height, width of Jason bedroom. For next N x M consisting of type L,O,C floor indicates the initial status of the bedroom.
// For all test data, it is guaranteed:

// • 1 ≤ N ≤ 10^3
// • 1 ≤ M ≤ 10^3
// • B and D are not adjacent to each other.
// • There are no infinte outcomes.


// Output:

// 1. Jason is not limited to taking only one step per second. As long as there is a road available, he can continue moving.
// 2. The output should indicate the latest time by which Jason must reach the road before it gets blocked by lava
// 3. Please print a number indicating the latest time Jason can escape bedroom from B to D. If Jason cannot escape bedroom after 1 second, print −1.


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v))
        {
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
            fa[find(u)] = find(v);
        }
    }

    // Find the path from B to D
    vector<bool> visited(n + 1, false);
    dfs(1, n, adj, visited);

    // Find the maximum weight in the path
    int maxWeight = 0;
    for (int i = 0; i < path.size(); i++)
    {
        maxWeight = max(maxWeight, path[i]);
    }
    cout << maxWeight << endl;
    return 0;
}