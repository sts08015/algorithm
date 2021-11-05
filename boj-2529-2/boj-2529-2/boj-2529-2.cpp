#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int indegree1[10];
int indegree2[10];

int main(void)
{
    int k;
    scanf("%d", &k);
    char* sign = (char*)malloc(sizeof(char) * k);
    vector<int> arr[10];

    for (int i = 0; i < k; i++)
    {
        getchar();
        scanf("%c", sign + i);
        
        if (sign[i] == '<')
        {
            indegree1[i + 1]++;
            indegree2[i + 1]++;
            arr[i].push_back(i + 1);
        }
        else
        {
            indegree1[i]++;
            indegree2[i]++;
            arr[i + 1].push_back(i);
        }
    }

    priority_queue<int> max_heap;
    priority_queue<int,vector<int>,greater<int>> min_heap;

    for (int i = 0; i < k + 1; i++)
    {
        if (indegree1[i] == 0)
        {
            max_heap.push(i);
            min_heap.push(i);
        }
    }

    char* ans1 = (char*)malloc(sizeof(char) * 10);
    char* ans2 = (char*)malloc(sizeof(char) * 10);

    int cnt = 0;
    for (int i = 0; i < k + 1; i++)
    {
        int tmp = max_heap.top();
        max_heap.pop();
        ans1[tmp] = cnt++;
        for (int j = 0; j < arr[tmp].size(); j++)
        {
            int x = arr[tmp][j];
            if (--indegree1[x] == 0) max_heap.push(x);
        }
    }
    cnt = 0;
    for (int i = 0; i < k + 1; i++)
    {
        int tmp = min_heap.top();
        min_heap.pop();
        ans2[tmp] = cnt++;
        for (int j = 0; j < arr[tmp].size(); j++)
        {
            int x = arr[tmp][j];
            if (--indegree2[x] == 0) min_heap.push(x);
        }
    }
    for (int i = 0; i < k + 1; i++) printf("%d", ans1[i] + 9 - k);
    puts("");
    for (int i = 0; i < k + 1; i++) printf("%d", ans2[i]);
    
    free(ans1);
    free(ans2);
    free(sign);
    return 0;
}

