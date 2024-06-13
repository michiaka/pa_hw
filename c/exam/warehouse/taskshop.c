#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct 
{
    /* data */
    int stock;
    char ean[101];
}Stock;

typedef struct 
{
    /* data */
    size_t capa;
    size_t len;
    Stock * data;
}Stocks;

bool insertData(char *buf,Stocks *stocks)
{
    int increment=0;char ean[102];
    if(sscanf(buf," %dx %101s", &increment,
                             ean) != 2) 
    {
        printf("invalid format\n");
        return false;
    }

    if(increment<1)
    {
        printf("not positive\n");
        return false;
    }
    int l=strlen(ean);
    if(l<5 ||l>100)
    {
        return false;
    }
    for(int i=0;i<l;i++)
    {
        if(ean[i]>'9'||ean[i]<'0')
        {
            return false;
        }
    }

    for(size_t i=0;i<stocks->len;i++)
    {
        if(strcmp(ean, stocks->data[i].ean)==0)
        {
            stocks->data[i].stock+=increment;
            printf("> %dx\n",stocks->data[i].stock);
            return true;   
        }
    }
    
    if(stocks->len == stocks->capa)
    {
        stocks->capa=stocks->capa*2+10;
        stocks->data=(Stock*)realloc(stocks->data,sizeof(Stock)*stocks->capa);
        for(size_t i=stocks->len;i<stocks->capa;i++)
        {
            stocks->data[i]={0};
        }
    }
    stocks->data[stocks->len].stock += increment;
    printf("> %dx\n",stocks->data[stocks->len].stock);
    strcpy(stocks->data[stocks->len].ean, ean);
    stocks->len++;
    return true;
}

bool find_remove(char *buf,Stocks *stocks)
{
    int decrement=0;char ean[102];
    if(sscanf(buf," %dx %101s", &decrement,
                             ean) != 2) 
    {
        printf("invalid format\n");
        return false;

    }
    if(decrement<1)
    {
        return false;
    }
    int l=strlen(ean);
    if(l<5 ||l>100)
    {
        return false;
    }
    for(int i=0;i<l;i++)
    {
        if(ean[i]>'9'||ean[i]<'0')
        {
            return false;
        }
    }
    for(size_t i=0;i<stocks->len;i++)
    {
        if(strcmp(ean, stocks->data[i].ean)==0)
        {
            int tmp = stocks->data[i].stock -decrement;
            
            if(tmp<0)//dont edit unless the result of the computation is valid

            {
                printf("Insufficient stock\n");
                return true;
            }
            else
            {
                stocks->data[i].stock-=decrement;
            printf("> %dx\n",stocks->data[i].stock);
            return true;
            }  
        }
    }

printf("Insufficient stock\n");
return true;

}
bool operation(char* line, Stocks *stocks)
{
    if(line[0] == '+')
    {
        if(!insertData(line+1,stocks))
            return false;
    }
    else if(line[0] == '-')
    {
        if(!find_remove(line+1,stocks))
            return false;
    }
    else 
    {
        return false;
    }
    return true;
}

int main()
{

    char *line=NULL;
    size_t capa=0;
    ssize_t len=0;
    Stocks stocks ={0};
    while((len=(getline(&line, &capa, stdin)))!= EOF)
    {
        if(len<0||!operation(line,&stocks))
        {
            printf("Don't edit ny entrance .\n");
        }
    }


    free(line);
    free(stocks.data);
    return 0;
}