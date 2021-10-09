#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

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

void display(RBTree* tree);

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

Node* getPredecessor(RBTree* tree,Node* c)
{
  Node* p = c->parent;
  while(c!=tree->NIL)
  {
    p = c;
    c = c->right;
  }
  return p;
}

Node* find(RBTree* tree,int num)
{
  Node* c = tree->root;
  while(c!=tree->NIL)
  {
    if(num>c->val) c = c->right;
    else if(num<c->val) c = c->left;
    else break;
  }
  if(c == tree->NIL) return NULL;
  else return c;
}

void handleDoubleD(RBTree* tree,Node* p,Node* t,bool chk)
{
  Node* s = NULL;
  Node* tmp = NULL;

  if(chk) s = p->left;
  else s = p->right;

  if(s->color == RED)
  {
    s->color = BLACK;
    p->color = RED;

    if(chk) rightRotation(p, s, tree);
    else leftRotation(p, s, tree);

    handleDoubleD(tree,p,t,chk);
  }
  else  //sibling is BLACK
  {
    if(s->left->color == BLACK && s->right->color == BLACK)
    {
      s->color = RED;
      if(p->color == RED) p->color = BLACK;
      else
      {
        if(p->parent != NULL)
        {
          if(p->parent->right == p) handleDoubleD(tree,p->parent,p,true);
          else handleDoubleD(tree,p->parent,p,false);
        }
      }
    }
    else if(s->left->color == RED && s->right->color == BLACK)
    {
      s->color = RED;
      s->left->color = BLACK;
      Node* l = s->left;
      if(chk) rightRotation(p,s,tree);
      else
      {
        rightRotation(s,l,tree);
        leftRotation(p,l,tree);
      }
    }
    else if(s->right->color == RED)
    {
      s->color = p->color;
      p->color = BLACK;
      s->right->color = BLACK;
      if(chk) rightRotation(p,s,tree);
      else leftRotation(p,s,tree);
    }
  }
}

void deletion(RBTree* tree,int num)
{
  Node* target = find(tree,num);
  if(target == NULL)
  {
    puts("No Such Node");
    return;
  }
  //node that is going to get deleted is predecessor!
  Node* p = target->parent;

  bool chk = true;  //right child --> true
  if(p!=NULL)
    if(p->left == target)
      chk = false;

  if(target->left == tree->NIL && target->right == tree->NIL)
  {
    if(target->color == RED)  //never root --> parent exists
    {
      if(chk) p->right = tree->NIL;
      else p->left = tree->NIL;
    }
    else
    {
      if(target == tree->root) tree->root = NULL;
      else
      {
        if(chk) p->right = tree->NIL;
        else p->left = tree->NIL;

        handleDoubleD(tree,p,tree->NIL,chk); //target is not root
      }
    }
    free(target);
  }
  else if(target->left == tree->NIL)
  {
    if(target->right->color == RED)
    {
      target->right->color = BLACK;
      if(target!=tree->root)
      {
        if(chk) p->right = target->right;
        else p->left = target->right;
      }
      else tree->root = target->right;
      target->right->parent = p;
    }
    else
    {
      if(target == tree->root)
      {
        tree->root = target->right;
        tree->root->color = BLACK;
      }
      else
      {
        if(chk) p->right = target->right;
        else p->left = target->right;
        handleDoubleD(tree,p,target->right,chk);
      }
    }
    free(target);
  }
  else if(target->right == tree->NIL)
  {
    if(target->left->color == RED)
    {
      target->left->color = BLACK;
      if(target!=tree->root)
      {
        if(chk) p->right = target->left;
        else p->left = target->left;
      }
      else tree->root = target->left;
      target->left->parent = p;
    }
    else
    {
      if(target == tree->root)
      {
        tree->root = target->left;
        tree->root->color = BLACK;
      }
      else
      {
        if(chk) p->right = target->left;
        else p->left = target->left;
        handleDoubleD(tree,p,target->left,chk);
      }
    }
    free(target);
  }
  else
  {
    Node* pred = getPredecessor(tree,target->left);
    target->val = pred->val;
    bool tmp = true;
    if(pred->parent != target)
    {
      pred->parent->right = tree->NIL;
    }
    else
    {
      pred->parent->left = pred->left;
      pred->left->parent = pred->parent;
      tmp = false;
    }

    if(pred->color == BLACK && pred->left->color == BLACK)
    {
      handleDoubleD(tree,pred->parent,tree->NIL,tmp);
      pred->left->color = BLACK;
    }
    
    //if red do nothing
    free(pred);
  }
}

void preorder(Node* root,Node* nil)
{
  if(root!=nil && root!=NULL)
  {
    if(root->color == RED) printf("%d-R ",root->val);
    else printf("%d-B ",root->val);
    preorder(root->left,nil);
    preorder(root->right,nil);
  }
}

void inorder(Node* root,Node* nil)
{
  if(root!=nil && root!=NULL)
  {
    inorder(root->left,nil);
    if(root->color == RED) printf("%d-R ",root->val);
    else printf("%d-B ",root->val);
    inorder(root->right,nil);
  }
}

void postorder(Node* root,Node* nil)
{
  if(root!=nil && root!=NULL)
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
  else puts("Wrong Mode!");
}

void display(RBTree* tree)
{
  puts("preorder");
  traversal(tree,PREORDER);
  puts("");

  puts("inorder");
  traversal(tree,INORDER);
  puts("");

  puts("postorder");
  traversal(tree,POSTORDER);
  puts("");
}
