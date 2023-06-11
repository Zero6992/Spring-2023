#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310;
const int INF = 1e9;
map<string, int> city_id;
vector<string> city_name;
int adj[MAXN][MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;
    city_name.resize(N+1);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j) adj[i][j] = 0;
            else adj[i][j] = INF;
        }
    }
    for(int i = 0; i < M; i++){
        string t1, t2;
        int d;
        cin >> t1 >> t2 >> d;
        if(!city_id[t1]){
            city_id[t1] = city_id.size();
            city_name[city_id[t1]] = t1;
        }
        if(!city_id[t2]){
            city_id[t2] = city_id.size();
            city_name[city_id[t2]] = t2;
        }
        adj[city_id[t1]][city_id[t2]] = min(adj[city_id[t1]][city_id[t2]], d);
        adj[city_id[t2]][city_id[t1]] = min(adj[city_id[t2]][city_id[t1]], d);
    }

    // Floyd-Warshall Algorithm
    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }

    vector<int> stops(K);
    for(int i = 0; i < K; i++){
        string s;
        cin >> s;
        stops[i] = city_id[s];
    }

    int res = 0;
    for(int i = 0; i < K - 1; i++){
        res += adj[stops[i]][stops[i+1]];
    }

    cout << res << "\n";

    return 0;
}
