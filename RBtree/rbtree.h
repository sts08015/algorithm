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

Node* makeNode(Node* p,int num)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->parent = p;
  node->left = NULL;
  node->right = NULL;
  node->val = num;
  node->color = RED;
  return node;
}

Node* insert(Node* root,int num)
{
  return NULL;
}
