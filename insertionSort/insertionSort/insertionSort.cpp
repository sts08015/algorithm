#include <iostream>
#define SIZE 10

using std::cout;
using std::endl;

int test[SIZE] = {10,9,3,2,4,5,1,7,8,6};

void InsertionSort()
{
    int i, j, cur;

    for (i = 1; i < SIZE; i++)
    {
        cur = test[i];
        for (j = i - 1; j >= 0 && test[j] > cur; j--)
            test[j + 1] = test[j];
        
        test[j + 1] = cur;
    }
}

void PrintArray(int option)
{
    if (option == 0) cout << "BEFORE : " << endl;
    else cout << "AFTER : "<< endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << test[i] << ' ';
    }
    cout << endl << endl;
}

int main(void)
{
    PrintArray(0);
    InsertionSort();
    PrintArray(1);
    return 0;
}
