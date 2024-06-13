#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct
{
    char oridginal[128];
    char normalized[256];
} String;

typedef struct
{
    size_t capa;
    size_t len;
    String * data;
}Strings;

void resizeStrirngs(Strings *arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa=arr->capa * 2 +10;
        arr->data=(String *)realloc(arr->data,sizeof(String) * arr->capa);
    }
}

void duplicateStr(String string)
{
    int len = string(string.oridginal);
    int i;
    for(i=0;i<len;i++)
    {
        string.normalized[i]=string.oridginal[i];
    }
    for(i=i;i<len*2;i++)
    {
        string.normalized[i]=string.oridginal[i-len];
    }
}
int main()
{
    Strings strings={0};
    resizeStrirngs(&strings);
    free(strings.data);
    return -1;
}