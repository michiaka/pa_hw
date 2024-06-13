#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>

typedef struct Titem
{
    struct Titem * m_Next;
    struct Titem * m_Prev;
    struct Titem * m_Sorted;
    char * m_text;
}TITEM;

typedef struct
{
    TITEM *m_first;
    TITEM *m_last;
    TITEM *m_Sorted;
}S;


void find_same(TITEM **cur, TITEM **prev, char *text)
{
    while(*cur)
    {
        if(strcmp((*cur)->text, text) == 0)
        {
            break;
        }
        *prev=*cur;
        *cur=(*cur)->m_Next;
    }
}

/**
*@arg:2 pointers to items to swap, S* s
* modify s->first, s->last when prev is the first or cur is the last 
*/
void swap_item(TITEM *cur, TITEM *prev)
{   
    if(!prev){}

    //!a->m_Prev == a being the first element, !b->m_Next == b being the last element
    if(!prev->m_Prev && !cur->m_Next)//one being first, cur being the last
    {    
        s->last = prev;
        s->m_first = cur;
        cur->m_Next = prev;
        prev->m_Prev = cur;
    }
    else if(!prev->m_Prev)
    else if(!cur->m_Next)
    else if
}

bool search(S*s, char *text)
{
    TITEM *cur=s->m_first;
    bool found=false;
    while(cur)
    {
        if(strcmp(cur->m_text,text) ==0)
        {
            found=true; 
            break;
        }
    }
    if(!found)
    {
        return false;
    }
    cur=s->m_first;
    TITEM *prev=nullptr;
    find_same(&cur,&prev,text);
    swap_item(s, cur, prev);
}

bool insertItem(S*s, char *text)
{
   
}