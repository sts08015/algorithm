#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHA_NUM 26

const char* test1 = "helloworldaabbcfcdde";
const char* test2 = "abcdefghifasdfaftkl";
const char* target = "daab";

char** table;
int len;


int nextState(int state,int c)
{
    if (state < len && c == target[state]) return state + 1;

    int cur = 0;
    for (int i = state; i > 0; i--)
    {
        if (target[i - 1] == c)
        {
            while (cur < i - 1)
            {
                if (target[cur] != target[state - i + 1 + cur]) break;
                cur++;
            }
            if (cur == i - 1) return i;
        }
    }

    return 0;
}

void buildAutomata()
{
    len = strlen(target);
    table = (char**)malloc(sizeof(char*)*(len+1));
    for (int i = 0; i < len+1; i++) table[i] = (char*)calloc(ALPHA_NUM,sizeof(char));

    for (int i = 0; i < len+1; i++)
    {
        for (int j = 0; j < ALPHA_NUM; j++)
        {
            int val = nextState(i,j+'a');
            table[i][j] = val;
        }
    }
    
}

void search()
{
    int len2 = strlen(test1);
    int state = 0;
    for (int i = 0; i < len2; i++)
    {
        state = table[state][test1[i]-'a'];
        if (state == len)
        {
            puts("found!");
            return;
        }
    }
    puts("not found!");
}

void clean()
{
    for (int i = 0; i < len+1; i++) free(table[i]);
    free(table);
}

int main(void)
{
    buildAutomata();
    search();
    clean();
    return 0;
}


