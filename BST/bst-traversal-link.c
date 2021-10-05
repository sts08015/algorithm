#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
  struct _node* left;
  struct _node* right;
  int val;
}Node;

void inorder(Node* root)
{
  if(root!=NULL)
  {
    inorder(root->left);
    printf("%d ",root->val);
    inorder(root->right);
  }
}

void preorder(Node* root)
{
  if(root!=NULL)
  {
    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
  }
}

void postorder(Node* root)
{
  if(root!=NULL)
  {
    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->val);
  }
}

Node* makeNode(int val)
{
  Node* node = (Node *)malloc(sizeof(Node));
  node->left = NULL;
  node->right = NULL;
  node->val = val;
  return node;
}

Node* find(Node* root,int num)
{
  if(root==NULL) return NULL;
  if(root->val == num) return root;
  if(root->val < num) return find(root->right,num);
  else return find(root->left,num);
}

Node* findSuccessor(Node* root)
{
  if(root == NULL) return NULL;
  while(root->left!=NULL) root = root->left;
  return root;
}

Node* insert(Node* root,int num)
{
  if(root == NULL) return makeNode(num);
  else if(root->val < num) root->right = insert(root->right,num);
  else root->left = insert(root->left,num);
  return root;
}

Node* delete(Node* root,int num)
{
  if(root == NULL) return NULL;
  if(root->val < num) root->right = delete(root->right,num);
  else if(root->val > num) root->left = delete(root->left,num);
  else
  {
    if(root->right!=NULL && root->left!=NULL)
    {
      Node* tmp = findSuccessor(root->right);
      root->val = tmp->val;
      root->right = delete(root->right,tmp->val);
    }
    else if(root->right!=NULL || root->left!=NULL)
    {
      Node* tmp;
      if(root->right == NULL) tmp = root->left;
      else tmp = root->right;
      free(root);
      return tmp;
    }
    else
    {
      free(root);
      return NULL;
    }
  }
  return root;
}

int main(void)
{
  int arr[] = {10,4,6,1,7,9,2,5,0,3,8};

  Node* Tree = NULL;
  for(int i=0;i<sizeof(arr)/sizeof(int);i++) Tree = insert(Tree,arr[i]);
  printf("inorder : ");inorder(Tree);puts("");
  printf("preorder : ");preorder(Tree);puts("");
  printf("postorder : ");postorder(Tree);puts("");

  for(int i=0;i<sizeof(arr)/sizeof(int);i++) Tree = delete(Tree,arr[i]);

  return 0;
}
