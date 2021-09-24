#pragma once
#include <iostream>
#include <cstring>
#include <random>
#include <chrono>

#define REPEAT 5
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis(-99999, 99999);

//1000,10000,50000,100000,500000,1000000

void Sort(int* arr,int len,void (*algo)(int*,int),const char* name)
{
  double avg = 0;

  for(int i=0;i<REPEAT;i++)
  {
    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    algo(arr,len);
    chrono::time_point<std::chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end-start;

    avg += chrono::duration_cast<chrono::microseconds>(diff).count();

    for(int i=0;i<len;i++) arr[i] = dis(gen);
  }

  avg /= REPEAT;
  cout << name << ": " << avg <<endl;
}

void swap(int& a,int& b)
{
  int tmp = a;
  a = b;
  b = tmp;
}

void Selection_Sort(int* arr,int len)
{
  int i,j;
  for(i=len-1;i>0;i--)
  {
    int max_idx = i;
    for(j=i-1;j>=0;j--)
      if(arr[max_idx] < arr[j])
        max_idx = j;

    if(i!=max_idx) swap(arr[i],arr[max_idx]);
  }
}

void Bubble_Sort(int* arr,int len)
{
  int i,j;
  for(i=0;i<len-1;i++)
    for(j=0;j<len-i-1;j++)
      if(arr[j] > arr[j+1]) swap(arr[j],arr[j+1]);
}

int partition(int* arr,int left, int right)
{
  int pivot = right;
  int i = left;
  int j = pivot;

  while(i < j)
  {
    while(arr[i] < arr[pivot]) i++;
    while(arr[j] >= arr[pivot] && i<j) j--;
    swap(arr[i],arr[j]);
  }
  swap(arr[i],arr[pivot]);
  return i;
}

void qsort(int* arr,int left, int right)
{
  if(left < right)
  {
    int q = partition(arr,left,right);
    qsort(arr,left,q-1);
    qsort(arr,q+1,right);
  }
}

void Quick_Sort(int* arr,int len)
{
  qsort(arr,0,len-1);
}

void Build_MaxHeap(int* arr,int* brr,int len)
{
  int heap_size = 0;

  for(int i=0;i<len;i++)
  {
    heap_size++;
    brr[heap_size] = arr[i];
    int idx = heap_size;
    int parent = idx/2;
    while(parent>=1)
    {
      if(brr[idx] > brr[parent])
      {
        swap(brr[idx],brr[parent]);
        idx = parent;
        parent /= 2;
      }
      else break;
    }
  }

}

void delete_heap(int* arr,int len)
{
  int idx = 1;
  int left = -1;
  int right = -1;

  while(idx*2 <= len)
  {
    if(idx*2 + 1 > len) right = -1;
    else right = idx*2 + 1;

    left = idx*2;

    if(right == -1)
    {
      if(arr[idx] < arr[left])
      {
        swap(arr[idx],arr[left]);
        idx = left;
      }
      else break;
    }
    else
    {
      if(arr[idx] < arr[left] || arr[idx] < arr[right])
      {
        if(arr[left] < arr[right])
        {
          swap(arr[idx],arr[right]);
          idx = right;
        }
        else
        {
          swap(arr[idx],arr[left]);
          idx = left;
        }
      }
      else break;
    }
  }
}

void hsort(int* arr,int len)
{
  for(int i=1;i<=len;i++)
  {
    swap(arr[1],arr[len+1-i]);
    delete_heap(arr,len-i);
  }
}

void Heap_Sort(int* arr,int len)
{
  int* brr = (int *)malloc(sizeof(int)*(len+1));  // because initial index is 1 rather than 0
  Build_MaxHeap(arr,brr,len);
  hsort(brr,len); //sorting brr
  free(brr);
}

void compare(int len)
{
  int *arr = (int*)malloc(sizeof(int)*len);
  for(int i=0;i<len;i++) arr[i] = dis(gen);

  cout << "[SORTING COMPARE]" << endl;
  Sort(arr,len,Selection_Sort,"Selection_Sort");
  Sort(arr,len,Bubble_Sort,"Bubble_Sort");
  Sort(arr,len,Quick_Sort,"Quick_Sort");
  Sort(arr,len,Heap_Sort,"Heap_Sort");

  free(arr);
}
