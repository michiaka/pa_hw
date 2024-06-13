#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>


typedef struct Titem
{
    struct Titem *m_Next;
    struct Titem *m_Prev;
    struct Titem *m_sorted;
    char  *m_text;
}TITEM;

typedef struct
{
    TITEM * m_first;
    TITEM * m_last;
    TITEM *m_sorted;
}S;

void deleteList(TITEM * list)
{
    while(list)
    {
        TITEM *tmp=list->m_Next;
        free(list->m_text);
        free(list);
        list = tmp;
    }
}
//to implement
bool insertItem(S*s, const char *text)
{
    TITEM * cur = s->m_first;
    bool duplicatefound=false;
    while(cur)
    {
        if(strcmp(text, cur->m_text)==0)
        {
            duplicatefound = true;
        }
        cur = cur->m_Next;
    }
    if(duplicatefound)
    {
        return false;
    }   
    TITEM * newNode=(TITEM *)malloc(sizeof(TITEM));
    newNode->m_text=strdup(text);
    newNode->m_Next = nullptr;
    if(!s->m_first)//empty
    {
        s->m_first=newNode;
        s->m_last=newNode;
        newNode->m_Prev=nullptr;
    }
    else 
    {
        newNode->m_Prev=s->m_last;    
        s->m_last->m_Next=newNode;
        s->m_last=newNode;    
    }

    //sorted linked list
    TITEM * cur_sorted=s->m_sorted;
    TITEM * prev_sorted=nullptr;
    while(cur_sorted && strcmp(text, cur_sorted->m_text) > 0)
    {
        prev_sorted=cur_sorted;
        cur_sorted=cur_sorted->m_sorted;
    }
    newNode->m_sorted = cur_sorted;
    if(!prev_sorted)
    {
        s->m_sorted = newNode;
    }
    else
    {
        prev_sorted->m_Next=newNode;
    }

    return true;
}

bool search(S *s, const char *text)
{
    return false;
}


int main()
{
    S s={0};

    if (!insertItem(&s, "1"));
    if (!insertItem(&s, "2"));
    if (!insertItem(&s, "3"));
    if (!insertItem(&s, "4"));
    if (!insertItem(&s, "5"));
    if (!insertItem(&s, "6"));
    if (!insertItem(&s, "7"));

    //display the douly linked list 
    TITEM * currentDoubly=s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");

    //display the singly linked list 

    TITEM *currentSingly=s.m_sorted;
    while(currentSingly!=NULL)
    {
        printf("%s ->", currentSingly->m_text);
        currentSingly = currentSingly->m_sorted;
    }
    printf("NULL\n");

    //search for "banana" and swap with the next node in the doubly linked list
    if(!search(&s, "apple"))
    {
        printf("Text not found\n");
    }


    deleteList(s.m_first);
    return -1;

    //display the doubly linked list after the swap
    currentDoubly = s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");


}