#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
	MAX, MIN
}MODE;

char chk[10];

bool solve(char* arr,char* brr,int len,int depth,MODE mode)
{
	if (len+1 == depth)
	{
		return true;
	}

	bool find = false;
	for (int i = 9; i >= 0; i--)
	{
		int j;
		if (mode == MIN) j = 9 - i;
		else j = i;

		if (!chk[j])
		{
			if (depth == 0)
			{
				if (j == 0 && arr[depth] == '>') continue;
				else if (j == 9 && arr[depth] == '<') continue;
			}
			else
			{
				if (depth == len)
				{
					if (j == 0 && arr[depth] == '<') continue;
					else if (j == 9 && arr[depth] == '>') continue;
				}
				if (arr[depth-1] == '<')
				{
					if (brr[depth - 1] > j) continue;
				}
				else
				{
					if (brr[depth - 1] < j) continue;
				}
			}
			brr[depth] = j;
			chk[j]++;
			find = true;
			bool val = solve(arr, brr, len, depth + 1,mode);
			if (!val)
			{
				chk[brr[depth]]--;
				brr[depth] = 0;
				find = false;
			}
			else break;
		}
	}

	return find;
}
int main(void)
{
	int k;
	scanf("%d", &k);
	char* arr = (char*)malloc(sizeof(char) * k);
	char* brr = (char*)calloc(k + 1,sizeof(char));
	char* crr = (char*)calloc(k + 1, sizeof(char));

	for (int i = 0; i < k; i++)
	{
		getchar();
		scanf("%c", arr + i);
	}

	solve(arr, brr, k, 0,MAX);
	for (int i = 0; i < k + 1; i++) printf("%d", brr[i]);
	puts("");
	memset(chk, 0, 10);
	solve(arr, crr, k, 0,MIN);
	for (int i = 0; i < k + 1; i++) printf("%d", crr[i]);

	free(arr);
	free(brr);
	free(crr);
	return 0;
}
