#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

typedef struct
{
    size_t capa;
    size_t len;
    char *data;
}Word;

void resizeWord(Word *arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(char *)realloc(arr->data, sizeof(char)*arr->capa);
    }
}

bool isValidrange(int min, int max, int word_len)
{
    if(min > max)
        return false;
    if(max > word_len)
        return false;
    if(min < 0)
        return false;
    else
        return true;
}

void printinput(Word word, int min, int max)
{
    for(size_t i=0; i<word.len;i++)
    {
        printf("%c", word.data[i]);
    }
    printf("\n");
    printf("min%d, max%d\n", min, max);
}

void skipwhite(char ** buf)
{
    while(isspace(**buf))
    {
        (*buf)++;
    }
}

void all_combination(Word word, int min_words, int max_words)
{
    int n=word.len-1;
    // int num_combination=1<<n;
    int min_space=min_words-1;
    int start=0;
    //counter the number of the combinatino until min
    for(int i=0;i<min_space;i++)//min_space being 1
    {
        int n_fac=tgamma(n+1);
        int i_fac=tgamma(i+1);
        int n_i = n-i;
        int n_i_fac=tgamma(n_i+1);

        start+=n_fac/(i_fac*n_i_fac);
    }
    int max_space=max_words-1;
    int end=0;
    for(int i=0;i<=max_space;i++)//0,1,2
    {
        int n_fac=tgamma(n+1);//2
        int i_fac=tgamma(i+1);//1,1,2
        int n_i = n-i;//2,1,0
        int n_i_fac=tgamma(n_i+1);//2,1,1
        end+=n_fac/(i_fac*n_i_fac);
        printf("i_fac*n_i_fac: %d\n", i_fac*n_i_fac);
        printf("adding :%d\n", n_fac/(i_fac*n_i_fac));
        printf("end:%d\n", end);
    }
    
    printf("%d %d\n", start, end);
    for(int j=start;j<end-1;j++)//after 
    {
        
        for(int i=0;i<n;i++)
        {   
            printf("%c", word.data[i]);
            if((j>>i) & 1)
            printf(" ");
            
        }
        printf("%c\n", word.data[n]);
    }    

}
int main()
{
    int min=0, max=0;
    char *line=nullptr;
    size_t capa;
    ssize_t len;
    int count_line=0;
    bool readWord=true;
    Word word={0};
    printf("Input:\n");
    while((len=getline(&line,&capa,stdin))!=EOF)
    {
        if(count_line == 2)
        {
            printf("Invalid input.\n");
            free(word.data);
            free(line);
            return -1; 
        }
        char *str=line;
        if(readWord)
        {
            skipwhite(&str);
            if(!isalpha(str[0]))
            {
                printf("Invalid input.\n");
                free(word.data);
                free(line);
                return -1;
            }
            while(isalpha(*str))
            {
                resizeWord(&word);
                word.data[word.len++]=*str;
                readWord=false;
                str++;
            }
            skipwhite(&str);
            if(str[0]!='\0')//check if there is any extra character left(reading input by shifting the pointer)
            {
                printf("Invalid input.\n");
                free(word.data);
                free(line);
                return -1;
            }
            readWord = false;
            count_line++;
        }
        else
        {   //checking if there is 2 number and not extra
            char extra=0;
            if(sscanf(str, "%d%d %c",&min, &max, &extra) !=2)
            {
                printf("Invalid input.\n");
                free(word.data);
                free(line);
                return -1;                  
            }
            if(!isValidrange(min, max, word.len))
            {
                printf("Invalid input.\n");
                free(word.data);
                free(line);
                return -1;         
            }
            count_line++;
        }
    }

    // printinput(word, min, max);


    all_combination(word, min, max);

    free(line);
    free(word.data);
    word.data=nullptr;
    return 0;
}
