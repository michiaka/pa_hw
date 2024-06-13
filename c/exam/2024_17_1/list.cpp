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
    while(cur_sorted)
    {
        
        cur_sorterd=cur_sorted->m_sorted;
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

    if (!insertItem(&s, "banana"))
    {
        printf("Text already in the list\n");
    }
    if (!insertItem(&s, "apple"))
    {
        printf("Text already in the list\n");
    }

    //display the douly linked list 
    TITEM * currentDoubly=s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");
    deleteList(s.m_first);
    return -1;
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


    //display the doubly linked list after the swap
    currentDoubly = s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");

    return 0;

}