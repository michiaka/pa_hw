#ifndef __PROGTEST__ 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>
 
typedef  struct Titem { 
  struct Titem * m_Next ; 
  char m_Digit ; 
} TITEM ;
 
TITEM * createItem (  char i , TITEM * next )  { 
  TITEM * l =  ( TITEM * )  malloc  (  sizeof ( * l )  ) ;  
  l -> m_Digit = i ; 
  l -> m_Next = next ; 
  return l ; 
} 

TITEM * createList ( const  char  * x )  { 
    int i =  0 ; 


    TITEM * item = NULL ; 
    while ( x [ i ] )  { 
     item = createItem ( x [ i ] , item ) ; 
     i ++; 
    } 
    return item ; 
} 

void delList ( TITEM * l )  { 
  while  ( l )  { 
      TITEM * tmp = l -> m_Next ; 
      free  ( l ) ; 
      l = tmp ; 
  } 
} 
#endif /* __PROGTEST__ */
 
void printList(TITEM * l)
{
    TITEM *tmp = l;
    int i = 0;
    while(tmp)
    {
        printf("digit %d:  %c\n", i, tmp->m_Digit);
        tmp = tmp->m_Next;
        i++;
    }
    
}

bool isDigit(char ch)
{
    return(ch >= '0' && ch <= '9');
}

// typedef struct 
// {
//     size_t capa;
//     size_t len;
//     char ** data;
// } AllItem;

typedef struct 
{
    size_t capa;
    size_t len;
    char * data;
}Item;

void resizeItem(Item * item)
{
    if(item->capa == item->len)
    {
        item->capa = item->capa * 2 + 10;
        item->data = (char *)realloc(item->data, sizeof(char)* item->capa);
    }
}

void reverse_arr(Item * arr)
{
    size_t l = 0, h = arr->len -1;
    while(l < h)
    {
        char tmp  = arr->data[h];
        arr->data[h] = arr->data[l];
        arr->data[l] = tmp;
        l ++;
        h --;
    }
}
//thisssssssssssssssss
size_t min(size_t a, size_t b)
{
    size_t res = 0;
    res = (a > b) ? b : a;
    return res;
}

TITEM * maxOf ( TITEM ** x ,  int nr )  { 
   /*To Do*/    
    printf("another one-----------------------\n");
    TITEM * maxItem = {0};
    Item max_item = {0};
    for(int i = nr-1; i >= 0; i--)
    {
        TITEM * curItem = x[i];
        if(!curItem)
            return NULL;
        Item cur_item = {0};
        while(curItem)
        {

            char ch = curItem->m_Digit;
            printf("digit of the curr %c\n", ch);
            if(!isDigit(ch))
            {
                return NULL;
            }
            
            resizeItem(&cur_item);
            cur_item.data[cur_item.len ++] = ch;
            curItem = curItem->m_Next;
        }
        //reverse the array
        reverse_arr(&cur_item);
        print
        //thissssssssssssssssssssss
        resizeItem(&cur_item);
        cur_item.data[cur_item.len++] = '\0';
        int res = strncmp(cur_item.data, max_item.data, min(max_item.len, cur_item.len));
        if(res > 0)
        {
            for(size_t i = 0; i < cur_item.len ; i++)
            {
                resizeItem(&max_item);
                max_item.data[max_item.len ++] = cur_item.data[i]; 
            }
            maxItem = x[i];
        }
        
        free(cur_item.data);
        cur_item.data = nullptr;
    }
    free(max_item.data);
    max_item.data = nullptr;
    printList(maxItem);
    return maxItem;

    
}
 
