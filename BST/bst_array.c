#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
int maxlen;

void inorder(int* root,int idx)
{
  if(root[idx]!=-1)
  {
    int tmp = idx<<1;
    inorder(root,tmp);
    printf("%d ",root[idx]);
    inorder(root,tmp+1);
  }
}

int find(int* root,int idx,int num)
{
  if(root[idx] == -1) return -1;
  int tmp = idx<<1;
  if(root[idx] == num) return num;
  else if(root[idx] < num) return find(root,tmp+1,num);
  else return find(root,tmp,num);
}

int findSuccessor(int* root,int idx)
{
  if(root[idx] == -1) return -1;
  int tmp = idx<<1;
  while(root[tmp]!=-1) tmp<<=1;
  return tmp>>1;  //return idx of Successor
}

void insert(int* root,int idx,int num)
{
  if(root!=NULL)
  {
    int tmp = idx << 1;
    if(root[idx] == -1) root[idx] = num;
    else if(root[idx] < num) insert(root,tmp+1,num);
    else insert(root,tmp,num);
  }
}

void move(int* root,int* arr,int idx,int diff,int depth)
{
  if(depth>0 && root[idx]!=-1)
  {
    arr[idx-diff] = root[idx];
    root[idx] = -1;
    diff<<=1;
    int tmp = idx<<1;
    move(root,arr,tmp,diff,depth-1);
    move(root,arr,tmp+1,diff,depth-1);
  }
}
int getDepth(int* root,int idx,int depth)
{
  if(root[idx]== -1) return depth;
  int depth1 = getDepth(root,idx<<1,depth+1);
  int depth2 = getDepth(root,(idx<<1)+1,depth+1);
  return ((depth1>depth2)?depth1:depth2);
}

void delete(int* root,int idx,int num)
{
  if(root != NULL)
  {
    int tmp = idx<<1;
    if(root[idx] < num) delete(root,tmp+1,num);
    else if(root[idx] > num) delete(root,tmp,num);
    else
    {
      if(root[tmp]!=-1 && root[tmp+1]!=-1)  //two children
      {
        int sucIdx = findSuccessor(root,tmp+1);
        int diff = sucIdx+1;
        int tmp = (sucIdx<<1)+1;
        int depth = getDepth(root,tmp,0);
        root[idx] = root[sucIdx];
        if(depth>0)
        {
          int* arr = (int*)malloc(sizeof(int)*(maxlen+1));
          memset(arr,-1,maxlen+1);
          move(root,arr,tmp,diff,depth);
          for(int i=0;i<=maxlen;i++) if(arr[i]!=-1) root[i] = arr[i];
          free(arr);
        }
        else root[sucIdx] = -1;
      }
      else if(root[tmp]!=-1 || root[tmp+1]!=-1) //one child
      {
        int depth;
        if(root[tmp] == -1)
        {
          tmp++;
          depth = getDepth(root,tmp,0);
        }
        else depth = getDepth(root,tmp,0);
        int diff = tmp-idx;
        int* arr = (int*)malloc(sizeof(int)*(maxlen+1));
        memset(arr,-1,maxlen+1);
        move(root,arr,tmp,diff,depth);
        for(int i=0;i<=maxlen;i++) if(arr[i]!=-1) root[i] = arr[i];
        free(arr);
      }
      else root[idx] = -1;  //no child
    }
  }
}

int main(void)
{
  int arr[] = {10,4,6,1,7,9,2,5,0,3,8};
  struct timeval start,end;
  int diff;
  int len = sizeof(arr)/sizeof(int);
  maxlen = len;
  for(int i=0;i<9;i++) maxlen = (maxlen<<1) + 1;
  int* Tree = (int*)malloc(sizeof(int)*(maxlen+1));  //index starts with 1
  if(Tree == NULL)
  {
    perror("Tree generation err");
    exit(-1);
  }
  memset(Tree,-1,maxlen+1);  // -1 means NULL;
  for(int i=0;i<len;i++) insert(Tree,1,arr[i]);
  inorder(Tree,1);
  puts("");
  gettimeofday(&start,NULL);
  int res = find(Tree,1,0);
  if(res == -1) puts("no node!");
  else printf("found! : %d\n",res);
  gettimeofday(&end,NULL);

  for(int i=0;i<len;i++) delete(Tree,1,arr[i]);
  diff = (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);
  printf("total microseconds : %d\n",diff);
  free(Tree);
  return 0;
}
