#include <stdio.h>
#include <stdlib.h>

void naiveMatching(char* arr, char* brr,int size1,int size2)
{
    int tmp = size2 - size1 + 1;
    for (int i = 0; i < tmp; i++)
    {
        char flag = 0;
        for (int j = 0; j < size1; j++)
        {
            if (arr[j] != brr[i + j])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0) goto YES;
    }

    puts("no");
    return;
YES:
    puts("yes");
}

int main(void)
{
    FILE* fp1 = fopen("1.txt","rt");    //pattern
    FILE* fp2 = fopen("2.txt","rt");    //text
    int size1, size2;

    fseek(fp1, 0, SEEK_END);
    fseek(fp2, 0, SEEK_END);
    size1 = ftell(fp1);
    size2 = ftell(fp2);
    fseek(fp1, 0, SEEK_SET);
    fseek(fp2, 0, SEEK_SET);

    char* arr = (char*)malloc(sizeof(char) * (size1+1));
    char* brr = (char*)malloc(sizeof(char) * (size2+1));
    arr[size1] = 0;
    brr[size2] = 0;

    fread(arr,sizeof(char),size1,fp1);
    fread(brr,sizeof(char),size2,fp2);


    puts(arr);
    puts(brr);

    naiveMatching(arr,brr,size1,size2);
    
    fclose(fp1);
    fclose(fp2);
    free(arr);
    free(brr);
    return 0;
}