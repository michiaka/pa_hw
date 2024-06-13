#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct
{
    bool occupied;
    char id[11];
}Space;

void skipwhite(char **buf)
{
    while(isspace(**buf))
    {
        (*buf)++;
    }
}

bool isvalidId(char *id)
{
    int l=strlen(id);
    for(int i =0; i< l; i++)
    {
        if(!((id[i] >= 'A' && id[i] <='Z') || (id[i] >= '1' && id[i] <= '9')))
            return false;
    }
    return true;
}
int indexconverter(int floor, int slot, int num_slots)
{
    int index=(floor*num_slots)+slot;
    return index;

}
bool isvalidspace(int floor, int slot, int num_floor, int num_slots)
{
    int max_floor=num_floor-1;
    int max_slot=num_slots-1;
    if(max_floor < floor || max_slot < slot)
    {
        return false;
    }
    return true;
}

void searchId(Space *arr, char*id, int num_spaces)
{
    for(int i=0; i<num_spaces;i++)  
    {
        if(strcmp(arr[i].id, id) ==0 || arr[i].occupied)
        {

            arr[i].occupied=false;
            printf("OK\n");
            return;
        }
    }
    printf("Not found.\n");
    return;
}
bool readLine(char *line, Space *spaces, int num_floor, int num_slots, int num_spaces)
{
    skipwhite(&line);
    if(line[0]!='+' && line[0]!='-')          
    {
        printf("here");
        return false;
    }
    //store
    if(line[0]=='+')
    {
        int floor=0,slot=0;char id[11]; char extra=0;
        if(sscanf(line, "+ %d %d %10s %c", &floor, &slot, id, &extra) !=3)
        {
            return false;
        }
        if(!isvalidspace(floor, slot, num_floor, num_slots))
        {
            return false;
        }
        if(!isvalidId(id))
        {
            printf("here");

            return false;
        }
        int index=indexconverter(floor, slot, num_slots);
        printf("%d\n", index);
        if(spaces[index].occupied)
        {
            printf("Ocuupied.\n");
            return true;
        }
        strcpy(spaces[index].id, id);
        spaces[index].occupied = true;
        printf("OK\n");

    }
    else
    {
        char id[11];char extra=0;
        if(sscanf(line,"- %10s %c",id, &extra)!=1)
        {
            return false;
        }
        if(!isvalidId(id))
        {
            return false;
        }
        searchId(spaces, id, num_spaces);
        return true;
    }

    return true;
}
int main()
{
    char *line=nullptr;
    size_t capa;
    ssize_t len;

    printf("Size:\n");
    getline(&line, &capa, stdin);
    int num_floor=0, num_slots =0;char extra=0;
    if(sscanf(line, "%d%d %c", &num_floor, &num_slots, &extra)!=2)
    {
        printf("Invalid input.\n");
        free(line);
        return -1;
    }

    int num_spaces=num_slots*num_floor;
    printf("%d\n", num_spaces);
    Space * spaces=(Space *)malloc(sizeof(Space)*num_spaces);
    for(int i=0;i<num_spaces;i++)
    {
        spaces[i]={0};
    }
    printf("Requirement:\n");
    while((len=getline(&line, &capa, stdin))!=EOF)
    {
        char *str=line;
        if(len<1 || !readLine(str,spaces,num_floor, num_slots, num_spaces))
        {
            printf("Invalid input.\n");
            free(line);
            free(spaces);
            return -1;
        }
    }
    
    free(line);
    free(spaces);
    return 0;
}