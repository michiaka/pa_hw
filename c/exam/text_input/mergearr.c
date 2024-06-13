#include<stdio.h>
#include<stdlib.h>



typedef struct 
{
    int start;
    int end;
}INTERVAL;

typedef struct 
{
    size_t capa;
    size_t len;
    INTERVAL * data;
} INTERVAL_Arr;


void compare(const void *a , const void *b)
{
    return ((INTERVAL *)a)->start - ((INTERVAL*)b)->start;
}

void connectInterval(INTERVAL_Arr arr1, INTERVAL_Arr *res)
{
    //sort them 
    qsort(arr1.data, arr1.len, sizeof(INTERVAL) , compare);
    for(size_t i = 0; i < arr1.len ; i++)
    {
        // 0 - 
    }

}

int main()
{
    connectInterval(L)