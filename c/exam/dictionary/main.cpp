#include<stdio.h>
#include <cstdlib>
#include <cstring>


// typedef struct
// {
//     size_t capa;
//     size_t len;
//     char *data;
// } Word;

typedef struct
{
    char word[31];
    int size;
}Word;

typedef struct
{
    size_t capa;
    size_t len;
    Word *data;
}Dictionary;


void resizeDic(Dictionary *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Word *)realloc(arr->data,sizeof(Word));
    }
}

void storedata(char * pch, Dictionary *dic)
{
    resizeDic(dic);
    dic->data[dic->len].size=strlen(pch);
    strcpy(dic->data[dic->len].word, pch);
    dic->len++;
}

void printData(Dictionary data)
{
    for(size_t i=0;i<data.len;i++)
    {
        printf("%s ", data.data[i].word);
    }
    printf("\n");
}


bool readInput(Dictionary *dic, Dictionary *text)
{
    char *line=nullptr;
    size_t capa;
    bool delimiter_found=false;
    char *pch;
    bool begining_txt=false;
    printf("Dictionary:\n");
    while(getline(&line, &capa, stdin)!=EOF)
    {
        char *str=line;
        pch= strtok(str, " ");
        if(!delimiter_found)
        {

            while(pch !=NULL)
            {
                if(strcmp(pch, "*****") ==0)
                {   
                    delimiter_found=true;
                    pch=strtok(NULL, " ");
                    break;
                }
                printf("%s \n", pch);
                // storedata(pch, dic);
                pch=strtok(NULL, " ");
            } 
        }
        if(delimiter_found)
        {   if(begining_txt)
            {
                printf("Text:\n");//case1, case2: execute case1->set it to case2 afterW
                begining_txt=false;
            }
            while(pch != NULL)
            {
                printf("%s \n", pch);
                // storedata(pch, text);
                pch=strtok(NULL," ");
            }
        }
    }
    return true;
}
int main()
{
    Dictionary dic={0};
    Dictionary text={0};
    if(!readInput(&dic, &text))
    {
        printf("Invalid input.\n");
        free(dic.data);
        return -1;
    }

    printf("dictionary:-----------------------------\n");
    printData(dic);
    printf("text:-----------------------------\n");
    printData(text);
    free(dic.data);
    free(text.data);
    return 0;
}
