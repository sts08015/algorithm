#include "rbtree.h"


int main(void)
{
  const int arr[] = {1,2,4,5,9,0,6,3,7,8};
  const int brr[] = {8,18,5,15,17,25,40,80};
  const int crr[] = {11,2,14,1,7,5,8,15};

  int len = sizeof(brr)/sizeof(int);

  RBTree* Tree = initTree();

  for(int i=0;i<len;i++) insertion(Tree,brr[i]);

  display(Tree);

  for(int i=0;i<len;i++) deletion(Tree,brr[i]);

  puts("\n");
  display(Tree);

  return 0;
}
