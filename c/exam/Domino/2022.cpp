#include<stdio.h>
#include<stdlib.h>

typedef struct 
{ 
    size_t capa;
    size_t len;
    char *data;    
}ID_Arr;
typedef struct 
{
    ID_Arr ids;
    int all[8];
}DOMINO;

typedef struct 
{   
    size_t capa;
    size_t len;
    DOMINO * data;
}DOMINO_Arr;
void resizeID_Arr(ID_Arr *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa = arr->capa*2+10;
        arr->data=(char *)realloc(arr->data,arr->capa);
    }
}

void resizeDOMINO_Arr(DOMINO_Arr *arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa *2 +10;
        arr->data =(DOMINO *)realloc(arr->data,sizeof(DOMINO)*arr->capa);
        for(size_t i = arr->len;i<arr->capa;i++)
        {
            arr->data[i].ids.data=nullptr;
            resizeID_Arr(&(arr->data[i].ids));
        }
    }
}

void destroyDOMINO_Arr(DOMINO_Arr *arr)
{
    for(size_t i = 0; i<arr->len;i++)
    {
        free(arr->data[i].ids.data);
    }
    free(arr->data);
}

void searchData(DOMINO_Arr * dominos, int *arr, char id)
{
    for(size_t i = 0;i<dominos->len;i++)
    {
        for(size_t j=0;j<4;j++)
        {
            if(dominos->data[i].all[j]==arr[0] && dominos->data[i].all[j+1]==arr[1]
            &&dominos->data[i].all[j+2]==arr[2] && dominos->data[i].all[j+3]==arr[3]
            )
            {
                resizeID_Arr(&(dominos->data[i].ids));
                dominos->data[i].ids.data[dominos->data[i].ids.len++] =  id;
                return;
            }
        }
    }
    //not found
    resizeDOMINO_Arr(dominos);
    dominos->data[dominos->len].ids.data[dominos->data[dominos->len].ids.len++] = id;
    for(int i = 0; i<8; i++)
    {
        dominos->data[dominos->len].all[i] = arr[i%4];    
    }
    dominos->len++;

}
int main()
{
    printf("Enter:\n");
    char * line = NULL;
    size_t capa = 0;
    int arr[8];
    DOMINO_Arr dominos = {0};
    char cur_id='a';
    while(getline(&line, &capa, stdin) != EOF)
    {
        char id = 0,last_bracket=0,extra=0;
        if(sscanf(line, "%c [%d, %d, %d, %d%c %c", &id, &arr[0], &arr[1],
                                                             &arr[2], &arr[3], 
                                                             &last_bracket, &extra) != 6 
                                                             || last_bracket != ']' 
                                                             || cur_id != id)
        {
            printf("Invalid input.\n");
            destroyDOMINO_Arr(&dominos);
            free(line);
            return 0;   
        }
        cur_id++;
        searchData(&dominos, arr, id);
    }

    printf("Unique: %zu\n", dominos.len);
    printf("Duplicates:\n");
    for(size_t i = 0; i<dominos.len;i++)
    {
        for(size_t j = 0; j<dominos.data[i].ids.len; j++)
        {
            if(dominos.data[i].ids.len > 1)
            {
            printf("%c", dominos.data[i].ids.data[j]);
            if(j < dominos.data[i].ids.len -1 )
            {
                printf(" = ");
            }
            }
        }
        if(dominos.data[i].ids.len > 1)
             printf("\n");
    }

    destroyDOMINO_Arr(&dominos);
    free(line);
    return 0;

}