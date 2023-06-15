#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 105
#define INF 0x3f3f3f3f

int capacity[MAXN][MAXN];
int parent[MAXN];
int adj[MAXN][MAXN];
int numAdj[MAXN];
int N;

int bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    parent[s] = s;
    int queue[MAXN], qh = 0, qt = 0;
    queue[qt++] = s;
    while (qh != qt && parent[t] == -1) {
        int u = queue[qh++];
        for (int i = 0; i < numAdj[u]; i++) {
            int v = adj[u][i];
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                queue[qt++] = v;
            }
        }
    }
    return parent[t] != -1;
}

int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int u = t, delta = INF;
        while (u != s) {
            delta = capacity[parent[u]][u] < delta ? capacity[parent[u]][u] : delta;
            u = parent[u];
        }
        u = t;
        while (u != s) {
            capacity[parent[u]][u] -= delta;
            capacity[u][parent[u]] += delta;
            u = parent[u];
        }
        flow += delta;
    }
    return flow;
}

int main() {
    scanf("%d", &N);
    int s = N, t = N + 1;
    int totalOfficers = 0;
    int requiredOfficers = 0;
    for (int i = 0; i < N; i++) {
        int a;
        scanf("%d", &a);
        totalOfficers += a;
        capacity[s][i] = a;
        adj[s][numAdj[s]++] = i;
    }
    for (int i = 0; i < N; i++) {
        int b;
        scanf("%d", &b);
        requiredOfficers += b;
        capacity[i][t] = b;
        adj[i][numAdj[i]++] = t;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x;
            scanf("%d", &x);
            if (i != j) {
                capacity[i][j] = x;
                adj[i][numAdj[i]++] = j;
            }
        }
    }
    int maxFlowValue = maxFlow(s, t);
    printf("%d\n", requiredOfficers > maxFlowValue ? requiredOfficers - maxFlowValue : 0);
    return 0;
}
