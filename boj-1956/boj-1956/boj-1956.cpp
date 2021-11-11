#include <stdio.h>
#include <vector>
using namespace std;

int brr[401][401];
const int INF = 10001;

int main(void)
{
    int v, e;
    scanf("%d %d", &v, &e);
    
    for (int i = 1; i <= v; i++)
        for (int j = 1; j <= v; j++)
            brr[i][j] = INF;

    for (int i = 0; i < e; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        brr[a][b] = c;
    }

    for (int i = 1; i <= v; i++)
    {
        for (int j = 1; j <= v; j++)
        {
            if (i == j) continue;
            for (int k = 1; k <= v; k++)
            {
                if (i == k) continue;
                int tmp = brr[j][i] + brr[i][k];
                if (brr[j][k] > tmp) brr[j][k] = tmp;
            }
        }
    }

    int ans = INF;
    for (int i = 1; i <= v; i++)
    {
        if (ans > brr[i][i]) ans = brr[i][i];
    }
    if (ans == INF) printf("-1");
    else printf("%d", ans);
    return 0;
}
