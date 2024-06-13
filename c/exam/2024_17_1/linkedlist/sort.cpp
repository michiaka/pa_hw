#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct Titem
{
    Titem * m_Next;
    Titem * m_Prev;
    char * m_text;
}TITEM;

typedef struct
{  
    TITEM * m_first;
    TITEM * m_last;
}S;

void deleteList(TITEM *lst)
{
    while(lst)
    {
        TITEM * tmp = lst->m_Next;
        free(lst->m_text);
        free(lst);
        lst=tmp;
    }
}

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

    return true;
}

void swapLists(S*s , TITEM * prev, TITEM *cur)
{
    if(!prev)
    {
        printf("no need to swap\n");
        return;
    }
    if(!cur)
    {
        printf("no need to swap cuz that is the last\n");
        return ;
    }
    if(!prev->m_Prev && !cur->m_Next)
    {
        s->m_first=cur;
        s->m_last=prev;
        cur->m_Next=prev;
        prev->m_Prev=cur;
        cur->m_Prev=nullptr;
        prev->m_Next=nullptr;
    }
    else if(!prev->m_Prev)
    {
        s->m_first=cur;
        cur->m_Next->m_Prev=prev;
        prev->m_Next=cur->m_Next;
        cur->m_Next=prev;
        prev->m_Prev=cur;
        cur->m_Prev=nullptr;
    }
    else if(!cur->m_Next)
    {
        s->m_last=prev;
        prev->m_Prev->m_Next=cur;
        cur->m_Prev=prev->m_Prev;
        cur->m_Next = prev;
        prev->m_Prev= cur;
        prev->m_Next=nullptr;
    }
    else
    {
        cur->m_Next->m_Prev=prev;
        prev->m_Prev->m_Next=cur;
        cur->m_Prev=prev->m_Prev;
        prev->m_Next=cur->m_Next;
        cur->m_Next=prev;
        prev->m_Prev=cur;
    }
}

void printList(S *s)
{
    printf("------------------------------------\n");
    TITEM * currentDoubly=s->m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");
    printf("------------------------------------\n");

}


void bubblesortList(S *s)
{
    TITEM  *cur = s->m_first;
    int count = 0;
    while(cur)
    {
        count++;
        cur = cur->m_Next;
    }
    printf("%d\n", count);


    for(int i = 0;i<count;i++)
    {
        TITEM * left = s->m_first;
        for(int k = 0;k < count - i - 1;k++)
        {
            if (left != NULL && left->m_Next && strcmp(left->m_text, left->m_Next->m_text) > 0)
            {
                swapLists(s, left, left->m_Next);
                left = left->m_Next;
            }
        }   
    }
    
}


int main()
{
    S s={0};

    if (!insertItem(&s, "5"));
    if (!insertItem(&s, "1"));
    if (!insertItem(&s, "4"));
    if (!insertItem(&s, "3"));
    if (!insertItem(&s, "2"));
    if (!insertItem(&s, "6"));

    // swapLists(&s, s.m_first->m_Next, s.m_first->m_Next->m_Next);
    //display the douly linked list 
    TITEM * currentDoubly=s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");

    bubblesortList(&s);
    currentDoubly=s.m_first;
    while(currentDoubly !=NULL)
    {
        printf("%s ->", currentDoubly->m_text);
        currentDoubly=currentDoubly->m_Next;
    }
    printf("NULL\n");
    deleteList(s.m_first);
    return -1;

}