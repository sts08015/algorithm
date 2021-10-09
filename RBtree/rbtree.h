#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum _trav
{
  PREORDER,INORDER,POSTORDER
}Traversal;

typedef enum _color
{
  RED,BLACK
}COLOR;

typedef struct _node
{
  struct _node* parent;
  struct _node* left;
  struct _node* right;
  int val;
  COLOR color;
}Node;

typedef struct _rbtree
{
  Node* root;
  Node* NIL;
}RBTree;

Node* makeNode(int num)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->val = num;
  node->color = RED;  //default : RED
  return node;
}

RBTree* initTree()
{
  RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
  Node* nil = makeNode(INT_MIN);
  nil->color = BLACK;
  //nil->left = nil;
  //nil->right = nil;

  tree->root = nil;
  tree->NIL = nil;
  return tree;
}

bool chkDRED(Node* p, Node*c)
{
  if(p==NULL) return false;
  else if(p->color == RED && p->color == c->color) return true;
  else return false;
}


void leftRotation(Node* p, Node* c,RBTree* tree)
{
  Node* gp = p->parent; // TODO : think when gp is NULL!
  if(gp!=NULL)  //p is not root
  {
    bool chk = (gp->right == p);
    if(chk) gp->right = c;
    else gp->left = c;
  }
  else tree->root = c;
  c->parent = gp;

  p->right = c->left;
  if(c->left!=tree->NIL) c->left->parent = p;

  c->left = p;
  p->parent = c;
}

void rightRotation(Node* p,Node* c, RBTree* tree)
{
  Node* gp = p->parent;
  if(gp!=NULL)
  {
    bool chk = (gp->right == p);
    if(chk) gp->right  = c;
    else gp->left = c;
  }
  else tree->root = c;
  c->parent = gp;

  p->left = c->right;
  if(c->right!=tree->NIL) c->right->parent = p;

  c->right = p;
  p->parent = c;
}

void checkRules(RBTree* tree,Node* p,Node* c)
{
  if(chkDRED(p,c))  //if p is root, never satisfies
  {
    Node* gp = p->parent; //always exists(not NULL)
    Node* u = NULL;
    Node* tmp = NULL;

    if(gp->right == p) u = gp->left;
    else u = gp->right;

    if(u->color == BLACK)
    {
      if(gp->right == p)
      {
        if(p->left == c) //case 2-1
        {
          rightRotation(p,c,tree);
          tmp = p;
          p = c;
          c = tmp;
        }
        leftRotation(gp,p,tree);  //case 2-2
      }
      else
      {
        if(p->right == c)  //case 2-1
        {
          leftRotation(p,c,tree);
          tmp = p;
          p = c;
          c = tmp;
        }
        rightRotation(gp,p,tree); //case 2-2
      }

      tmp = gp;
      gp = p;
      p = tmp;
      gp->color = BLACK;
      p->color = RED;
    }
    else  //case 1
    {
        gp->color = RED;
        p->color = BLACK;
        u->color = BLACK;

        if(tree->root->color == RED) tree->root->color = BLACK;
        if(gp->parent!=NULL) checkRules(tree,gp->parent,gp);
    }
  }
}

void insertion(RBTree* tree, int num)
{
  Node* newNode = makeNode(num);
  Node* p = NULL;
  Node* c = tree->root;

  bool flag = true; //to check left or right
  while(c!=tree->NIL)
  {
    p = c;
    if(num > c->val)
    {
      c = c->right;
      flag = true;
    }
    else
    {
      c = c->left;
      flag = false;
    }
  }

  newNode->parent = p;
  newNode->left = tree->NIL;
  newNode->right = tree->NIL;

  if(tree->root == tree->NIL)
  {
    newNode->color = BLACK; //root is BLACK
    tree->root = newNode;
  }
  else
  {
    if(flag) p->right = newNode;
    else p->left = newNode;
  }

  checkRules(tree,p,newNode);
}


void deletion()
{
  //TODO
}

void preorder(Node* root,Node* nil)
{
  if(root!=nil)
  {
    if(root->color == RED) printf("%d-R ",root->val);
    else printf("%d-B ",root->val);
    preorder(root->left,nil);
    preorder(root->right,nil);
  }
}

void inorder(Node* root,Node* nil)
{
  if(root!=nil)
  {
    inorder(root->left,nil);
    if(root->color == RED) printf("%d-R ",root->val);
    else printf("%d-B ",root->val);
    inorder(root->right,nil);
  }
}

void postorder(Node* root,Node* nil)
{
  if(root!=nil)
  {
    postorder(root->left,nil);
    postorder(root->right,nil);
    if(root->color == RED) printf("%d-R ",root->val);
    else printf("%d-B ",root->val);
  }
}

void traversal(RBTree* tree,Traversal mode)
{
  if(mode == PREORDER) preorder(tree->root,tree->NIL);
  else if(mode == INORDER) inorder(tree->root,tree->NIL);
  else if(mode == POSTORDER) postorder(tree->root,tree->NIL);
}
