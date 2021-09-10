#include <iostream>
#include <iomanip>
#include <ctime>
#define N 13377

int arr1[N][N];
int arr2[N][N];
int ans[N][N];
clock_t start, end;
double result;

using std::cout;
using std::endl;

void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            arr1[i][j] = 1;
            arr2[i][j] = 1;
        }
}

void reset()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            ans[i][j] = 0;
}

void col_mul_1()    //kji
{
    for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void col_mul_2()    //jki
{
    for (int j = 0; j < N; j++)
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void mix_mul_1()    //ijk
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void mix_mul_2()    //jik
{
    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            for (int k = 0; k < N; k++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void row_mul_1()    //kij
{
    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void row_mul_2()    //ikj
{
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
            {
                ans[i][j] += arr1[i][k] * arr2[k][j];
            }
}

void test_row()
{
    cout << "<ROW MUL>" << endl;

    start = clock();
    row_mul_1();
    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "row result 1: " << result << " s" << endl;
    reset();

    start = clock();
    row_mul_2();
    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "row result 2: " << result << " s" << endl;
    reset();

    cout << endl;
}

void test_mixed()
{
    cout << "<MIX MUL>" << endl;

    start = clock();
    mix_mul_1();
    end = clock();
    result = (double)(end - start)/CLOCKS_PER_SEC;
    cout << "mix result 1: " << result << " s" << endl;
    reset();

    start = clock();
    mix_mul_2();
    end = clock();
    result = (double)(end - start)/CLOCKS_PER_SEC;
    cout << "mix result 2: " << result << " s" << endl;
    reset();
    
    cout << endl;
}

void test_col()
{
    cout << "<COL MUL>" << endl;

    start = clock();
    col_mul_1();
    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "col result 1: " << result << " s" << endl;
    reset();

    start = clock();
    col_mul_2();
    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "col result 2: " << result << " s" << endl;
    reset();

    cout << endl;
}

void test()
{
    test_row();
    test_mixed();
    test_col();
}

int main(void)
{
    cout << std::fixed << std::setprecision(3);
    init();
    test();
    return 0;
}
