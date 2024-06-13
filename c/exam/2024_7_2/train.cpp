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
    int capa;
    char company[4097];
}Train;

typedef struct
{
    size_t capa;
    size_t len;
    Train *data;
}Trains;

void resizeTrains(Trains *arr)
{
    if(arr->capa == arr->len)
    {
        arr->capa = arr->capa *2+10;
        arr->data=(Train *)realloc(arr->data, sizeof(Train) *arr->capa);
    }
}

void printTrains(Trains arr)
{
    for(size_t i =0;i<arr.len;i++)
    {
        printf("%d:%02d:%02d %d:%02d:%02d %d %s\n", arr.data[i].departure.h,arr.data[i].departure.m, arr.data[i].departure.s
                                                     ,arr.data[i].arrival.h,arr.data[i].arrival.m, arr.data[i].arrival.s, arr.data[i].capa, arr.data[i].company);
    }
}

void skipwhite(char ** line)
{
    while(isspace(**line))
    {
        (*line) ++;
    }
}

long int timeconverter(Time time)
{
    long int dif = time.h * 3600 + time.m * 60 + time.s;
    return dif;
}

bool isValidtime(Time time)
{
    if(time.h < 0 || time.m < 0 || time.m > 59 || time.s < 0|| time.s > 59)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int acending_depa_decending_capa(const void *a, const void *b)
{
    if(((Train *)a)->departure.dif >  ((Train *)b)->departure.dif)
    {
        return 1;
    }
    else if(((Train *)a)->departure.dif < ((Train *)b)->departure.dif)
    {
        return -1;
    }
    else if(((Train *)a)->capa < ((Train *)b)->capa)
    {
        return 1;
    }
    else if(((Train *)b)->capa < ((Train *)a)->capa)
    {
        return -1;
    }
    else 
    {
        return 0;
    }
}
bool readLine(char *line, Trains*trains, bool *dataCan)
{
    skipwhite(&line);
    char symbol= line[0];
    if(symbol != '?' && symbol != '+') return false;
    if(symbol == '+' && !(*dataCan)) return false;
    line ++;
    skipwhite(&line);
    if(symbol =='+')
    {
        char extra=0;
        resizeTrains(trains);
        if(sscanf(line, "%d:%02d:%02d %d:%02d:%02d %d %4096s %c", &trains->data[trains->len].departure.h, &trains->data[trains->len].departure.m,&trains->data[trains->len].departure.s
                                                                 ,&trains->data[trains->len].arrival.h, &trains->data[trains->len].arrival.m,&trains->data[trains->len].arrival.s
                                                                 ,&trains->data[trains->len].capa, trains->data[trains->len].company, &extra) != 8)
        {
            return false;
        }
        trains->data[trains->len].departure.dif = timeconverter(trains->data[trains->len].departure);
        trains->data[trains->len].arrival.dif = timeconverter(trains->data[trains->len].arrival);
        if(trains->data[trains->len].departure.dif  > trains->data[trains->len].arrival.dif ) return false;
        if(!isValidtime(trains->data[trains->len].arrival) || !isValidtime(trains->data[trains->len].departure)) return false;
        if (trains->data[trains->len].capa <= 0) return false;
        //store
        trains->len++;
        return true;
    }
    else if(symbol =='?')
    {
        *dataCan = false;
        char extra=0; int passenger=0;; Time query={0};
        if(sscanf(line, " %d:%02d:%02d %d %c", &query.h, &query.m, &query.s, &passenger, &extra)!=4)
        {
            return false;
        }
        query.dif = timeconverter(query);
        if(!isValidtime(query)) return false;
        if(passenger <= 0) return false;

        //sort by the departure and capa
        // printTrains(*trains);
        qsort(trains->data, trains->len, sizeof(Train), acending_depa_decending_capa);
        // printf("after sort ---------------------------------------\n");
        // printTrains(*trains);
        size_t i;bool found = false;
        for(i = 0;i<trains->len;i++)
        {
            if(query.dif <= trains->data[i].departure.dif)
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            printf("The connection doesn't exist\n");
            return true;
        }
        int count =1;bool fullyoccupied=false; int left = passenger;
        size_t k;
        for(k = i;k<trains->len;k++)
        {
            //passenger is not occupied fully
            
            if(left > trains->data[k].capa)
            {
                left-= trains->data[k].capa;
            }//where the passenger will be fully occupied
            else if(left <= trains->data[k].capa)
            {
                fullyoccupied=true;
                break;
            }
            count ++;   
        }

        if(fullyoccupied)
        {
            printf("%d:%d:%02d:%02d %d:%02d:%02d %d \n", 1 , trains->data[i].departure.h, trains->data[i].departure.m, trains->data[i].departure.s
                                                                    ,trains->data[i].arrival.h,trains->data[i].arrival.m,trains->data[i].arrival.s
                                                                    ,trains->data[i].capa);
            if(k>i)
            {
                // k--;
                printf("%d:%d:%02d:%02d %d:%02d:%02d %d\n",count, trains->data[k].departure.h, trains->data[k].departure.m, trains->data[k].departure.s
                                                                    ,trains->data[k].arrival.h,trains->data[k].arrival.m,trains->data[k].arrival.s
                                                                    ,left);
            }
        }
        else
        {
            printf("%d ppl left\n",left);
        }
    }


    return true;
}


int main()
{
    char *line=nullptr;
    size_t capa;
    ssize_t len;
    Trains trains = {0};
    bool dataCan = true;
    while((len=getline(&line, &capa, stdin))!=EOF)
    {
        if(!readLine(line, &trains, &dataCan))
        {
            printf("Invalid input.\n");
            
        }
    }
    // printTrains(trains);
    free(line);
    free(trains.data);
    return 0;

}