#ifndef __PROGTEST__ 
int main (  void  )  {
 
    TITEM * a [ 5 ] ; 
    TITEM * res ;
 
    //----- Basic test ------------------------------------------ ----- 
    a [ 0 ]  = createList ( "191" ) ; 
    a [ 1 ]  = createList ( "113" ) ; 
    a [ 2 ]  = createList ( "197" ) ; 
    res = maxOf ( a ,  3 ) ;
 
    assert ( res == a [ 2 ] ) ;
 
    for ( int i =  0 ; i <  3 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Ordinal higher number ---------------------------------------- - 
    printf("this-------------------------\n");
    a [ 0 ]  = createList ( "313" ) ; 
    a [ 1 ]  = createList ( "1191" ) ; 
    a [ 2 ]  = createList ( "997" ) ; 
    res = maxOf ( a ,  3 ) ;
 
    assert ( res == a [ 1 ] ) ;
 
    for ( int i =  0 ; i <  3 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Bad input ------------------------------------------ ------ 
    a [ 0 ]  = createList ( "222" ) ; 
    a [ 1 ]  = NULL ; 
    a [ 2 ]  = createList ( "4333" ) ; 
    a [ 3 ]  = createList ( "1" ) ; 
    res = maxOf ( a ,  4 ) ;
 
    assert ( res == NULL ) ;
 
    for ( int i =  0 ; i <  4 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Bad value ----------------------------------------- ---- 
    a [ 0 ]  = createList ( "29a" ) ; 
    a [ 1 ]  = createList ( "11" ) ; 
    res = maxOf ( a ,  2 ) ;
 
    assert ( res == NULL ) ;
 
    for ( int i =  0 ; i <  2 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Same number ----------------------------------------- ------ 
    a [ 0 ]  = createList ( "27986" ) ; 
    a [ 1 ]  = createList ( "3256" ) ; 
    a [ 2 ]  = createList ( "27986" ) ; 
    a [ 3 ]  = createList ( "17000" ) ; 
    res = maxOf ( a ,  4 ) ;
 
    assert ( res == a [ 0 ] ) ;
 
    for ( int i =  0 ; i <  4 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Zero ---------------------------------------------------- ------------- 
    a [ 0 ]  = createList ( "0" ) ; 
    a [ 1 ]  = createList ( "0" ) ; 
    a [ 2 ]  = createList ( "0" ) ; 
    a [ 3 ]  = createList ( "0" ) ; 
    a [ 4 ]  = createList ( "0" ) ; 
    res = maxOf ( a ,  5 ) ;
 
    assert ( res == a [ 0 ] ) ;
 
    for ( int i =  0 ; i <  5 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Unsigned Long Long Int ------------------------------------ 
    a [ 0 ]  = createList ( "0" ) ; 
    a [ 1 ]  = createList ( "18446744073709551615" ) ; 
    a [ 2 ]  = createList ( "1112367822345622" ) ; 
    a [ 3 ]  = createList ( "9991234530632948235" ) ; 
    a [ 4 ]  = createList ( "1213004921032" ) ; 
    res = maxOf ( a ,  5 ) ;
 
    assert ( res == a [ 1 ] ) ;
 
    for ( int i =  0 ; i <  5 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- More like Unsigned Long Long Int ---------------------------- 
    a [ 0 ]  = createList ( "50230529401950984100481491404914091408580" ) ; 
    a [ 1 ]  = createList ( "50230529401950123123123234492492042044242" ) ; 
    a [ 2 ]  = createList ( "50230529401950984100480123032931110119944" ) ; 
    a [ 3 ]  = createList ( "50230529401950123123123234492400000000000" ) ; 
    a [ 4 ]  = createList ( "50230531000000000000000000000000000000000" ) ; 
    res = maxOf ( a ,  5 ) ;
 
    assert ( res == a [ 4 ] ) ;
 
    for ( int i =  0 ; i <  5 ; i ++ ) delList ( a [ i ] ) ;
 
    //----- Greater than Unsigned Long Long Int different long -------------- 
    a [ 0 ]  = createList ( "253051330239013091349049023023" ) ; 
    a [ 1 ]  = createList ( "253051330239013091349049023024" ) ; 
    a [ 2 ]  = createList ( "2094241212100000000000100100" ) ; 
    a [ 3 ]  = createList ( "999919103904248923023" ) ; 
    a [ 4 ]  = createList ( "9999999999999999999999999999" ) ; 
    res = maxOf ( a ,  5 ) ;
 
    assert ( res == a [ 1 ] ) ;
 
    for ( int i =  0 ; i <  5 ; i ++ ) delList ( a [ i ] ) ; 
    return  0 ; 
} 
#endif /* __PROGTEST__ */