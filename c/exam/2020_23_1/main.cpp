#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct
{
    char code[101];
    int num;
} EAN;

typedef struct
{
    size_t capa;
    size_t len;
    EAN *data;
}Warehouse;

void resizeWarehouse(Warehouse *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(EAN *)realloc(sizeof(EAN)*arr->capa);
    }
}
void printWarehouse(Warehouse arr)
{
    for(size_t i=0;i<arr->len;i++)
    {
        printf("%dx %s\n", arr.data[i].num, arr.data[i].code);
    }
}

void skipwhite(char **buf)
{
    while(isspace(**buf))
    {
        (*buf)++;
    }
}
bool isValidcode(char *code)
{
    int l=strlen(code);
    if(l < 5 || l<100)
        return false;
    for(int i=0;i<l;i++)
    {
        if(!isdigit(code[i]))
            return false;
    }

    return true;
}

void addUnique(Warehouse *arr, char* code)
{
    for(size_t i=0; i<arr->len;i++)
    {
        if(strcmp(arr->data[i].code, code)==0)
        {
            arr->data[i].num++;
        }
    }

    resizeWarehouse(arr);
    strcpy(arr->data[i], )


}
bool readLine(char *line, Warehouse *warehouse)
{
    skipwhite(&line);
    if(line[0] != '+'&& line[1]!= '-')
        return false;
    line++;
    char num=0;char code[101];char extra=0;
    if(sscanf(line, " %dx %100s %c", &num, &code, &extra)!=2)
    {
        return false;
    }
    if(!isValidcode(code))
    {
        return false;
    }

    addUnique(warehouse, code);
}
int main()
{
    char *line=nullptr;
    size_t capa;
    ssize_t len;
    Warehouse warehouse ={0};
    while((len=getline(&line, &capa, stdin) !=EOF))
    {
        char *str=line;
        if(len==1 && line[0]='\n')continue;
        if(len<1||!readLine(str, &warehouse))
        {
            printf("Invalid input.\n");
            free(line);
            free(warehouse.data);
            return -1;
        }
    }
    
    printWarehouse(warehouse);

    free(line);
    free(warehouse.data);
    return -1;
}
