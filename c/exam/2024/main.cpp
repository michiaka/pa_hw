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

void deleteList(TITEM * l)
{
    while(l)
    {
        TITEM *tmp =l->m_Next;
        free(l->m_text);
        free(l);
        l=tmp;
    }
}

//create the node with given text and inser it into the last place of the doubly linked lsit
bool insertItem(S* s, const char *text)
{
    //check if the text is  
    TITEM *cur=s->m_first;
    while(cur)
    {
        if(strcmp(cur->m_text, text) ==0)
        {
            return false;
        }
        cur = cur->m_Next;
    }
    TITEM * newNode = (TITEM *)malloc(sizeof(TITEM));
    newNode->m_text=strdup(text);
    //insert in into the doubly linked list
    if(!s->m_last)//list is empty
    {
        s->m_first=s->m_last=newNode;
        newNode->m_Next=newNode->m_Prev=nullptr;
    }
    else
    {
        newNode->m_Prev = s->m_last;
        s->m_last->m_Next = newNode;
        s->m_last=newNode;
        newNode->m_Next=nullptr;
    }

    //insert into the sorted order of the singly linked list
    TITEM *currentSorted = s->m_sorted;
    TITEM *prevSorted = nullptr;
    while(currentSorted && strcmp(currentSorted->m_text, text)<0)
    {
        prevSorted = currentSorted;
        currentSorted =currentSorted->m_sorted;
    }
    //cur : the next element, prev : the prev element
    if(!prevSorted)
    {
        newNode->m_sorted = s->m_sorted;
        s->m_sorted=newNode;
    }
    else
    {
        //middle or last
        prevSorted->m_sorted = newNode;
        newNode->m_sorted = currentSorted;
    }
    return true;
}


bool search(S* s, const char *text)
{

    bool found=false;
    TITEM * cur = s->m_first;

    while(cur)
    {
        if(strcmp(cur->m_text, text)==0)
        {
            found = true;
        }
        cur=cur->m_Next;
    }
    if(!found)
    {
        return false;
    }
    cur = s->m_first;
    TITEM * prev = nullptr;
    while(cur && strcmp(cur->m_text, text)!=0)
    {
        prev = cur;
        cur=cur->m_Next;
    }

    if(!prev)//cur is the first
    {
        return true;
    }

    //swapping the prev and cur
    if(!prev->m_Prev && !cur->m_Next)//prev being first cur being the last
    {
        prev->m_Prev = cur;
        cur->m_Next= prev;
        prev->m_Next=nullptr;
        cur->m_Prev=nullptr;
        s->m_first=cur;
        s->m_last=prev;
    }
    else if(!prev->m_Prev)//prev being the first
    {
        prev->m_Next = cur->m_Next;
        cur->m_Next->m_Prev=prev;
        prev->m_Prev=cur;
        cur->m_Next=prev;
        cur->m_Prev=nullptr;
        s->m_first=cur;
    }
    else if(!cur->m_Next)//cur being the last
    {
        cur->m_Prev=prev->m_Prev;
        prev->m_Prev->m_Next=cur;
        cur->m_Next =prev;
        prev->m_Prev=cur;
        prev->m_Next=nullptr;
        s->m_last=prev;
    }
    else//prev, cur being in the middle
    {
        prev->m_Prev=cur;
        cur->m_Next=prev;
        prev->m_Next=cur->m_Next;
        cur->m_Next->m_Prev=prev;
        cur->m_Prev=prev->m_Prev;
        cur->m_Prev->m_Next=cur;
    }

    return true;
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

    deleteList(s.m_first);
    return 0;

}