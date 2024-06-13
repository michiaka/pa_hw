#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct
{
    int h;
    int m;
    int s;
    long int dif;
}Time;

typedef struct
{
    Time departure;
    Time arrival;
    char company[4097];
}Train;

typedef struct
{   
    size_t capa;
    size_t len;
    Train *data;
}Trains;

typedef struct
{
    Train * a_b;
    Train * b_c;
} Shortest;

void prinTrain(Trains arr)
{
    for(size_t i =0; i< arr.len;i++)
    {
        printf("%02d:%02d:%02d %02d:%02d:%02d %s\n", arr.data[i].departure.h, arr.data[i].departure.m, arr.data[i].departure.s
                                                    ,arr.data[i].arrival.h, arr.data[i].arrival.m,arr.data[i].arrival.s, arr.data[i].company);
    }
}
void printTime(Time time)
{
    printf("%d:%d:%d dif %ld\n", time.h, time.m, time.s, time.dif);
}

void skipwhite(char **buf)
{
    while(isspace(**buf))
    {
        (*buf) ++;
    }
}


long int timeconverter(Time time)
{
    long int res= time.h * 3600 + time.m * 60 + time.s;
    return res;
}

bool isValidtime(Time time)
{
    if(time.m > 59 || time.m < 0) return false;
    if(time.s > 59 || time.s < 0) return false;
    if(time.h < 0) return false;
    else
        return true;
}


void resizeTrains(Trains*arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa*2+10;
        arr->data=(Train *) realloc(arr->data, sizeof(Train) *arr->capa);
    }
}

bool storedata(char * line, Trains * trains)
{

    resizeTrains(trains);
    char extra=0;
    if(sscanf(line, "%02d:%02d:%02d %02d:%02d:%02d %4096s %c", &trains->data[trains->len].departure.h, &trains->data[trains->len].departure.m, &trains->data[trains->len].departure.s
                                                , &trains->data[trains->len].arrival.h, &trains->data[trains->len].arrival.m, &trains->data[trains->len].arrival.s, trains->data[trains->len].company, &extra) !=7)
    {
        return false;
    }
    trains->data[trains->len].departure.dif=timeconverter(trains->data[trains->len].departure);
    trains->data[trains->len].arrival.dif=timeconverter(trains->data[trains->len].arrival);
    if(trains->data[trains->len].departure.dif > trains->data[trains->len].arrival.dif)
    {
        return false;
    }
    if(!isValidtime(trains->data[trains->len].departure) || !isValidtime(trains->data[trains->len].arrival))    
    {
        return false;
    }
    trains->len++;
    return true;
                        
}


int acending(const void * a, const void *b)
{
    if((*(Train *)a).departure.dif > (*(Train *)b).departure.dif )
    {
        return 1;
    }
    else if((*(Train *)a).departure.dif < (*(Train *)b).departure.dif )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

bool  findshortest(long int arrivaltoStation, Trains * trains, Train **res)
{
    qsort(trains->data, trains->len, sizeof(Train), acending);
    //1) satisgying departuretime >= arrivaltoStation
    //2) among all of  trains which satisfy 1), the one with the least arrival time
    size_t i; bool found=false;
    for(i = 0;i<trains->len;i++)
    {
        if(arrivaltoStation <= trains->data[i].departure.dif) 
        {
            found = true;
            break;
        }
    }
    long int minArrivaltime = trains->data[i].arrival.dif;
    *res = &trains->data[i];
    for(size_t k = i;k<trains->len;k++)
    {
        if(minArrivaltime > trains->data[k].arrival.dif)
        {
            minArrivaltime = trains->data[k].arrival.dif;
            *res = &trains->data[k];
        }
    }
    return found;
}

bool readLine(Trains *a_b, Trains *b_c, char* line, bool *dataCan)
{
    skipwhite(&line);
    char symbol=line[0];
    if(symbol != 'A' && symbol !='B' && symbol !='?') return false;
    if((symbol == 'A' || symbol == 'B') && !(*dataCan))
    {
        return false;
    }    
    line++;
    if(symbol != '?')
    {
        if(symbol == 'A')
        {
            if(!storedata(line, a_b))
            {
                return false;
            }
        }
        else
        {
            if(storedata(line, b_c))
            {
                return true;
            }
        }
    }
    else
    {
        *dataCan=false;
        if(a_b->len < 1 || b_c->len < 1)
        {
            printf("connection doesnt exist.\n");
            return true;
        }
        Time query={0};char extra=0;
        if(sscanf(line, "%02d:%02d:%02d %c", &query.h, &query.m, &query.s, &extra) != 3)
        {
            return false;
        }
        query.dif = timeconverter(query);
        Shortest shortest = {0};
        if(!findshortest(query.dif, a_b, &shortest.a_b))
        {
            printf("connection doesnt exist.\n");
            return true;
        }
        Time arrivaltoB={0}; 
        arrivaltoB.dif= shortest.a_b->arrival.dif;
        if(!findshortest(arrivaltoB.dif, b_c, &shortest.b_c))
        {
            printf("connection doesnt exist.\n");
            return true;
        }
 
        else
        {
            printf("A: %02d:%02d:%02d %02d:%02d:%02d %s\n", shortest.a_b->departure.h, shortest.a_b->departure.m, shortest.a_b->departure.s
                                                        , shortest.a_b->arrival.h, shortest.a_b->arrival.m, shortest.a_b->arrival.s
                                                        ,shortest.a_b->company );
            printf("B: %02d:%02d:%02d %02d:%02d:%02d %s\n", shortest.b_c->departure.h, shortest.b_c->departure.m, shortest.b_c->departure.s
                                                        , shortest.b_c->arrival.h, shortest.b_c->arrival.m, shortest.b_c->arrival.s
                                                         ,shortest.b_c->company );

        }
    }  


    return true;
}

int main()
{
    char *line = nullptr;
    size_t capa=0;
    ssize_t len=0;
    Trains a_b = {0};
    Trains b_c = {0};
    bool dataCan=true;
    printf("Jizdni rad:\n");
    while((len=getline(&line, &capa, stdin))!= EOF)
    {
        if(!readLine(&a_b, &b_c, line, &dataCan))
        {
            printf("Invalid input.\n");
        }
    }
    
    free(line);
    free(a_b.data);
    free(b_c.data);

    return 1;
}