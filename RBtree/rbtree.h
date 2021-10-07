#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef enum color
{
  RED,BLACK
}COLOR;

typedef struct _node
{
  struct _node *parent;
  struct _node* left;
  struct _node* right;
  int val;
  COLOR color;
}Node;

Node* makeNode(int num)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  node->val = num;
  node->color = RED;
  return node;
}

bool chkDRed(Node* p,Node *c)
{
  if(p->color == RED && p->color == c->color) return true;
  else return false;
}

int* sortNode(Node* a,Node* b,Node *c)
{
  static int arr[3] = {0};
  arr[0] = a->val;
  arr[1] = b->val;
  arr[2] = c->val;
  //bubble sort
  for(int i=0;i<2;i++)
    for(int j=0;j<2-i;j++)
      if(arr[j] < arr[j+1])
      {
        int tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
  return arr;
}

Node* insert(Node* root,int num,int depth)
{
  if(root == NULL)
  {
    Node* newNode = makeNode(num);
    if(depth == 0) newNode->color = BLACK;  //real root node
    return newNode;
  }
  else if(root->val < num)
  {
    root->right = insert(root->right,num);
    root->right->parent = root;
    if(chkDRed(root,root->right)) //double red
    {
      if(root->parent->left == root)
      {
        Node* c = root->right;
        Node* gp = root->parent;
        Node* u = root->parent->right;
        if(u!=NULL) //if uncle exists
        {
          if(u->color == RED) //recolor
          {
            c->color = BLACK;
            u->color = BLACK;
            if(gp->parent == NULL) gp->color = BLACK;
            else
            {
              gp->color = RED;
              Node* cur = gp;

              while(cur->parent!=NULL)
              {
                if(chkDRed(cur->parent,cur))
                {
                  //real root is always black so there always exsit cur->parent->parent
                  Node* t_p = cur->parent;
                  Node* t_gp = t_p->parent;
                  Node* t_u;
                  if(t_gp->right == t_p) t_u = t_gp->left;
                  else t_u = t_gp->right;

                  cur->color = BLACK;
                  t_u->color = BLACK;
                  t_gp->color = RED;

                  cur = cur->parent->parent;
                }
                else break;
              }

            }
          }
          else  //reconstruct
          {
            const int* arr = sortNode(c,root,gp);
            root->val = arr[0];
            gp->val = arr[1];
            int tmp = u->val;
            u->val = arr[2];

            Node* z = makeNode(tmp);
            z->parent = u;
            if(u->right!=NULL)
            {
              z->right = u->right;
              u->right->parent = z;
            }
            u->right = z;

            free(root->right);
            root->right = NULL;
          }
        }
      }
      else
      {
        //TODO
      }
    }
  }
  else
  {
    root->left = insert(root->left,num);
    root->left->parent = root;
    if(chkDRed(root,root->left))
    {
      //TODO
    }

  }

  return root;
}
