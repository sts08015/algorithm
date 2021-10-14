#include <stdio.h>
#include <limits.h>
int arr[3][8] = {{6,7,12,-5,5,3,11,4},{-8,10,14,9,7,13,8,5},{11,12,7,4,8,-2,9,4}};


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

int pebble(int n,int p)
{
  if(n == 1)
  {
    if(p!=4) return arr[p-1][0];
    else return arr[0][0] + arr[2][0];
  }
  else
  {
    int ans = INT_MIN;
    for(int i=1;i<=4;i++)
    {
      if(check(p,i))
      {
        int tmp = pebble(n-1,i);
        if(tmp>ans) ans = tmp;
      }
    }
    if(p!=4) return ans + arr[p-1][n-1];
    else return ans + arr[0][n-1] + arr[2][n-1];
  }
}

int pebbleSum(int n)
{
  int ans = pebble(n,1);
  for(int i=2;i<=4;i++)
  {
    int tmp = pebble(n,i);
    if(ans<tmp) ans = tmp;
  }
  return ans;
}

int main(void)
{
  int ans = pebbleSum(8);
  printf("%d\n",ans);
  return 0;
}
