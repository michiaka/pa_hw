#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Tverse{

    char m_Str[128] ;
    struct Tverse * m_Next ;
}TVERSE;


void freeList(TVERSE * stSrc) {

    TVERSE * p = stSrc ;

    while(p)
    {
        TVERSE * pTmp = p->m_Next ;
        free(p) ;
        p = pTmp ;
    }
}



TVERSE * createVerse(const char str[128], TVERSE * next) {

    TVERSE * newVerse = (TVERSE *)malloc(sizeof(TVERSE)) ;
    strcpy(newVerse->m_Str, str);
    newVerse->m_Next = next;

    return newVerse ;
}


/* your auxiliary functions: */


typedef struct 
{
    size_t capa;
    size_t len;
   // char * data[256];
    char 
}DB_STRs;

typedef struct
{
    size_t capa;
    size_t len;
    int *data;
}Group;

typedef struct
{
    size_t capa;
    size_t len; 
    Group* data;
}Groups;


void printDB_STRs(DB_STRs arr)
{
    for(size_t i=0;i<arr.len;i++)
    {
        printf("[%zu]:%s\n", i, arr.data[i]);
    }
}

void printGroups(Groups arr)
{
    for(size_t i=0;i<arr.len;i++)
    {
        printf("group[%zu]---------------------\n",i);
        for(size_t k=0;k<arr.data[i].len;k++)
        {
            printf("[%d] ", arr.data[i].data[k]);
        }
    }
}

void resizeGroup(Group * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(int *) realloc(arr->data, sizeof(int)*arr->capa);
    }
}
void resizeGroups(Groups * arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Group *) realloc(arr->data, sizeof(Group)*arr->capa);
        for(size_t i=arr->len;i<arr->capa;i++)
        {
            arr->data[i]={0};
            resizeGroup(&arr->data[i]);            
        }   
    }
}

void desGroups(Groups *arr)
{
    for(size_t i=0;i<arr->capa;i++)
    {
        free(arr->data[i].data);
    }
    free(arr->data);
}

void resizeDBSTR(DB_STRs *arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(char *) realloc(arr->data, sizeof(char *)*arr->capa);
    }
}

char * duplicate_str(char *str)
{
    char res[256];
    size_t l = strlen(str);
    size_t i;
    for(i=0;i<l;i++)
    {
        res[i]=str[i];
    }
    for(i=i;i<l*2;i++)
    {
        res[i]=str[i-l];
    }
    str[l*2]='0';
}

TVERSE * Tverse(TVERSE * src) {

    /* to do */ 
    TVERSE *cur_VERSE = src;
    DB_STRs dup_strs={0};
    //while iterating make the array of duplicated string 
    while(cur_VERSE)
    {
        char str[128];
        strcpy(str, cur_VERSE->m_Str);
        resizeDBSTR(&dup_strs);
        char* dup=duplicate_str(str);
        printf("dup :%s\n", dup); 
        strcpy(dup_strs.data[dup_strs.len++], duplicate_str(str));
        cur_VERSE=cur_VERSE->m_Next;
    }
    
    printDB_STRs(dup_strs);
    free(dup_strs.data);

}






int main() {




    TVERSE * x = NULL;
    TVERSE * y = NULL ;

    x = createVerse("el PinesMab", x) ;
    x = createVerse("Stanley Pines", x) ;
    x = createVerse("abel PinesM", x) ;
    x = createVerse("Stanford Pines", x) ;
    x = createVerse("ley PinesStan", x) ;
    x = createVerse("Mabel Pines", x) ;
    x = createVerse("Dipper Pines", x) ; //keep in mind that this is the head now.

    y = Tverse(x) ;

    assert(strcmp (y->m_Str, "Mabel Pines") == 0) ;
    assert(strcmp (y->m_Next->m_Str, "abel PinesM") == 0) ;
    assert(strcmp (y->m_Next->m_Next->m_Str, "el PinesMab") == 0) ;
    

    freeList(x) ;
    freeList(y) ;

    /* you can add your cases here */


    return EXIT_SUCCESS;
}

