#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//arr = {ptr1,ptr2,ptr3};


typedef struct 
{
    char code[101];
    int ocurrence;
}EAN;

typedef struct 
{
    size_t capa;
    size_t len;
    EAN *data;
} EAN_arr;

void removeNL(char *line, ssize_t len)
{
    if(len > 0 || line[len -1] == '\n')
    {
        line[len -1] = '\0';
    }
}

void resizeEAN_arr(EAN_arr * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa* 2 + 10;
        arr->data = (EAN *)malloc(sizeof(EAN) * arr->capa);
    }
}


bool arrwithDigit(char *arr)
{
    size_t len = strlen(arr);
    for(size_t i = 0; i < len; i++)
    {
        if(arr[i] < '0' ||  arr[i] > '9')
        {
            return false;
        }
    }

    return true;
}


bool find_storeData(EAN_arr *all, char * code)
{
    for(size_t i = 0; i < all->len; i++)
    {
        if(strncmp(all->data[i].code, code, 100) == 0)
        {
            all->data[i].ocurrence ++;
            return true;
        }
    }

    return false;

}
int main()
{
    char * line = NULL;
    size_t capa;
    ssize_t len;
    EAN_arr all = {0};
    while((len = getline(&line, &capa, stdin)) != EOF)
    {
        //when you take string, null termniator is automatically pushed 
        char code[101];
        if(sscanf(line, "%100s", code) != 1 || !arrwithDigit(code))      
        {
            free(line);
            free(all.data);
            printf("Invalid input.\n");
            return -1;
        }

        if(!find_storeData(&all, code))
        {
            resizeEAN_arr(&all);
            // all.data[all.len].code = (char *) malloc(sizeof(char) * 101);
            for(int i = 0; i < 101; i ++)
            {
                all.data[all.len].code[i] = code[i];
            }
            all.data[all.len].ocurrence ++;
            all.len++;
        }
    }

    for(size_t i = 0; i < all.len; i++)
    {
        printf("%s %dx\n", all.data[i].code, all.data[i].ocurrence);
    }
    free(line);
    free(all.data);
    return -1;

}