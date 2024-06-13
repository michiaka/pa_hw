#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct TItem
{
    char *word;
    struct TItem * next;
    struct TItem * nextWord;
    struct TItem * preWord;     
}TITEM;

void freeList(TITEM * lst)
{
    while(lst)
    {
        TITEM * tmp =lst->next;
        free(lst->word);
        free(lst);
        lst=tmp;
    }
}
void skipnonalpha(const char ** buf)
{
    while(!isalpha(**buf))
    {
        (*buf)++;
    }
}

typedef struct
{
    size_t capa;
    size_t len;
    char * data;
}Str;



TITEM * foundStr(TITEM * head, Str str)
{
    TITEM *cur=head;
    TITEM *sameword=nullptr;
    while(cur)
    {
        if(strcmp(cur->word, str.data)==0)
        {
            sameword=cur;
        }
        cur=cur->next;
    }

    return sameword;
}
void resizeStr(Str *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(char *)realloc(arr->data,sizeof(char)*arr->capa);
    }
}

void readalpha(const char ** buf, Str *str)
{
    while(isalpha(**buf))
    {
        resizeStr(str);
        str->data[str->len++]=**buf;
        (*buf)++;
    }
    str->data[str->len]=0;
}
TITEM * stringtoList(const char *str)
{
    const char * ptr= str;    
    TITEM * head=nullptr;
    TITEM * prev=nullptr;

    while(1)
    {
        Str string = {0};
        if(*ptr == 0)
        {
            free(string.data);
            break;
        }
        skipnonalpha(&ptr);
        if(*ptr == 0)
        {
            free(string.data);
            break;
        }
        readalpha(&ptr, &string);
        TITEM *sameword = foundStr(head, string);
        TITEM * newNode=(TITEM *)malloc(sizeof(TITEM));
        newNode->word=strdup(string.data);
        newNode->next=nullptr;
        newNode->nextWord=nullptr;
        newNode->preWord=nullptr;
        if(!prev)
        {
            head=newNode;
        }
        else
        {
            prev->next=newNode;
        }
        if(sameword)//if sameword exist
        {
            sameword->nextWord=newNode;
            newNode->preWord=sameword;
        }
        free(string.data);
        prev=newNode;
    }

    return head;
}


int main()
{
    TITEM *x;
    x=stringtoList("Na louce rostou*rostou +kvetni Na");
    TITEM *cur = x;
    TITEM *prev = nullptr;
    while(cur)    
    {
        printf("%s\n", cur->word);
        prev=cur;
        cur=cur->next;
    }

    while(prev)
    {
        printf("%s\n", prev->word);
        prev=prev->preWord;
    }

    freeList(x);
    
} 