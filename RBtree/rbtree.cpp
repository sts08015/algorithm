#include "rbtree.h"


int main(void)
{
  //const int arr[] = {1,2,4,5,9,0,6,3,7,8};
  const int arr[] = {8,18,5,15,17,25,40,80};

  int len = sizeof(arr)/sizeof(int);

  RBTree* Tree = initTree();

  for(int i=0;i<len;i++) insertion(Tree,arr[i]);



  // one for color means black
  puts("preorder");
  traversal(Tree,PREORDER);
  puts("");

  puts("inorder");
  traversal(Tree,INORDER);
  puts("");

  puts("postorder");
  traversal(Tree,POSTORDER);
  puts("");


  //for(int i=0;i<len;i++) deletion(Tree,arr[i]);

  return 0;
}
