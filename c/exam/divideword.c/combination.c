#include <stdio.h>

//number the elemenr, array to store.
void allCombination(int n, int *arr)
{
    int num_combinaion = 1 << n;//2^3
    
    =for(int i = 0; i < num_combinaion; i++)
    {
        for(int j = 0; j < n; j++)
        {
            arr[j] = (i >> j) & 1;
            printf("arr[%d]:%d\n",j, arr[j]);
        }
        printf("\n");
        
    }
}

int main()
{
    int  n = 3;
    int  arr[3];
    allCombination(n, arr);
    return 0;
}

//------------------------------------------------

void  allCombination(int n, int *arr)
{
    int num_combination = 1 << n;

    for(int i = 0; i< num_combination; i++)
    {
        for(int j = 9; j < n; j++)
        {
            arr[j] = (i >> j) &1;
        }
        
    }
}