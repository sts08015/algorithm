#include "rbtree.h"


int main(void)
{
  const int arr[] = {1,2,4,5,9,0,6,3,7,8};
  Node* Tree = NULL;
  int len = sizeof(arr)/sizeof(int);

  for(int i=0;i<len;i++) Tree = insert(Tree,arr[i]);

  return 0;
}
