#include<stdio.h>
#include<stdlib.h>


typedef struct 
{
    int load;
    int start;
    int end;
}LOG;

typedef struct 
{
    size_t capa;
    size_t len;
    LOG *data;
} LOG_Arr;


void printLOG_Arr(LOG_Arr arr)
{
    for(size_t i = 0; i< arr.len;i++)
    {
        printf("arr[%zu]: %d: %d..%d\n", i, arr.data[i].load, arr.data[i].start, arr.data[i].end);
    }
}
void resizeLOG_Arr(LOG_Arr * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa * 2+ 10;
        arr->data = (LOG *)realloc(arr->data, sizeof(LOG)* arr->capa);
    }
}

bool intersection(LOG log1, LOG log2, int *start, int *end)
{
    *start = (log1.start > log2.start) ? log1.start : log2.start;
    *end = (log1.end > log2.end) ? log2.end : log1.end;

    if(*start >= *end)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void createAllInterVal(LOG_Arr * arr)
{
    for(size_t i = 0; i < arr->len; i++)
    {
        for(size_t j = i+1; j < arr->len; j++)
        {
            int start = 0;int end = 0;
            int s1 = arr->data[i].start; 
            int s2 = arr->data[j].start;
            int e1 = arr->data[i].end;
            int e2 = arr->data[j].end;
            if(intersection(arr->data[i], arr->data[j], &start, &end))
            {
                printf("intersection here [%zu][%zu]\n", i, j);
                if(s1 <= s2 && e1 <= e2 )
                {
                    resizeLOG_Arr(arr);
                    arr->data[arr->len].load = arr->data[i].load + arr->data[j].load;
                    arr->data[arr->len].start = start;
                    arr->data[arr->len].end = end;
                    arr->len++;

                    arr->data[i].end = start;
                    arr->data[j].start = end;
                    
                }                
                else if(s2 <= s1 && e2 <= e1)
                {
                    resizeLOG_Arr(arr);
                    arr->data[arr->len].load = arr->data[i].load + arr->data[j].load;
                    arr->data[arr->len].start = start;
                    arr->data[arr->len].end = end;
                    arr->len++;

                    arr->data[i].start = end;
                    arr->data[j].end = start;
                }
                else if(s1 <= s2 && e2 <= e1)
                {
                    resizeLOG_Arr(arr);
                    arr->data[arr->len].load = arr->data[i].load; 
                    arr->data[arr->len].start = arr->data[j].end;
                    arr->data[arr->len].end = arr->data[i].end;
                    arr->len++;

                    arr->data[j].load = arr->data[i].load + arr->data[j].load; 
                    arr->data[i].end = arr->data[j].start;
                }
                else//all oposite 
                {
                    resizeLOG_Arr(arr);
                    arr->data[arr->len].load = arr->data[j].load; 
                    arr->data[arr->len].start = arr->data[i].end;
                    arr->data[arr->len].end = arr->data[j].end;
                    arr->len++;

                    arr->data[i].load = arr->data[i].load + arr->data[j].load; 
                    arr->data[j].end = arr->data[i].start;
                }
            }
            
        }
    }
}

int compare(const void* a, const void* b)
{
    return ((LOG *)a)->start - ((LOG *)b)->end;
}
void connectInterval(LOG_Arr res, LOG_Arr *merged)
{
    //sort them based on the starting value of the interval
    qsort(res.data, res.len, sizeof(LOG), compare);
    printf("after sorting based on the start\n");
    printLOG_Arr(res);
    for(size_t i = 0; i < res.len; i++)
    {
        size_t start = i;
        size_t j = i + 1;
        while(res.data[i].end == res.data[j].start && j < res.len)
        {
            //0 - 1, 1 -2, 2 - 3
            printf("i:%zu, j:%zu\n", i, j);
            i++;
            j++;
        }
        j -= 1;
        printf("start: %zu, j: %zu\n", start, j);
        resizeLOG_Arr(merged);
        merged->data[merged->len].start = res.data[start].start;
        merged->data[merged->len].end = res.data[j].end; 
        merged->data[merged->len].load = res.data[j].load;
        merged->len ++;
    }

}
int main()
{
    LOG_Arr log = {0};
    log.data = nullptr;

    printf("Load:\n");


    resizeLOG_Arr(&log);
    //gets out either EOF or different valeu
    while(scanf("%d:%d..%d", &log.data[log.len].load, &log.data[log.len].start, 
                            &log.data[log.len].end) == 3)
    {
        resizeLOG_Arr(&log);
        log.len ++;
    }
    if(!feof(stdin) || log.len < 1)
    {
        if(!feof(stdin))
        {
            printf("extra\n");
        }
        printf("Invalid Input\n");
        printf("extra thing or less\n");
        free(log.data);
        log.data = nullptr;
        return -1;
    }
    printf("print log.-------------------------\n");
    printLOG_Arr(log);

    createAllInterVal(&log);
    printf("print log.-------------------------\n");
    printLOG_Arr(log);
    //iterate to find the max load
    int max_load = log.data[0].load;
    for(size_t i = 0; i< log.len ;i++)
    {
        max_load = (log.data[i].load > max_load) ? log.data[i].load : max_load;
    }
    //put all the elements with the load
    LOG_Arr res ={0};
    for(size_t i = 0; i<log.len; i++)
    {
        if(max_load == log.data[i].load)
        {
            resizeLOG_Arr(&res);
            res.data[res.len].start = log.data[i].start;
            res.data[res.len].end = log.data[i].end;
            res.data[res.len].load = log.data[i].load;
            res.len ++;
        }
    }

    LOG_Arr merged = {0};
    connectInterval(res, &merged);
    //print
    printf("Maximum load: %d\n", max_load);
    for(size_t i = 0; i< merged.len; i++)
    {
        printf("%d..%d\n", merged.data[i].start, merged.data[i].end);
    }

    free(log.data);
    free(res.data);
    free(merged.data);
    log.data = nullptr;
}