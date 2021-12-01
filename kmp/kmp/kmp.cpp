#include<stdio.h>
#include<string.h>
#include <stdlib.h>


void prefixSuffixArray(char* pat, int M, int* pps) 
{
    int len = 0;
    pps[0] = 0;
    int i = 1;
    while (i < M) 
    {
        if (pat[i] == pat[len]) 
        {
            len++;
            pps[i] = len;
            i++;
        }
        else {
            if (len != 0) len = pps[len - 1];
            else 
            {
                pps[i] = 0;
                i++;
            }
        }
    }
}
void KMP(char* text, char* pattern) 
{
    int M = strlen(pattern);
    int N = strlen(text);
    int* pps = (int*)malloc(sizeof(int) * M);

    prefixSuffixArray(pattern, M, pps);
    int i = 0;
    int j = 0;
    while (i < N) 
    {
        if (pattern[j] == text[i]) 
        {
            j++;
            i++;
        }
        if (j == M) {
            printf("Index : %d\n", i - j);
            j = pps[j - 1];
        }
        else if (i < N && pattern[j] != text[i]) 
        {
            if (j != 0) j = pps[j - 1];
            else i = i + 1;
        }
    }
    free(pps);
}
int main(void) 
{
    char text[] = "helloWorldfifismaaazzzz";
    char pattern[] = "fisma";
    KMP(text, pattern);
    return 0;
}