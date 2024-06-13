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


typedef struct 
{
    POINT start;
    POINT end;
    long dis;
} DISTANCE;

typedef struct 
{
    long capa;
    long len;
    DISTANCE *data;
} DISTANCE_Arr;

void resizePOINT_Arr(POINT_Arr * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa *2 + 10;
        arr->data = (POINT *)realloc(arr->data, sizeof(POINT)* arr->capa );
    }
}
void resizeDISTANCE_Arr(DISTANCE_Arr * arr)
{
        if(arr->capa == arr->len)
    {
        arr->capa = arr->capa *2 + 10;
        arr->data = (DISTANCE *)realloc(arr->data, sizeof(DISTANCE)* arr->capa );
    }
}

void printDISTANCE_Arr(DISTANCE_Arr arr)
{
    for(long i = 0; i < arr.len ; i++)
    {
        printf("%ld %ld, %ld, %ld", arr.data[i].start.dis,
                    arr.data[i].start.alt
                    ,arr.data[i].end.dis
                    ,arr.data[i].end.alt
                    );
        printf("\n");
                    
    }
}
bool insertData(char * line, POINT_Arr *points)
{
    resizePOINT_Arr(points);
    
    if(sscanf(line, "%ld%ld", &(points->data[points->len].dis), &(points->data[points->len].alt)) ==2)
    {
        //printf("points->len %ld,%ld",points->len, points->data[points->len].dis);
        return true;
    }
    else if(sscanf(line, "%ld,%ld", &points->data[points->len].dis, &points->data[points->len].alt) ==2)
    {
        return true;
    }
    return false;
}


bool operation(char * line, POINT_Arr *points)
{
    if(line[0] == '+')
    {
        if(!insertData(line+1, points))
            return false;
    }
    else
    {
        return false;
    }
    return true;

}

int compare_height(const void* a, const void * b)
{
    return (((DISTANCE *)b)->start.alt - (((DISTANCE*)b)->end.alt)) - (((DISTANCE *)a)->start.alt -((DISTANCE *)a)->end.alt) ;
}

int findDecending(POINT_Arr points, DISTANCE_Arr* decreasing, DISTANCE_Arr* max_decreasing)
{

    int max_dif_alt = 0;
    printf("finddecending-----\n");
    for(long i = 0; i < points.len ; i++)
    {
        printf("%ld \n", points.data[i].alt);

    }
    printf("asdfdsafsadfsdadfasdfadsf\n");
    for(long i = 0; i < points.len; i++)
    {
        for(long j = i + 1; j < points.len ; j++)
        {
                resizeDISTANCE_Arr(decreasing);
                decreasing->data[decreasing->len].start = points.data[i];
                decreasing->data[decreasing->len].end = points.data[j];
                decreasing->data[decreasing->len].dis = points.data[j].dis - points.data[i].dis;
                decreasing->len ++;
        }
        
    }
//sort based on the maximus deceending
    if(decreasing->len < 1)
    {
        return -2;
    }
    qsort(decreasing->data, decreasing->len, sizeof(DISTANCE),compare_height);
    //8888122
    printf("start printing -----------------\n");
    printDISTANCE_Arr(*decreasing);
    max_dif_alt = decreasing->data[0].start.alt - decreasing->data[0].end.alt;
    if(max_dif_alt >= 0)
    {
        long count = 0;
        while(count < decreasing->len && max_dif_alt == decreasing->data[count].start.alt - decreasing->data[count].end.alt)
        {
            resizeDISTANCE_Arr(max_decreasing);
            max_decreasing->data[max_decreasing->len].start = decreasing->data[count].start;
            max_decreasing->data[max_decreasing->len].end = decreasing->data[count].end;
            max_decreasing->data[max_decreasing->len].dis = decreasing->data[count].dis;
            max_decreasing->len ++;
            count ++;
        }
    
    }
    return max_dif_alt;
}

int compare(const void * a, const void *b)
{
    return (((DISTANCE *)b)->end.dis - ((DISTANCE *)b)->start.dis) - (((DISTANCE *)a)->end.dis - ((DISTANCE *)a)->start.dis);
}

void findMaxDis(DISTANCE_Arr decreasing, DISTANCE_Arr* res)
{
    if(decreasing.len < 1)
    {
        return;
    }
    qsort(decreasing.data, decreasing.len, sizeof(DISTANCE), compare);
    printf("infindmax, start printing decreasing--after sorting by distance--------------\n");
    printDISTANCE_Arr(decreasing);
    printf("infindmax, finish printing decreasing--after sorting--------------\n");
    //888221
    long count = 0;
    long max = decreasing.data[0].dis;
    while(count < decreasing.len && max == decreasing.data[count].dis)
    {
        resizeDISTANCE_Arr(res);
        res->data[res->len].start = decreasing.data[count].start;
        res->data[res->len].end = decreasing.data[count].end;
        res->data[res->len].dis = decreasing.data[count].dis;
        res->len ++;
        count ++;
    }
    
}

void printResult(DISTANCE_Arr res, long alt_dif)
{


    printf("*%ld km, descent: %ld m, variants: %ld*\n", res.data[0].dis, alt_dif, res.len);
    for(long i = 0; i < res.len ; i++)
    {
        printf("*+ %ld (%ld) -> + %ld (%ld)*\n", res.data[i].start.dis, res.data[i].start.alt, res.data[i].end.dis, res.data[i].end.alt);
    }
}

int main()
{
    char * line = NULL;
    size_t capa = 0;
    ssize_t len =0;
    POINT_Arr points ={0};
    printf("*Cycle route:*\n");
    len = getline(&line, &capa, stdin);
    if(len <= 0)
    {
        printf("Invalid input.\n");
        free(line);
        line = nullptr;
        free(points.data);
        points.data = nullptr;
        return 0;
    }
    resizePOINT_Arr(&points);
    sscanf(line,"%ld", &points.data[0].alt);
    points.data[0].dis =0;
    points.len++;
    while((len = getline(&line, &capa, stdin)) != EOF)
    {
        if(len == 0 || !operation(line, &points))
        {
            printf("Invalid input.\n");
            free(line);
        line = nullptr;
    free(points.data);
    points.data = nullptr;
            return 0;
        }
        points.len++;
    }

        for(long i = 0; i < points.len ; i++)
    {
        printf("%ld ", points.data[i].alt);

    }
    //not invalid
    DISTANCE_Arr all_decending = {0};
    DISTANCE_Arr max_decending ={0};
    long max_dif_alt = 0;
    max_dif_alt = findDecending(points, &all_decending, &max_decending);
    printf("start printing alldecending------------------\n");
    printDISTANCE_Arr(all_decending);
    printf("finish printing alldecending-----------------\n");
    printf("start printing maxdecending--------------\n");
    printDISTANCE_Arr(max_decending);
    printf("finish printing maxdecending--------------\n");

    if(max_decending.len < 1)
    {
        printf("*Not Found*\n");
        free(line);
        line = nullptr;
        free(points.data);
        points.data = nullptr;
        free(max_decending.data);
        free(all_decending.data);
        return 0;
        
    }
    
    DISTANCE_Arr res = {0}; 
    findMaxDis(max_decending, &res);


    free(line);
    line = nullptr;
    free(points.data);
    points.data = nullptr;

    printResult(res, max_dif_alt);
    free(max_decending.data);
    free(all_decending.data);
    free(res.data);

    return 0;
}
