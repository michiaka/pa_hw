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

//insert in the sorted place
bool insertITEM(S *s, const char * text)
{   
    TITEM * cur = s->m_first;
    while(cur)
    {
        if(strcmp(text, cur->m_text)==0)
        {
            return false;
        }
        cur=cur->m_Next;
    }
    cur = s->m_first;
    TITEM * prev = nullptr;
    while(cur && strcmp(text, cur->m_text) >= 0)
    {
        prev = cur;
        cur = cur->m_Next;
    }
    // cur being the next
    // prev being the prev
    TITEM * newNode = (TITEM *) malloc (sizeof(TITEM));
    newNode->m_text=strdup(text);
    if(!cur)
    {
        s->m_last=newNode;
    }
    else
    {
        cur->m_Prev=newNode;
    }
    if(!prev)
    {
        s->m_first = newNode;
    }
    else
    {
        prev->m_Next=newNode;
    }
    newNode->m_Next=cur;
    newNode->m_Prev=prev;
    return true;
}

void removeItem(S* s,TITEM * item)
{
    if(!item->m_Prev)
    {
        s->m_first = item->m_Next;
    }
    else
    {
        item->m_Prev->m_Next=item->m_Next;
    }
    if(!item->m_Next)
    {
        s->m_last = item->m_Prev;
    }
    else
    {
        item->m_Next->m_Prev=item->m_Prev;
    }
    // free(item->m_text);
    // free(item);

}

bool  insertItem(S *s , TITEM *item, TITEM *next)
{    //next : next pointer 
    //next->m_Prev : prev poiner
    item->m_Next=next;//1) update the poiters of the item you are inserating
    //2) update pointers of item which will point the item you inset
    if(!next)
    {
        item->m_Prev=s->m_last;
        s->m_last->m_Next=item;
        s->m_last=item;
    }
    else
    {
        item->m_Prev=next->m_Prev;
        next->m_Prev->m_Next=item;
        next->m_Prev=item;
    }
    
    return false;
}
bool move_n_element(S*s, const char *text, int n)
{
    TITEM * curf=s->m_first;
    while(cur && strcmp(text, cur->m_text)!=0)
    {
        cur=cur->m_Next;
    }
    if(!cur)
    {
        return false;
    }
    //found 
    TITEM *next = cur->m_Next;
    for(int i = 0;i<n;i++)//------------------?-------------
    {
        if(!next)
        {
            return false;
        }
        next=next->m_Next;
    }
    removeItem(s, cur);
    insertItem(s, cur, next);
    return true;
}

int main()
{
    S s={0};
    insertITEM(&s, "1");
    insertITEM(&s, "3");
    insertITEM(&s, "2");
    insertITEM(&s, "6");
    insertITEM(&s, "4");
    //duplicate
    insertITEM(&s, "1");
    //print from the head
    TITEM * cur = s.m_first;
    while(cur)
    {
        printf("%s->", cur->m_text);
        cur=cur->m_Next;
    }
    printf("NULL\n");
    // print from the tail
    move_n_element(&s, "2", 3);
    cur = s.m_last;
    while(cur)
    {
        printf("%s->", cur->m_text);
        cur=cls
        ur->m_Prev;
    }
    printf("NULL\n");

    deleteList(s.m_first);
    return 0;
}