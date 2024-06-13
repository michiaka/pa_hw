#include <stdio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
 
#define MAX_SIZE 4096 
#define WRONG_INPUT 1 
#define CORRECT_INPUT 0
 
typedef  struct  { 
    int teeth ; 
    char company [ MAX_SIZE +  1 ] ; 
} gear_t ;
 
typedef  struct  { 
    gear_t * gear ; 
    size_t size ; 
    size_t maxSize ; 
} gearArr_t ;
 
typedef  struct  { 
    int first ; 
    int second ; 
    char company [ MAX_SIZE +  1 ] ; 
} ratio_t ;
 
typedef  struct  { 
    ratio_t * gear ; 
    size_t size ; 
    size_t maxSize ; 
} ratioArr_t ;
 
void resizeGear ( gearArr_t * shop )  { 
    if  ( shop -> size >= shop -> maxSize )  { 
        shop -> maxSize = shop -> maxSize *  2  +  1 ; 
        shop -> gear =  ( gear_t * )  realloc ( shop -> gear , shop -> maxSize *  sizeof ( gear_t ) ) ; 
    } 
}
 
void resizeRatio ( ratioArr_t * ratio )  { 
    if  ( ratio -> size >= ratio -> maxSize )  { 
        ratio -> maxSize = ratio -> maxSize *  2  +  1 ; 
        ratio -> gear =  ( ratio_t * )  realloc ( ratio -> gear , ratio -> maxSize *  sizeof ( ratio_t ) ) ; 
    } 
}
 
int readGear ( gearArr_t * shop )  { 
    resizeGear ( shop ) ; 
    int value =  scanf ( "%d %4069s" ,  & shop -> gear [ shop -> size ] . teeth , shop -> gear [ shop -> size ] . company ) ;
 
    if  ( value !=  2  || shop -> gear [ shop -> size ] . teeth  <=  0 ) 
        return WRONG_INPUT ;
 
    shop -> size ++; 
    return CORRECT_INPUT ; 
}
 
int findGcd ( int first ,  int second )  { 
    int highest = first > second ? first : second ; 
    int gcd ; 
    for  ( int i =  1 ; i <= highest ; i ++ )  { 
        if  ( first % i ==  0  && second % i ==  0 ) 
            gcd = i ; 
    } 
    return gcd ; 
}
 
void printOutput ( ratioArr_t * ratio ,  size_t i )  { 
    int gcd = findGcd ( ratio -> gear [ i ] . first , ratio -> gear [ i ] . second ) ; 
    printf ( "%d:%d \n " , ratio -> gear [ i ] . first / gcd , ratio -> gear [ i ] . second / gcd ) ; 
    printf ( "* %s: %d:%d \n " , ratio -> gear [ i ] . company , ratio -> gear [ i ] . first , ratio -> gear [ i ] . second ) ; 
}
 
void findGear ( gearArr_t * shop , ratioArr_t * ratio , ratio_t * find ,  int cnt )  { 
    size_t i ; 
    bool match =  false ; 
    for  ( i =  0 ; i < ratio -> size ; i ++ )  { 
        if  ( 1.0 * ratio -> gear [ i ] . first / ratio -> gear [ i ] . second  ==  1.0 * find -> first / find -> second )  { 
            match =  true ; 
            breaks _  // find first match 
        } 
        else  if  ( 1.0 * ratio -> gear [ i ] . first / ratio -> gear [ i ] . second  >  1.0 * find -> first / find -> second )  {  // first with higher ratio 
            breaks _ 
        } 
    } 
    // are the same 
    if  ( match )  { 
        printf ( "Exactly: \n " ) ; 
        int gcd = findGcd ( ratio -> gear [ i ] . first , ratio -> gear [ i ] . second ) ; 
        printf ( "%d:%d \n " , ratio -> gear [ i ] . first / gcd , ratio -> gear [ i ] . second / gcd ); 
        for  ( size_t k = i ; k < ratio -> size ; k ++ )  { 
            if  ( 1.0 * ratio -> gear [ k ] . first / ratio -> gear [ k ] . second  !=  1.0 * find -> first / find -> second ) 
                break ; 
            printf ( "* %s: %d:%d \n " , ratio -> gear [ k ] . company , ratio -> gear [ k ] . first , ratio -> gear [ k ] . second ) ; 
        } 
    } 
    if  ( ! match )  {  // 
        if  ( i >=  1 )  {  // lower exists 
            printf ( "Lesser ratio: \n " ) ; 
            printOutput ( ratio , i -  1 ) ; 
        } 
        if  ( i < ratio -> size )  {  // higher exists 
            printf ( "Vetsi ratio: \n " ) ; 
            printOutput ( ratio , i ) ;
 
        } 
    } 
}
 
