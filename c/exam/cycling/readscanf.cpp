#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct 
{
    long dis;
    long alt;
} POINT;

typedef struct 
{
    long capa;
    long len;
    POINT * data;
} POINT_Arr;


void resizePOINT_Arr(POINT_Arr * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa *2 + 10;
        arr->data = (POINT *)realloc(arr->data, sizeof(POINT)* arr->capa );
    }
}


bool readInput(POINT_Arr * points)
{   
    resizePOINT_Arr(points);
    if(scanf("%ld ", &points->data[points->len].alt) == 1) 
    {
        points->data[points->len].dis = 1;
        points->len++;
        while(1)
        {
            resizePOINT_Arr(points);
            if(scanf(" + %ld %ld", &points->data[points->len].dis, &points->data[points->len].alt) == 2)
            {
                points->len++;
                continue;
            }
            else if(scanf(" + %ld,%ld", &points->data[points->len].dis, &points->data[points->len].alt) == 2)
            {
                points->len++;
                continue;
            }
            else
            {
                break;
            }
        }
        if(!feof(stdin) || points->len < 2)
        {
            printf("extra or not enough\n");
            return false;
        }
        return true;
    }
    else
        return false;
}



int main()
{
    
    POINT_Arr points = {0};
    if(!readInput(&points))
    {
        printf("invalid\n");
    }

    free(points.data);
    return 0;
}