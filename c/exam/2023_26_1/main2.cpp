#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
//a) star: seachALL b) digits: search based on that

//point: reading string: add '\0' at the end without increasing the length
//point2: 
typedef struct
{
    size_t capa;
    size_t len;
    char * data;
}Code;

typedef struct
{
    int salary;
    Code code;
}Data;

typedef struct
{
    size_t capa;
    size_t len;
    Data * data;
}Datas;

typedef struct 
{
    int salary;
    int occurence;
}Salary;

typedef struct 
{
    size_t capa;
    size_t len;
    Salary *data;
}Salarys;

void desCode(Code *arr)
{
    free(arr->data);
    arr->data=nullptr;
}

void desDatas(Datas *arr)
{
    for(size_t i=0;i<arr->len;i++)
    {
        desCode(&arr->data[i].code);
    }
    free(arr->data);
}


void resizeSalarys(Salarys* salarys)
{
    if(salarys->len == salarys->capa)
    {
        salarys->capa = salarys->capa*2+10;
        salarys->data = (Salary *)realloc(salarys->data, sizeof(Salary)*salarys->capa);
        for(size_t i=salarys->len;i<salarys->capa;i++)
        {
            salarys->data[i] = {0};
        }
    }
}
void resizeCode(Code *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(char*)realloc(arr->data, sizeof(char)*arr->capa);//leak 
        
        for(size_t i=arr->len;i<arr->capa;i++)
        {
            arr->data[i]= 0;
        }
    }
}


void initData(Data * data)
{
    data->salary=0;
    data->code ={0};
}

void resizeDatas(Datas * arr)
{ 
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Data*)realloc(arr->data,sizeof(Data)*arr->capa);
        for(size_t i = arr->len; i<arr->capa;i++)
        {
            initData(&arr->data[i]);//initilize for the element(Data) create
        }   
    }  
}

void skipwhite(char **buf)
{
    while(isspace(*(*buf)))
    {
        (*buf)++;
    }
}

bool readCode(char **buf, Code* code)
{
    if(!isdigit(*(*buf)))
    {
        return false;
    }
    while(isdigit(*(*buf)))
    {
        resizeCode(code);
        code->data[code->len++]=(*(*buf));
        (*buf)++;
    }
    //make sure adding the null terminator
    resizeCode(code);
    code->data[code->len] = '\0';//lenth of the stirng should include the null terminator
    return true;
}

bool isduplicate(Datas *datas, Code code)
{
    for(size_t i=0;i<datas->len;i++)
    {
        if(code.len != strlen(datas->data[i].code.data))
        {
            continue;
        }
        if(strcmp(datas->data[i].code.data, code.data) == 0)
        {
            return true;
        }
    }
    return false;
}

bool insertData(char *line, Datas *datas)
{
    skipwhite(&line);
    Code code ={0};
    if(!readCode(&line, &code))
    {
        free(code.data);
        return false;
    }
    // if(isduplicate(datas, code))
    // {
    //     printf("Invalid input\n");
    //     free(code.data);
    //     return true;
    // }
    skipwhite(&line);
    int salary = 0;
    if(sscanf(line, "%d", &salary) != 1)
    {
        free(code.data);
        return false;
    }
    if(salary < 0)
    {
        free(code.data);
        return false;
    }
    resizeDatas(datas);
    datas->data[datas->len].code.data = (char *)malloc(code.len + 1);
    datas->data[datas->len].code.len = code.len;
    strncpy(datas->data[datas->len].code.data, code.data, code.len);//strncpy ovr strcpy
    datas->data[datas->len].code.data[code.len]= '\0';
    datas->data[datas->len].salary=salary;
    datas->len++;
    free(code.data);
    return true;
}

void printSalary(Salarys arr)
{
    for(size_t i=0;i<arr.len;i++)
    {
        printf("salarys[%zu]: salary %d [%d]\n", i, arr.data[i].salary, arr.data[i].occurence);

    }
}

int compare_Salarys(const void * a, const void *b)
{
    return ((Salary *)b)->occurence - ((Salary *)a)->occurence;
}


bool id_match(bool isStar, Code searchCode, Code code)
{
    if(isStar) return true;
    if(strncmp(searchCode.data, code.data, searchCode.len) ==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printDatas(Datas datas)
{
    for(size_t i= 0;i<datas.len;i++)
    {
        printf("%s %d\n",datas.data[i].code.data, datas.data[i].salary);
    }
}
bool searchData(char *line, Datas datas)
{

    printDatas(datas);
    skipwhite(&line);
    char star=0, extra=0;
    bool isStar = false;
    Code code={0};
    Salarys res = {0};
    if(sscanf(line, "%c %c", &star, &extra) == 1 && star=='*')
    {       
        isStar = true;    
    }
    else
    {
        if(!readCode(&line, &code))
        {
            return false;
        }
    }
    size_t l = code.len;
    for(size_t i = 0; i<datas.len;i++)
    {
        if(l > datas.data[i].code.len)//the seachcommnad is longer than data
        {
            continue;
        }
        if(id_match(isStar, code, datas.data[i].code))
       //storing unique salarys of the corresponding
        {
            bool found = 0;
            for(size_t j=0;j<res.len;j++)
            {
                if(res.data[j].salary == datas.data[i].salary)
                {
                    res.data[j].occurence++;
                    found = 1;
                }
            }
            if(!found)
            {
                resizeSalarys(&res);
                res.data[res.len].salary=datas.data[i].salary;
                res.data[res.len].occurence++;
                res.len++;
            }

        }
    }

    
    // printf("before sorting.-----------------------------\n");
    // printSalary(res);
    //based on the occurrece
    qsort(res.data, res.len, sizeof(Salary), compare_Salarys);
    // printf("after sorting-----------------------------\n");
    // printSalary(res);
    printf("------------------------\n");
    if(res.len == 0)
    {
        printf("Modus: N/A\n");
    }
    else
    {
        int i = 0;
        printf("Modus: ");
        while(res.data[0].occurence==res.data[i].occurence)
        {
            if(i==0)
            {
                printf("%d",res.data[i].salary); 
            }
            else
            {
                printf(", %d",res.data[i].salary);
            }
            i++;
        }
        printf(" [%d]\n", res.data[0].occurence);
    }
    printf("------------------------\n");
    
    free(code.data);
    free(res.data);
    return true;

}


bool operation(char *line, Datas* datas, bool * searched)
{
    if(line[0]=='+')
    {
        if(*searched)
        {
            return false;
        }
        if(!insertData(line+1, datas))
        {
            return false;
        }
    }
    else if(line[0]=='?')
    {

        if(!searchData(line+1, *datas))
        {
            return false;
        }
        //seaedhc without problems
        *searched = true;
    
    }
    else
    {
        return false;
    }
    return true;
}
int main()
{
    char *line =NULL;
    size_t capa =0;
    ssize_t len=0;
    Datas datas = {0};//initialization of 2d d.arr. => not have to allocate
    printf("Data:\n");
    bool searched = false;
    while((len =(getline(&line, &capa,stdin))) != EOF)
    {
        if(len<0||!operation(line, &datas, &searched))
        {
            printf("Invalid input.\n");
        }
    }

    free(line);
    desDatas(&datas);
    return 0;
}