int readRequest ( gearArr_t * shop , ratioArr_t * ratio )  { 
    ratio_t find ; 
    int cnt ; 
    int value =  scanf ( " %d:%d, %d" ,  & find. first ,  & find. second ,  & cnt ) ;
 
    if  ( value !=  3  || find. first  <=  0  || find. second  <=  0  || cnt <=  0 ) 
        return WRONG_INPUT ; 
    findGear ( shop , ratio ,  & find , cnt ) ; 
    return CORRECT_INPUT ; 
}
 
int cmp ( const  void  * a ,  const  void  * b )  { 
    ratio_t * p1 =  ( ratio_t * ) a ; 
    ratio_t * p2 =  ( ratio_t * ) b ; 
    if ( 1.0 * p1 -> first / p1 -> second <  1.0 * p2 -> first / p2 -> second ) 
        return  - 1 ; 
    if  ( 1.0 * p1 -> first / p1 -> second >  1.0 * p2 -> first / p2 -> second ) 
        return  1 ; 
    return  0 ; 
}
 
void makeAllCombinations ( gearArr_t * shop , ratioArr_t * ratio )  { 
    for  ( size_t i =  0 ; i < shop -> size ; i ++ )  { 
        for  ( size_t j =  0 ; j < shop -> size ; j ++ )  { 
            if  ( strcmp ( shop -> gear [ i ] . company , shop -> gear [ j ] . company )  !=  0 ) 
                continue ; 
            resizeRatio ( ratio ) ;
 
            ratio -> gear [ ratio -> size ] . first  = shop -> gear [ i ] . teeth _ 
            ratio -> gear [ ratio -> size ] . second  = shop -> gear [ j ] . teeth _ 
            strcpy ( ratio -> gear [ ratio -> size ] . company , shop -> gear [ i ] . company ) ; 
            ratio -> size ++; 
        } 
    } 
    qsort ( ratio -> gear , ratio -> size ,  sizeof ( ratio_t ) , cmp ) ; 
}
 
int readInput ( gearArr_t * shop , ratioArr_t * ratio )  { 
    char sign ; 
    bool newInput =  true ;
 
    printf ( "Gears: \n " ) ; 
    while  ( 69 )  { 
        int value =  scanf ( " %c" ,  & sign ) ; 
        if  ( value == EOF ) 
            return EOF ; 
        if  ( value !=  1 ) 
            return WRONG_INPUT ; 
        if  ( sign ==  '+'  && newInput )  { 
            if  ( readGear ( shop )  == WRONG_INPUT ) 
                return WRONG_INPUT ; 
        } 
        else  if  ( sign ==  '?' )  { 
            if  ( newInput )  { 
                newInput =  false ; 
                makeAllCombinations ( shop , ratio ) ; 
            } 
            if  ( readRequest ( shop , ratio )  == WRONG_INPUT ) 
                return WRONG_INPUT ; 
        } 
    } 
}
 
int main ( )  { 
    gearArr_t shop =  { } ; 
    ratioArr_t ratio =  { } ; 
    if  ( readInput ( & shop ,  & ratio )  == WRONG_INPUT )  { 
        printf ( "Wrong input. \n " ) ; 
        free ( shop. gear ) ; 
        free ( ratio. gear ) ; 
        return  0 ; 
    }
 
    free ( shop. gear ) ; 
    free ( ratio. gear ) ; 
    return  0 ; 
}