#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
    int time;
    bool occupied;
    char id[11];
} SLOT;


typedef struct
{
    size_t capa;
    size_t len;
    SLOT * data;
}SLOT_Arr;

void indexconverter(size_t index,  size_t *floor, size_t * slot, size_t slot_num)
{
    *floor = index / slot_num;
    *slot = index % slot_num;
}

void findSlot(SLOT_Arr * slots, size_t * floor, size_t *slot, char * id, size_t slot_num)
{
    //longest time
    int max_time = slots->data[0].time;
    
    for(size_t i = 0; i < slots->capa; i++)
    {
        printf("time [%zu]: %d\n", i, slots->data[i].time);
        max_time = (slots->data[i].time > max_time) ? slots->data[i].time : max_time;
        
    }
    //earlier
    // printSLOT_Arr
    size_t i;
    for(i = 0; i < slots->capa; i++)
    {
        printf("time [%zu]: %d\n", i, slots->data[i].time);
        if(max_time == slots->data[i].time && !slots->data[i].occupied)
        {
            break;
        }
    }

    //store the info
    for(int j = 0; j < 11;  j++)
    {
        slots->data[i].id[j] = id[j];
    }
    slots->data[i].occupied = 1;
    slots->data[i].time = 0;
    //convert the index into the floor and slot
    printf("this is i %zu\n", i);
    indexconverter(i, floor, slot, slot_num);

}

bool insertData(char * buf, SLOT_Arr *slots, size_t slot_num)
{
    char id[11] ={0};
    char ch = 0;
    if(sscanf(buf, " %10s %c", id, &ch) != 1)
    {
        return false;
    }
    if(slots->capa - slots->len == 0)
    {
        printf("Fully occupied\n");
        return true;
    }
    slots->len++;
    size_t floor = 0;
    size_t slot = 0;
    findSlot(slots, &floor, &slot, id, slot_num);
    char floor1 = 'A' + floor;
    char slot1 = 'a' + slot;
    printf("Position: %c%c, remaining: %zu\n", floor1, slot1  ,slots->capa - slots->len);

    return true;

}

void printSLOT_Arr(SLOT_Arr arr)
{
    for(size_t i = 0;i < arr.capa; i++)
    {
        printf("[%zu]: %d, (%d) %s\n", i, arr.data[i].time, arr.data[i].occupied, arr.data[i].id);
    }
}

bool search_delete(char * buf, SLOT_Arr * slots, size_t slot_num)
{
    char id[11] ={0};
    char ch = 0;
    if(sscanf(buf, " %10s %c", id, &ch) != 1)
    {
       
        return false;
    }
    bool found = 0;
    size_t i ;
    printSLOT_Arr(*slots);
    for(i = 0; i < slots->capa; i++)
    {
        if(strncmp(slots->data[i].id, id, 10) == 0 && slots->data[i].occupied)
        {
            slots->data[i].occupied = 0;
            found = 1;
            break;
        }
    }

    printf("this i: %zu--------------------\n", i);

    if(!found)
    {
        printf("Not found\n");
        return true;
    }
    size_t floor = 0;
    size_t slot = 0;
    indexconverter(i, &floor, &slot, slot_num);
    char floor1 = 'A' + floor;
    char slot1 = 'a' + slot;
    slots->len --;
    printf("Position: %c%c, remaining: %zu\n", floor1, slot1  ,slots->capa - slots->len);
    return true;
    
}

bool operation(char * line, SLOT_Arr * slots, size_t slot_num)
{
    if(line[0] == '+')
    {
        if(!insertData(line+1, slots, slot_num))
            return false;
    }
    else if(line[0] == '-')
    {
        if(!search_delete(line+1, slots, slot_num))
            return false;
    }
    else
    {
        return false;
    }

    return true;
}
void addtime(SLOT_Arr * slots)
{
    for(size_t i = 0; i < slots->capa ; i++)
    {
        if(!(slots->data[i].occupied))
        {
         slots->data[i].time ++;
        }
    }
}
int main()
{
    char *line = NULL;
    size_t capa = 0;
    ssize_t len = 0;

    size_t  floor_num = 0; size_t slot_num =0;
    char floor = 0; char slot = 0;
    printf("Size:\n");
    if(getline(&line, &capa, stdin) > 0)
    { 
        if((len = sscanf(line, " %c %c", &floor, &slot)) != 2)
        {
            free(line);
            printf("Invalid input\n");

            return -1;
        }

        if(floor < 'A' || floor > 'Z' || slot < 'a' || slot > 'z')
        {
            free(line);
            printf("Invalid input\n");

            return -1;
        }
    }

    floor_num = (floor - 'A') + 1;
    slot_num = (slot - 'a') + 1;

    //allocatae
    SLOT_Arr slots = {0};
    slots.capa = floor_num * slot_num;
    slots.data = (SLOT *) malloc (sizeof(SLOT) * slots.capa);
    printf("Requirements:\n");
    while(getline(&line, &capa, stdin) != EOF)  
    {
        addtime(&slots);
        if(!operation(line, &slots, slot_num))
        {
            printf("Invalid input\n");
        }
    }

    
    free(line);
    line = nullptr;
    free(slots.data);
    slots.data = nullptr;
    return 0;
}