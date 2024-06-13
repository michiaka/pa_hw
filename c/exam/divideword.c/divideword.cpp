#include<stdio.h>
#include<stdlib.h>
#include<string.h>
bool allAlpha(char * arr)
{
    size_t len = strlen(arr);
    for(size_t i = 0; i<len; i++)
    {
        if((arr[i] < 'a' || arr[i] > 'z') && (arr[i] < 'A' || arr[i] > 'Z'))
        {
            printf("here");
            return false;
        }
    }
    return true;
}


void allCombination(char *word, size_t num_space, char * space_slot)
{
    size_t len = strlen(word);
    size_t num_combinations = 1 << num_space; // 2^num_space

    for(size_t i = 1; i < num_combinations; i++)
    {
        for(size_t j = 0; j < num_space; j++)
        {
            space_slot[j] = (i >> j) & 1;   
        }

        for(size_t k = 0; k < len; k++)
        {
            printf("%c", word[k]);   
            if(k < len - 1 && space_slot[k]) // Check if there should be a space after this character
            {
                printf(" ");
            }
        }
        printf("\n"); // Print a newline after each combination
    }
    printf("Total :  %zu\n", num_combinations -1);
}

int main()
{
    printf("Enter:\n");
    char * line = NULL;
    size_t capa =0;
    ssize_t len = 0;
    len = getline(&line, &capa, stdin);  
    if(len < 1 || len > 100)
    {
        printf("Invalid input.\n");
        free(line);
        return -1;
    }
    char word[101];
    sscanf(line, "%100s", word);
    if(!allAlpha(word))
    {
        printf("Invalid input.\n");
        free(line);
        return -1;
    }

    size_t num_char = strlen(word);
    size_t num_space = num_char - 1;
    char *space_slot = (char *)malloc(num_space);

    allCombination(word, num_space, space_slot);

    free(line);
    return 0;
}