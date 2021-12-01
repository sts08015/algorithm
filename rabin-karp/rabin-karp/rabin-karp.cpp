#include <stdio.h>
#include <string.h>

#define NUM 256

void search(char* pat, char* txt, int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0, t = 0, h = 1;

    for (i=0;i<M-1;i++) h=(h*NUM)%q;

    for (i = 0; i < M; i++)
    {
        p=(NUM*p+pat[i])% q;
        t=(NUM*t+txt[i])% q;
    }

    for (i = 0; i <=N-M; i++)
    {
        if (p == t) 
        {
            for (j = 0; j < M; j++) if (txt[i + j] != pat[j]) break;
            if (j == M) printf("Found!! index : %d \n", i);
        }
        if (i < N - M) 
        {
            t = (NUM*(t-txt[i]*h)+txt[i+M])%q;
            if (t < 0) t=(t + q);
        }
    }
}

int main()
{
    char target[] = "HELLO WORLD hahahahWORLD";
    char pattern[] = "WORLD";

    int q = 101;
    search(pattern, target, q);
    return 0;
}