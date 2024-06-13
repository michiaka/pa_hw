#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <assert.h> 
#include <ctype.h>

/*input validation of the linked list */
typedef  struct Titem { 
  struct Titem * m_Next ; 
  char m_Digit ; 
} TITEM ;
 
TITEM * createItem (char i, TITEM * next){ 
  TITEM * l =  (TITEM *)malloc(sizeof ( * l )  ) ;  
  l -> m_Digit = i; 
  l -> m_Next = next; 
  return l ; 
} 

TITEM * createList( const char * x){ 
    int i = 0; 
    TITEM * item = NULL; 
    while ( x [ i ] ){ 
     item = createItem ( x [ i ] , item ) ; 
     i ++; 
    } 
    return item ; 
} 

void delList ( TITEM * l )  { 
  while  ( l )  { 
      TITEM* tmp = l -> m_Next ;
      free  ( l ) ; 
      l = tmp ; 
  } 
} 

int printList (const TITEM * l) {

    const TITEM * temp1 = l;
    const TITEM * bfrtail;
    int count = 0;
    //checks if it is the digit
    while ( l != NULL ) {
        if ( !isdigit( l->m_Digit ) ) {
            return 1;  
        }

        bfrtail = l;
        l = l->m_Next;
        count++;

    }

    //checks if the element with null pointer (last) will have 1 as size

    char lastvalue = bfrtail->m_Digit;
    // printf(" This is the last value in the linked list : %c \n", lastvalue );

    if ( lastvalue == '0' ) {
        if( count > 1){
            printf("with 001\n");
            return 1;
        }
    }

    l = temp1;
    
    while (l != NULL ) {

        printf( "%c\n", l->m_Digit );
        l = l -> m_Next;
    }
     
    // printf( " %d", count);

    return 0;
  
}


int main (  void  )  {
 

 
    //----- Basic test ------------------------------------------ ----- 
 

    printList(createList("199"));
    printList(createList("1z2"));
    printList(createList("001"));
    printList(createList("010"));
    printList(createList("0"));

    
    return 1;

    
}