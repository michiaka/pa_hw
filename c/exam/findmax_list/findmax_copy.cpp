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

typedef struct
{
    size_t capa;
    size_t len;
    char *data;
}Item;

void resizeItem(Item * item)
{
    if(item->capa == item->len)
    {
        item->capa = item->capa * 2 + 10;
        item->data = (char *)realloc(item->data, sizeof(char)* item->capa);
    }
}

bool isValidlist(TITEM *l)
{
    TITEM *cur =l;
    if(!cur)
    {
        return NULL;
    }
    while(cur)
    {
        if(!isdigit(cur->m_Digit))
        {
            return false;
        }
        cur=cur->m_Next;
    }
    return true;
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
int dinamicmp(Item* str1, Item* str2)
{
    int l1=str1->len;
    int l2=str2->len;
    if(l1>l2)
    {
        return 1;
    }
    if(l1<l2)
    {
        return -1;
    }
    return strcmp(str1->data, str2->data);
}

void dynamicpy(Item  *desti, Item *source)
{
    free(desti->data);
    desti->data=(char *) malloc(sizeof(char)*source->len+1);
    desti->len=source->len;
    strcpy(desti->data, source->data);
}
void printItem(Item arr)
{
    for(size_t i=0;i<arr.len;i++)
    {
        printf("%c", arr.data[i]);
    }
    printf("\n");
}
TITEM * maxOf ( TITEM ** x ,  int nr )  
{
    for(int i=0;i<nr;i++)
    {
        TITEM *cur=x[i];
        if(!isValidlist(cur))
        {
            return NULL;
        }
    }
    TITEM *max_ITEM={0};
    Item max_item={0};
    for(int i = 0;i<nr;i++)
    {
        TITEM *cur=x[i];
        Item cur_item={0};
        while(cur)  
        {
            resizeItem(&cur_item);
            cur_item.data[cur_item.len++]=cur->m_Digit;
            cur=cur->m_Next;
        }
        resizeItem(&cur_item);
        cur_item.data[cur_item.len]='\0';
        reverse_arr(&cur_item);
        if(cur_item.data[0]=='0' && cur_item.data[1]=='0')
        {
            free(cur_item.data);
            free(max_item.data);
            return NULL;
        }
        // printItem(cur_item);
        if(dinamicmp(&cur_item, &max_item) >0)
        {
            printf("%s", cur_item.data);
            dynamicpy(&max_item, &cur_item);
            max_ITEM = x[i];
        }
        free(cur_item.data);
    }


    free(max_item.data);

    return max_ITEM;

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
 
    assert ( res == a [  0] ) ;
 
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