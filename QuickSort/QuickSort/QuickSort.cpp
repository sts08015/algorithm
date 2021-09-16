#include <iostream>
#define SIZE 10

using std::cout;
using std::endl;

int test[SIZE] = { 10,9,3,2,4,5,1,7,8,6 };

void swap(int a, int b)
{
    int tmp = test[a];
    test[a] = test[b];
    test[b] = tmp;
}

int partition(int left, int right)
{
    int mid = (left + right) / 2;
    //swap(mid, right);

    int pivot = test[right];
    int i = left, j = right;

    while (i < j)
    {
        while (pivot > test[i]) i++;
        while (pivot <= test[j] && i<j) j--;
        swap(i, j);
    }
    swap(i,right);
    return i;
}

void QuickSort(int left,int right)
{
    if (left < right)
    {
        int q = partition(left, right);
        QuickSort(left, q - 1);
        QuickSort(q + 1, right);
    }
}

void PrintArray(int option)
{
    if (option == 0) cout << "BEFORE : " << endl;
    else cout << "AFTER : " << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << test[i] << ' ';
    }
    cout << endl << endl;
}

int main(void)
{
    PrintArray(0);
    QuickSort(0,SIZE-1);
    PrintArray(1);
    return 0;
}
