#ifndef __PROGTEST__ 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>
 
typedef  struct TItem
 { 
    struct TItem * m_Next ; 
    int m_Mul ; 
    int m_Pow ; 
} TITEM ;
 
TITEM * createItem (  int mul ,  int  pow , TITEM * next ) 
{ 
    TITEM * n =  ( TITEM * )  malloc  ( sizeof  (  * n ) ) ; 
    n -> m_Mul = mul ; 
    n -> m_Pow =  pow ; 
    n -> m_Next = next ; 
    return n ; 
}
 
void deleteList ( TITEM * l ) 
{ 
    while  ( l ) 
    { 
        TITEM * tmp = l -> m_Next ; 
        free  ( l ) ; 
        l = tmp ; 
    } 
} 
#endif /* __PROGTEST__ */


 
TITEM * addPoly ( TITEM * a , TITEM * b ) 
{ 
    TITEM * res = NULL;
    TITEM ** lastPtr = &res;

    TITEM * cur_a = a; TITEM * cur_b = b;
    TITEM * prev_a = NULL, *prev_b = NULL;
    if(!cur_a  || !cur_b)
    {
        deleteList(res);
        return NULL;
    }
    while(cur_a && cur_b)
    {
        //powers in ascending order
        if(prev_a && prev_b)
        {
            if(cur_a->m_Pow <= prev_a->m_Pow || cur_b->m_Pow <= prev_b->m_Pow)
            {   
                deleteList(res);       
                return NULL;
            }
        }

        if(cur_a->m_Pow == cur_b->m_Pow)
        {
            if(cur_a->m_Mul + cur_b->m_Mul == 0)
            {
                prev_a = cur_a;
                prev_b = cur_b;
                cur_a = cur_a->m_Next;
                cur_b = cur_b->m_Next;
                continue;
            }
            *lastPtr = createItem(cur_a->m_Mul + cur_b->m_Mul, cur_a->m_Pow, NULL);
            prev_a = cur_a;
            prev_b = cur_b;
            cur_a = cur_a->m_Next;
            cur_b = cur_b->m_Next;
        }
        else if(cur_a->m_Pow > cur_b->m_Pow)
        {
            if(cur_b->m_Mul == 0)
            {
                prev_b = cur_b;
                cur_b = cur_b->m_Next;            
                continue;    
            }
            *lastPtr = createItem(cur_b->m_Mul, cur_b->m_Pow, NULL);
            prev_b = cur_b;
            cur_b = cur_b->m_Next;
        }
        else
        {
            if(cur_a->m_Mul == 0)
            {
                prev_a = cur_a;
                cur_a = cur_a->m_Next;
                continue;
            }
            *lastPtr = createItem(cur_a->m_Mul, cur_a->m_Pow, NULL);
            prev_a = cur_a;
            cur_a = cur_a->m_Next;
        }
        lastPtr = &(*lastPtr)->m_Next;
    }

//either one of them are not null/ both of them are null

    while(cur_a)
    {        
        if(prev_a)
        {
            if(cur_a->m_Pow <= prev_a->m_Pow)
            {
                deleteList(res);
                return NULL;
            }
        }
        *lastPtr = createItem(cur_a->m_Mul, cur_a->m_Pow, NULL);
        lastPtr = &(*lastPtr)->m_Next;
        prev_a = cur_a;
        cur_a = cur_a->m_Next;
    }

    while(cur_b)
    {
        if(prev_a && prev_b)
        {
            if(cur_b->m_Pow <= prev_b->m_Pow)
            {
                printf("get out hrere\n");
                deleteList(res);
                return NULL;
            }
        }
        *lastPtr = createItem(cur_b->m_Mul, cur_b->m_Pow, NULL);
        lastPtr = &(*lastPtr)->m_Next;
        prev_b = cur_b;
        cur_b = cur_b->m_Next;
    }

    //getting out of the loop <=> valid 2 linked list

    //the way im changing is the wrong
    if(!res)
    {   
        *lastPtr = createItem(0, 0, NULL);
    }

    return res;
}

void printList(TITEM * l)
{
    if(!l)
        printf("nullllllllllllllllll\n");
    
    while(l)
    {
        printf("m_Mul %d, m_Pow %d\n", l->m_Mul, l->m_Pow);
        l = l->m_Next;
    }
}
 
#ifndef __PROGTEST__ 
int main (  int argc ,  char  * argv [ ]  ) 
{ 
    TITEM * a ,  * b ; 
    TITEM * res ;
 
    a = createItem ( 2 , 1 , NULL ) ;
    b = createItem ( 0 , 0 , NULL ) ; 
    res = addPoly ( a , b ) ; 
    if(!res)
    {
        printf("NULL----------------------\n");   
    }
    assert  ( res -> m_Mul ==  2  ) ; 
    assert  ( res -> m_Pow ==  1  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    printList(res);
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
    

    printf("---------------------------------------------------\n");
 
    a = createItem ( 2 , 1 , NULL ) ; 
    b = createItem ( 3 , 1 , createItem ( 4 , 2 , createItem ( 2 , 3 , createItem ( 1 , 0 , NULL ) ) )) ;
    res = addPoly ( a , b ) ; 
    printList(res);
    assert  ( res == NULL ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    a = createItem ( 2 , 1 , NULL ) ; 
    b = createItem ( 3 , 1 , createItem ( 4 , 1 , NULL ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res == NULL ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    // a = createItem ( 3 , 0 , createItem ( 2 , 1 , createItem ( 9 , 3 , NULL ) ) ) ; 
    // b = createItem ( 0 , 0 , createItem ( 4 , 2 , createItem ( - 1 , 3 , NULL ) ) ) ; 
    // res = addPoly ( a , b ) ; 
    // if(!res)
    // {
    //     printf("res is nullll--------------\n");
    // }
    // assert  ( res == NULL ) ; 
    // deleteList ( a ) ; 
    // deleteList ( b ) ; 
    // deleteList ( res ) ;
 
    a = createItem ( 3 , 0 , createItem ( 2 , 1 , createItem ( 5 , 3 , NULL ) ) ) ; 
    b = createItem ( - 7 , 0 , createItem ( - 2 , 1 , createItem ( - 5 , 3 , NULL ) ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res -> m_Mul ==  - 4  ) ; 
    assert  ( res -> m_Pow ==  0  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    a = createItem ( 3 , 1 , createItem ( - 2 , 2 , createItem ( 4 , 3 , NULL ) ) ) ; 
    b = createItem ( - 3 , 1 , createItem ( 2 , 2 , createItem ( - 4 , 3 , NULL ) ) ) ; 
    res = addPoly ( a , b ) ; 
    assert  ( res -> m_Mul ==  0  ) ; 
    assert  ( res -> m_Pow ==  0  ) ; 
    assert  ( res -> m_Next == NULL ) ; 
    deleteList ( a ) ; 
    deleteList ( b ) ; 
    deleteList ( res ) ;
 
    return  0 ; 
} 
#endif /* __PROGTEST__ */