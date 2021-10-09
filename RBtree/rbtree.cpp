#include "rbtree.h"


int main(void)
{
  //const int arr[] = {1,2,4,5,9,0,6,3,7,8};
  const int arr[] = {8,18,5,15,17,25,40,80};

  int len = sizeof(arr)/sizeof(int);

  RBTree* Tree = initTree();

  for(int i=0;i<len;i++) insertion(Tree,arr[i]);
  display(tree);
  //for(int i=0;i<len;i++) deletion(Tree,arr[i]);

  return 0;
}
