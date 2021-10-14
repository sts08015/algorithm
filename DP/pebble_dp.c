#include <stdio.h>
#include <limits.h>
#include <string.h>

int arr[3][8] = {{6,7,12,-5,5,3,11,4},{-8,10,14,9,7,13,8,5},{11,12,7,4,8,-2,9,4}};
int peb[4][8];

int check(int a,int b)
{
  if(a == 1)
  {
    if(b == 2 || b == 3) return 1;
    else return 0;
  }
  else if(a == 2)
  {
    if(b!=2) return 1;
    else return 0;
  }
  else if(a == 3)
  {
    if(b == 1 || b == 2) return 1;
    else return 0;
  }
  else
  {
    if(b == 2) return 1;
    else return 0;
  }
}

int pebbleSum(int n)
{
  for(int i=1;i<=4;i++)
  {
    if(i!=4) peb[i-1][0] = arr[i-1][0];
    else peb[3][0] = arr[0][0] + arr[2][0];
  }

  for(int i=2;i<=n;i++)
  {
    for(int p=1;p<=4;p++) //cur pattern
    {
      for(int q=1;q<=4;q++) //before pattern
      {
        if(check(p,q))
        {
          int tmp = peb[p-1][i-1];
          int val;
          if(p!=4) val = arr[p-1][i-1] + peb[q-1][i-2];
          else val = arr[0][i-1] + arr[2][i-1] + peb[q-1][i-2];
          if(val > tmp) peb[p-1][i-1] = val;
        }
      }
    }
  }

  int ans = INT_MIN;
  for(int i=1;i<=4;i++)
  {
    int tmp = peb[i-1][n-1];
    if(tmp > ans) ans = tmp;
  }
  return ans;
}

int main(void)
{
  for(int i=0;i<4;i++) memset(peb[i],INT_MIN,sizeof(int)*8);
  int ans = pebbleSum(8);
  printf("%d\n",ans);
  return 0;
}
