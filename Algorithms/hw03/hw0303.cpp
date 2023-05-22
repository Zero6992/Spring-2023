#include <bits/stdc++.h>
using namespace std;

#define INF (int)1e9
#define MAXN 1005
typedef pair<int, int> ii;

int N, M;
char grid[MAXN][MAXN];
int lavaTime[MAXN][MAXN], escapeTime[MAXN][MAXN];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
ii bed, door;

bool isValid(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < M;
}

void bfsLava()
{
    queue<pair<ii, int>> q;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (grid[i][j] == 'L')
            {
                q.push({{i, j}, 0});
                lavaTime[i][j] = 0;
            }
            else
            {
                lavaTime[i][j] = INF;
            }
        }
    }
    while (!q.empty())
    {
        auto front = q.front();
        q.pop();
        ii u = front.first;
        int t = front.second;
        for (int i = 0; i < 4; i++)
        {
            int x = u.first + dx[i], y = u.second + dy[i];
            if (isValid(x, y) && grid[x][y] == 'C' && t + 1 < lavaTime[x][y])
            {
                lavaTime[x][y] = t + 1;
                q.push({{x, y}, t + 1});
            }
        }
    }
}

void bfsEscape() {
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
            escapeTime[i][j] = -INF;
    escapeTime[bed.first][bed.second] = lavaTime[bed.first][bed.second];
    priority_queue<pair<int, ii>> q; 
    q.push({escapeTime[bed.first][bed.second], bed});
    while(!q.empty()) {
        auto front = q.top(); q.pop();
        ii u = front.second; int t = front.first;
        for(int i = 0; i < 4; i++) {
            int x = u.first + dx[i], y = u.second + dy[i];
            if(isValid(x, y) && min(t, lavaTime[x][y] - 1) > escapeTime[x][y]) {
                escapeTime[x][y] = min(t, lavaTime[x][y] - 1);
                q.push({escapeTime[x][y], {x, y}});
            }
        }
    }
}


int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'B')
                bed = {i, j};
            if (grid[i][j] == 'D')
                door = {i, j};
        }
    bfsLava();
    bfsEscape();

if(escapeTime[door.first][door.second] <= 0)
    cout << -1 << endl;
else
    cout << escapeTime[door.first][door.second] << endl;


    return 0;
}
