#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

char arr[6][6] = {
    {0,1,1,0,1,1},
    {1,0,1,0,0,0},
    {0,1,0,1,0,0},
    {0,0,0,0,1,0},
    {0,0,0,1,0,0},
    {1,0,0,0,1,0} 
};
vector<int> vec[6];

typedef struct _node
{
    int val;
    int size;
    struct _node** con;
}Node;

Node G[6];

char visit[6];


void dfs_list(int s)
{
    if (s == 5)
    {
        printf("5\n");
        return;
    }
    else printf("%d ", s);

    for (size_t i = 0; i < vec[s].size(); i++)
    {
        int x = vec[s][i];
        if (visit[x] == 0)
        {
            visit[x] = 1;
            dfs_list(x);
            visit[x] = 0;
        }
    }
}

void bfs_list(int s)
{
    queue<int> que;
    que.push(s);

    while (!que.empty())
    {
        int tmp = que.front();
        que.pop();
        if (tmp == 5)
        {
            printf("5\n");
            continue;
        }
        else printf("%d ", tmp);

        for (size_t i = 0; i < vec[tmp].size(); i++)
        {
            int x = vec[tmp][i];
            if (visit[x] == 0)
            {
                visit[x] = 1;
                que.push(x);
            }
        }
    }
}

void by_list()
{
    vec[0].push_back(1);
    vec[0].push_back(2);
    vec[0].push_back(4);
    vec[0].push_back(5);

    vec[1].push_back(0);
    vec[1].push_back(2);

    vec[2].push_back(1);
    vec[2].push_back(3);

    vec[3].push_back(4);

    vec[4].push_back(3);

    vec[5].push_back(0);
    vec[5].push_back(4);

    puts("\n=== dfs_list ===");
    memset(visit, 0, 6);
    visit[0] = 1;
    dfs_list(0);
    puts("=== bfs_list ===");
    memset(visit, 0, 6);
    visit[0] = 1;
    bfs_list(0);
}

void dfs_matrix(int s)
{
    if (s == 5)
    {
        printf("5\n");
        return;
    }
    else printf("%d ", s);

    for (int i = 0; i < 6; i++)
    {
        if (arr[s][i] != 0 && visit[i]==0)
        {
            visit[i] = 1;
            dfs_matrix(i);
            visit[i] = 0;
        }
    }
}

void bfs_matrix(int s)
{
    queue<int> que;
    que.push(s);

    while (!que.empty())
    {
        int tmp = que.front();
        que.pop();
        if (tmp == 5)
        {
            printf("5\n");
            continue;
        }
        else printf("%d ", tmp);

        for (int i = 0; i < 6; i++)
        {
            if (arr[tmp][i] != 0 && visit[i] == 0)
            {
                visit[i] = 1;
                que.push(i);
            }
        }
    }
}

void by_matrix()
{
    puts("\n=== dfs_matrix ===");
    visit[0] = 1;
    dfs_matrix(0);
    memset(visit, 0, 6);
    visit[0] = 1;
    puts("=== bfs_matrix ===");
    bfs_matrix(0);
}

void dfs_node(int s)
{
    if (s == 5)
    {
        printf("5\n");
        return;
    }
    else printf("%d ", s);

    for (int i = 0; i < G[s].size; i++)
    {
        int x = G[s].con[i]->val;
        if (visit[x] == 0)
        {
            visit[i] = 1;
            dfs_matrix(x);
            visit[i] = 0;
        }
    }
}

void bfs_node(int s)
{
    queue<Node*> que;
    que.push(&G[s]);

    while (!que.empty())
    {
        Node* tmp = que.front();
        que.pop();
        if (tmp->val == 5)
        {
            printf("5\n");
            continue;
        }
        else printf("%d ", tmp->val);

        for (int i = 0; i < tmp->size; i++)
        {
            Node* x = tmp->con[i];
            if (visit[x->val] == 0)
            {
                visit[x->val] = 1;
                que.push(x);
            }
        }
    }
}

void by_node()
{
    G[0].size = 4;
    G[1].size = 2;
    G[2].size = 2;
    G[3].size = 1;
    G[4].size = 1;
    G[5].size = 2;
    for (int i = 0; i < 6; i++)
    {
        G[i].val = i;
        G[i].con = (Node**)malloc(sizeof(Node*) * G[i].size);
    }
    
    G[0].con[0] = &G[1];
    G[0].con[1] = &G[2];
    G[0].con[2] = &G[4];
    G[0].con[3] = &G[5];

    G[1].con[0] = &G[0];
    G[1].con[1] = &G[2];

    G[2].con[0] = &G[1];
    G[2].con[1] = &G[3];

    G[3].con[0] = &G[4];

    G[4].con[0] = &G[3];

    G[5].con[0] = &G[0];
    G[5].con[1] = &G[4];
    
    
    puts("\n=== dfs_node ===");
    memset(visit, 0, 6);
    visit[0] = 1;
    dfs_node(0);
    puts("=== bfs_node ===");
    memset(visit, 0, 6);
    visit[0] = 1;
    bfs_node(0);

    for (int i = 0; i < 6; i++)
    {
        free(G[i].con);
    }
}


int main(void)
{
    by_matrix();
    by_list();
    by_node();
    return 0;
}

