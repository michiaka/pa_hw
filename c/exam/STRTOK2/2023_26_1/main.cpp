#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct
{
    size_t capa;
    size_t len;
    char *data;
}Zipcode;

typedef struct
{
    Zipcode code;
    int salary;
}Data;

typedef struct
{
    size_t capa;
    size_t len;
    Data *data;
}Datas;

typedef struct
{
    int salary;
    int ocurrence; 
}Res;

typedef struct 
{
    size_t capa;
    size_t len;
    Res *data;
}Res_Arr;

void desDatas(Datas *arr)
{
    for(size_t i=0;i<arr->capa;i++)
    {
        free(arr->data[i].code.data);
    }
    free(arr->data);
}

void resizeZipcode(Zipcode *arr)
{
    if(!arr)
    {
        printf("NULL----------------\n");
    }
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(char *)realloc(arr->data,sizeof(char)*arr->capa);
    }
}
void resizeDatas(Datas *arr)//outer
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Data *)realloc(arr->data,sizeof(Data)*arr->capa);
        for(size_t i=arr->len;i<arr->capa;i++)
        {
            arr->data[i].code ={0};
            resizeZipcode(&arr->data[i].code);
        }
    }
}

void skipwhite(char ** buf)
{
    while(isspace(**buf))
    {
        (*buf)++;
    }
}
bool insertData(char *line, Datas *datas)
{
    skipwhite(&line);
    if(!isdigit(line[0]))
    {
        printf("HERE\n");
        return false;
    }   
    Zipcode code={0};
    while(isdigit(line[0]))
    {
        resizeZipcode(&code);
        code.data[code.len++]=line[0];
        line++;
    }
    resizeZipcode(&code);
    code.data[code.len]='\0';

    skipwhite(&line);
    int salary=0;
    char extra=0;
    if(sscanf(line, "%d %c", &salary, &extra) !=1)
    {
        free(code.data);
         return false;
    }

    //store
    // datas->data[datas->len].code.data = strdup(code);
    resizeDatas(datas);
    int l =strlen(code.data);
    for(int i=0;i<l;i++)
    {
        resizeZipcode(&datas->data[datas->len].code);
        datas->data[datas->len].code.data[datas->data[datas->len].code.len++]
            =code.data[i];
    }
    resizeZipcode(&datas->data[datas->len].code);
    datas->data[datas->len].code.data[datas->data[datas->len].code.len]='\0';
    datas->data[datas->len].salary = salary;
    free(code.data);
    datas->len++;
    return true;
}

bool salaryexist(Res_Arr * salarys, int salary)
{
    for(size_t i=0; i<salarys->len;i++)
    {
        if(salarys->data[i].salary == salary)
        {
            salarys->data[i].ocurrence++;
            return true;
        }
    }
    return false;
}

void printSalarys(Res_Arr arr)
{
    for(size_t i=0; i<arr.len;i++)
    {
        printf("%d  [%d]\n", arr.data[i].salary, arr.data[i].ocurrence);
    }
}

void resizeRes_Arr(Res_Arr * arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Res *)realloc(arr->data,sizeof(Res)*arr->capa);
        for(size_t i =arr->len; i<arr->capa;i++)
        {
            arr->data[i] = {0};
        }
    }
}
int compare(const void * a, const void *b)
{
    return ((Res*)b)->ocurrence - ((Res*)a)->ocurrence;
}
bool searchData(char *line, Datas *datas)
{
    skipwhite(&line);
    // query
    Res_Arr sameCode={0};
    if(line[0]!='*')
    {
        if(!isdigit(line[0]))
        {
            printf("HERE\n");
            free(sameCode.data);
            return false;
        }   
        Zipcode code={0};
        while(isdigit(line[0]))
        {
            resizeZipcode(&code);
            code.data[code.len++]=line[0];
            line++;
        }
        resizeZipcode(&code);
        code.data[code.len]='\0';

        //search
        for(size_t i=0;i<datas->len;i++)
        {
            if(strlen(code.data) > strlen(datas->data[i].code.data)) continue;
            //if store all the salary whenver code mathc
            if(strncmp(code.data, datas->data[i].code.data, strlen(code.data)) ==0)
            {

                if(!salaryexist(&sameCode, datas->data[i].salary))
                {
                    resizeRes_Arr(&sameCode);
                    sameCode.data[sameCode.len].salary=datas->data[i].salary;
                    sameCode.data[sameCode.len].ocurrence++;
                    sameCode.len++;
                }
            }
        }
        free(code.data);
    }
    else
    {
        for(size_t i=0;i<datas->len;i++)
        {
                if(!salaryexist(&sameCode, datas->data[i].salary))
                {
                    resizeRes_Arr(&sameCode);
                    sameCode.data[sameCode.len].salary=datas->data[i].salary;
                    sameCode.data[sameCode.len].ocurrence++;
                    sameCode.len++;
                }
  
        }
    }

    // printSalarys(sameCode);
    qsort(sameCode.data, sameCode.len, sizeof(Res), compare);
    // printf("=-----------------------------\n");
    printSalarys(sameCode);

    printf("Mode: ");
    int i =0;
    if(sameCode.len == 0)
    {
        printf("N/A\n");
            free(sameCode.data);
            return true;

    }
    else
    {
    while(sameCode.data[i].ocurrence==sameCode.data[0].ocurrence)
    {
        if(i!=0)
        {
            printf(", ");
        }
        printf("%d", sameCode.data[i].salary);
        i++;
        
    }
    printf("[%d]\n", sameCode.data[0].ocurrence);
    free(sameCode.data);
    return true;
    }
}
bool operation(char *line,Datas *datas)
{
    if(line[0] == '+')
    {
        if(!insertData(line+1, datas)) return false;
    }
    else if (line[0] == '?')
    {
        if(!searchData(line+1, datas)) return false;
    }
    else
    {
        return false;
    }

    return true;
}
// void skipwhite(char ")
void printDatas(Datas datas)
{
        for(size_t i=0;i<datas.len;i++)
        {
            printf("%s   %d\n", datas.data[i].code.data, datas.data[i].salary);
        }
}

int main()
{

    Datas datas={0};
    char *line=nullptr;
    size_t capa;
    ssize_t len;
    printf("Data:\n");
    while((len=getline(&line, &capa, stdin))!=EOF)
    {
        if(len<1)continue;
        if(!operation(line, &datas))
        {
            printf("Invalid input.\n");
        }
    }

    // printDatas(datas);
    free(line);
    desDatas(&datas);
    return 0;    

}
