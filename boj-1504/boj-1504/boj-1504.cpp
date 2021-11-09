#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
typedef vector<vector<pair<int, int>>> wow;
int* cost;

void dijkstra(int start,wow& vec)
{
    priority_queue<pair<int, int>> pq;
    cost[start] = 0;
    pq.push({0,start});

    while (!pq.empty())
    {
        int d = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (cost[cur] < d) continue;
        for (int i = 0; i < vec[cur].size(); i++)
        {
            int next = vec[cur][i].first;
            int nextD = d + vec[cur][i].second;

            if (nextD < cost[next])
            {
                cost[next] = nextD;
                pq.push({-nextD,next});
            }
        }

    }

}

void init(int* arr,int n)
{
    for (int i = 0; i < n; i++) arr[i] = INT_MAX;
}

int main(void)
{
    int n, e;
    scanf("%d %d", &n, &e);
    cost = (int*)malloc((n+1)*sizeof(int));
    wow vec(n+1, vector<pair<int, int>>(0,{0,0}));
    
    init(cost, n + 1);

    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        vec[a].push_back({b,c});
        vec[b].push_back({ a,c });
    }
    int v1, v2;
    scanf("%d %d", &v1, &v2);

    dijkstra(1,vec);
    int i1 = cost[v1];
    int i2 = cost[v2];
    if (i1 == INT_MAX || i2 == INT_MAX)
    {
        printf("-1");
        free(cost);
        return 0;
    }

    init(cost, n + 1);
    dijkstra(v1, vec);
    int j = cost[v2];
    if (j == INT_MAX)
    {
        printf("-1");
        free(cost);
        return 0;
    }
    int k1 = cost[n];

    init(cost, n + 1);
    dijkstra(v2, vec);
    int k2 = cost[n];
    if (k1 == INT_MAX || k2 == INT_MAX)
    {
        printf("-1");
        free(cost);
        return 0;
    }

    int ans = min(i1 + j + k2, i2 + j + k1);

    printf("%d", ans);
    free(cost);
    return 0;
}
