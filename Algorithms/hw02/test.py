from collections import defaultdict

def bfs(match, dist, N, M):
    queue = []
    for u in range(1, N + 1):
        if match[u] == 0:
            dist[u] = 0
            queue.append(u)
        else:
            dist[u] = float("inf")
    dist[0] = float("inf")
    
    while queue:
        u = queue.pop(0)
        if u != 0:
            for v in adj[u]:
                if dist[match[v]] == float("inf"):
                    dist[match[v]] = dist[u] + 1
                    queue.append(match[v])
    return dist[0] != float("inf")


def dfs(match, dist, u):
    if u == 0:
        return True
    for v in adj[u]:
        if dist[match[v]] == dist[u] + 1 and dfs(match, dist, match[v]):
            match[u] = v
            match[v] = u
            return True
    dist[u] = float("inf")
    return False


def hopcroft_karp(N, M, flight_routes):
    global adj
    adj = defaultdict(list)
    for u, v in flight_routes:
        adj[u].append(N + v)
    match = [0] * (N + M + 1)
    dist = [0] * (N + M + 1)
    matching = 0
    
    while bfs(match, dist, N, M):
        for u in range(1, N + 1):
            if match[u] == 0 and dfs(match, dist, u):
                matching += 1
    return matching

# example 1
N, M = 3, 3
R = 3
flight_routes = [(1, 3), (2, 1), (3, 2)]
print(hopcroft_karp(N, M, flight_routes))  # Output: 2

# example 2
N, M = 5, 3
R = 4
flight_routes = [(2, 2), (2, 3), (4, 1), (5, 1)]
print(hopcroft_karp(N, M, flight_routes))  # Output: 1

# example 3
N, M = 10, 10
R = 11
flight_routes = [(3, 7), (7, 4), (2, 8), (7, 7), (1, 2), (3, 4), (9, 2), (4, 9), (5, 8), (6, 8), (10, 6)]
print(hopcroft_karp(N, M, flight_routes))  # Output: 3
