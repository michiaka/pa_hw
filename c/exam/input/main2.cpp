#include<stdio.h>//1236
#include<stdlib.h>
#include<ctype.h>

typedef struct
{
    size_t capa;
    size_t len;
    int *data;
}Element;

void skipwhite(char **line)
{
    while(isspace(**line))
    {
        (*line) ++;
    }
}
int main()
{
    Element element[3];

    char *line =nullptr;
    size_t capa;
    ssize_t len;
    while((len =getline(&line, &capa, stdin))!=EOF)
    {
        char *str =line;
        skipwhite(&str);
        while(scanf("%d"), )
    
        
        
    }

    free(line);

    return 0;
}