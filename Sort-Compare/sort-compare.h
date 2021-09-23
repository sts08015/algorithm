#pragma once
#include <iostream>
#include <cstring>
#include <random>
#include <chrono>

#define REPEAT 1
using namespace std;

//1000,10000,50000,100000,500000,1000000

void Sort(int* arr,int len,void (*algo)(int*,int),const char* name)
{
  double avg;
  int* brr = (int*)malloc(sizeof(int)*len);

  for(int i=0;i<REPEAT;i++)
  {
    memcpy(brr,arr,sizeof(int)*len);

    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    algo(arr,len);
    chrono::time_point<std::chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end-start;

    avg += chrono::duration_cast<chrono::microseconds>(diff).count();
  }

  avg /= REPEAT;
  //cout << name << ": " << avg <<endl;
  free(brr);
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

void Quick_Sort(int* arr,int len)
{

}

void Heap_Sort(int* arr,int len)
{

}

void compare(int len)
{
  int *arr = (int*)malloc(sizeof(int)*len);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> dis(0, 999);

  for(int i=0;i<len;i++) arr[i] = dis(gen);

  puts("initial!!");
  for(int i=0;i<len;i++) printf("%d\n",arr[i]);

  cout << "[SORTING COMPARE]" << endl;
  Sort(arr,len,Selection_Sort,"Selection_Sort");
  Sort(arr,len,Bubble_Sort,"Bubble_Sort");
  Sort(arr,len,Quick_Sort,"Quick_Sort");
  Sort(arr,len,Heap_Sort,"Heap_Sort");

  free(arr);
}
