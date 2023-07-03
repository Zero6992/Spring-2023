#include <stdio.h>
#include <stdlib.h>

#define MAX 100005
#define INF 1000000007

typedef struct {
    int city;
    int cost;
    int max_cost;
} Node;

typedef struct {
    Node heap[MAX];
    int size;
} PriorityQueue;

void push(PriorityQueue *pq, int city, int cost, int max_cost) {
    int target = ++pq->size;

    while (target != 1 && cost < pq->heap[target / 2].cost) {
        pq->heap[target] = pq->heap[target / 2];
        target /= 2;
    }

    pq->heap[target].city = city;
    pq->heap[target].cost = cost;
    pq->heap[target].max_cost = max_cost;
}

Node pop(PriorityQueue *pq) {
    Node ret = pq->heap[1];
    Node temp = pq->heap[pq->size--];
    int parent = 1, child = 2;

    while (child <= pq->size) {
        if (child < pq->size && pq->heap[child].cost > pq->heap[child + 1].cost) {
            child++;
        }
        if (temp.cost <= pq->heap[child].cost) {
            break;
        }
        pq->heap[parent] = pq->heap[child];
        parent = child;
        child *= 2;
    }
    pq->heap[parent] = temp;
    return ret;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *graph[MAX] = {0};
    int *cost[MAX] = {0};
    int edge_count[MAX] = {0};
    int min_cost[MAX] = {0};
    int max_cost[MAX] = {0};
    PriorityQueue pq = {0};
    int visit[MAX] = {0};
    int city_count[MAX] = {0};
    int u, v, w;

    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);

        edge_count[u] += 1;
        edge_count[v] += 1;
        graph[u] = (int *)realloc(graph[u], sizeof(int) * (edge_count[u] + 1));
        graph[v] = (int *)realloc(graph[v], sizeof(int) * (edge_count[v] + 1));
        cost[u] = (int *)realloc(cost[u], sizeof(int) * (edge_count[u] + 1));
        cost[v] = (int *)realloc(cost[v], sizeof(int) * (edge_count[v] + 1));

        graph[u][edge_count[u]] = v;
        graph[v][edge_count[v]] = u;
        cost[u][edge_count[u]] = w;
        cost[v][edge_count[v]] = w;
    }

    for (int i = 2; i <= n; i++) {
        min_cost[i] = INF;
    }

    push(&pq, 1, 0, 0);

    while (pq.size != 0) {
        Node now = pop(&pq);

        if (visit[now.city]) {
            continue;
        }

        visit[now.city] = 1;
        min_cost[now.city] = now.cost;
        max_cost[now.city] = now.max_cost;

        for (int i = 1; i <= edge_count[now.city]; i++) {
            int next = graph[now.city][i];
            int next_cost = cost[now.city][i];
            if (visit[next]) {
                continue;
            }

            if (min_cost[next] >= now.cost + next_cost) {
                push(&pq, next, now.cost + next_cost, now.max_cost > next_cost ? now.max_cost : next_cost);
                if (min_cost[next] == now.cost + next_cost) {
                    city_count[next] = city_count[now.city] + 1 > city_count[next] ? city_count[now.city] + 1 : city_count[next];
                } else {
                    city_count[next] = city_count[now.city] + 1;
                }
            }
        }
    }

    printf("%d %d\n", min_cost[n] - max_cost[n], city_count[n] - 1);

    return 0;
}
