#include<stdio.h>
#include<stdlib.h>


typedef struct 
{
    int dis;
    int alt;   
} POINT;

typedef struct 
{
    size_t capa;
    size_t len;
    POINT * data;
}POINTS;


void resizePOINTS(POINTS * arr)
{
    if(arr->len == arr->capa)
    {
        arr->capa = arr->capa*2 + 10;
        arr->data = (POINT * ) realloc (arr->data,sizeof(POINT)* arr->capa);
    }
}

void push_array(POINTS * arr, int dis, int alt)
{
    resizePOINTS(arr);
    arr->data[arr->len].dis = dis;
    arr->data[arr->len].alt = alt;
    arr->len++;
}

int main()
{
    POINTS all_points = {0};
    printf("Cycle route:\n");
    int start;
    if(scanf("%d", &start) != 1)
    {
        printf("Invalid input\n");
        return -1;
    }
    push_array(&all_points, 0,  start);
    
    char plus;
    while (scanf(" %c", &plus) == 1)
    {
       int dis, alt;
       if(scanf(" %d, %d", &dis, &alt) !=2)
       {
            printf("Invalid input\n");
       }
    //    if(scanf(" %d %d", &di))
        push_array(&all_points, dis, alt);
    }
    if(!feof(stdin))
    {
        printf("Invalid input\n");
        return -1;
    }
    
    
}