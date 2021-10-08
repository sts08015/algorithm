#include "rbtree.h"


int main(void)
{
  const int arr[] = {1,2,4,5,9,0,6,3,7,8};
  int len = sizeof(arr)/sizeof(int);

  RBTree* Tree = initTree();

  for(int i=0;i<len;i++) insert(Tree,arr[i]);


  
  puts("preorder");
  traversal(Tree,PREORDER);
  puts("");

  puts("inorder");
  traversal(Tree,INORDER);
  puts("");

  puts("postorder");
  traversal(Tree,POSTORDER);
  puts("");

  return 0;
}
