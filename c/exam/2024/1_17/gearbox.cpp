#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<float.h>

#define EPL DBL_EPSILON*1000

/*
1)  print multiple min, max-> qsort & print the res by iterating the loop until the input is the same
    print multiole 0~nth min, max ->qsort & print the res by iterating the loop until the number of type of the output type exeeds the limit specfied

2)  printing the closest one -> store the data in the two separate array(smaller, acending) & qsort
    smaller: decending order
    bigger : acending order
*/

typedef struct
{
    size_t capa;
    size_t len;
    int *data;
} Arr;

typedef struct
{
    float ratio;
    int ratio1;
    int ratio2;
} Pair;

typedef struct
{
    size_t capa;
    size_t len;
    Pair *data;
} Pairs;

void resizeArr(Arr * arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(int *)realloc(arr->data, sizeof(int) * arr->capa);
    }
}

void resizePairs(Pairs * arr)
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Pair *)realloc(arr->data, sizeof(Pair) * arr->capa);
    }
}
void printArr(Arr arr)
{
    for(size_t i = 0; i< arr.len ;i++)
    {
        printf("%d\n", arr.data[i]);
    }
}

void printPairs(Pairs arr)
{
    for(size_t i = 0; i< arr.len ;i++)
    {
        printf("%f-%d:%d\n", arr.data[i].ratio, arr.data[i].ratio1, arr.data[i].ratio2);
    }
}
void skipwhite(char **line)
{
    while(isspace(** line))
    {
        (*line)++;
    }
}
int  acending(const void *a, const void * b)
{
    float num1 = (*(float *)a), num2 =(*(float *)b);
    if(fabs(num1-num2) <= EPL*(fabs(num1)+fabs(num2)))
    {
        return 0;
    }
    else if(num1 > num2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
int deceding(const void *a, const void *b)
{
        float num1 = (*(float *)a), num2 =(*(float *)b);
    if(fabs(num1-num2) <= EPL*(fabs(num1)+fabs(num2)))
    {
        return 0;
    }
    else if(num1 > num2)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
 
int findGcd(int first, int second) {
    int min=first<second?first:second;
    int gcd=1;
    for(int i=2;i<=min;i++)
    {
        if(first%i==0 && second%i==0)
        {
            gcd=i;
        }
    }
    return gcd;
}
 
void printRes(Pairs arr, int num, bool issmaller, char * company)
{
    if(arr.len < 1)
    {
        return;
    }
    if(issmaller)
    {
        printf("A smaller ratio:\n");
    }
    else
    {
        printf("A bigger ratio:\n");
    }
    int count = 0;
    float prev=0;//assign the value which will satisfy the condition for the first iteration
    for(size_t i=0;i<arr.len;i++)
    {
        //NEW TYPE OF OUTPUT
        if(!(fabs(prev-arr.data[i].ratio) <= EPL*(fabs(prev)+fabs(arr.data[i].ratio))))
        {
            count++;   
            if(count > num) break; // here you check 
            int gcd = findGcd(arr.data[i].ratio1, arr.data[i].ratio2);
            int reduced_ratio1=arr.data[i].ratio1/gcd,
            reduced_ratio2=arr.data[i].ratio2/gcd;
            printf("%d:%d\n", reduced_ratio1, reduced_ratio2);        
        }
        printf("* %s: %d:%d\n", company, arr.data[i].ratio1, arr.data[i].ratio2);
    }
}

bool readLine(char *line, Arr * arr, char * company, bool * stored)
{
    skipwhite(&line);
    char symbol=line[0];
    if(symbol!='+' && symbol !='?') return false;
    if(!stored && symbol == '?') return false;
    line ++;
    skipwhite(&line);
    if(symbol == '+')
    {
        int num = 0; char extra =0;
        if(sscanf(line, "%d %4096s %c", &num, company, &extra) != 2)
        {
            return false;
        }
        resizeArr(arr);
        arr->data[arr->len++] = num;
    }
    if(symbol == '?')
    {
        // printf("this is the input:----------------------\n");
        // printArr(*arr);    

        int ratio1=0,ratio2=0;float ratio=0;int num=0;//store it in tthe datatype same as it is given with 
        if(sscanf(line, "%d:%d,%d", &ratio1, &ratio2, &num) != 3)
        {
            return false;
        }
        if(ratio1==0||ratio2==0)
        {
            return false;
        }
        float r1=ratio1, r2=ratio2;
        ratio=r1/r2;

        Pairs smaller={0}; Pairs bigger={0};bool samefound=false;
        for(size_t i=0; i<arr->len;i++)
        {
            for(size_t k=0;k<arr->len;k++)
            {
                float cur_ratio=0;
                float cur_ratio1=arr->data[i];float cur_ratio2=arr->data[k];//to compute in a float you need to store in the float 
                cur_ratio=cur_ratio1/cur_ratio2;
                //print the result of the computation before the the if condition
                // printf("cur_ratio %f, ratio %f\n", cur_ratio, ratio);
                if(fabs(cur_ratio-ratio) <= EPL*(fabs(cur_ratio)+fabs(ratio)))// first
                {
                    if(!samefound)
                    {
                        printf("Exactly:\n");
                        printf("%d:%d\n", ratio1, ratio2);
                        samefound=true;
                    }

                    printf("* %s: %d:%d\n", company, arr->data[i], arr->data[k]);
                }
                else if(cur_ratio < ratio)
                {
                    resizePairs(&smaller);
                    smaller.data[smaller.len].ratio=cur_ratio;
                    smaller.data[smaller.len].ratio1=arr->data[i];
                    smaller.data[smaller.len].ratio2=arr->data[k];
                    smaller.len++;
                }
                else
                {
                    resizePairs(&bigger);
                    bigger.data[bigger.len].ratio=cur_ratio;
                    bigger.data[bigger.len].ratio1=arr->data[i];
                    bigger.data[bigger.len].ratio2=arr->data[k];
                    bigger.len++;
                }
            }
        }
        // printf("ALL THE RATIO  :------------------------------------\n");
        // printPairs(smaller);
        // printPairs(bigger);
        // printf("PRINTING THE  :------------------------------------\n");
        
        if(!samefound)
        {
            qsort(smaller.data, smaller.len, sizeof(Pair), deceding);
            qsort(bigger.data, bigger.len, sizeof(Pair), acending);

            //take num from the both arrays 
            printRes(smaller, num, true, company);
            printRes(bigger, num, false, company);
        }
        

        free(smaller.data);
        free(bigger.data);
        printf("---------------------------------------------------\n");

        }
    
    return true;
}

int main()
{
    char *line=nullptr;
    size_t capa=0;
    ssize_t len=0;
    Arr arr={0};    
    char company[4097];
    bool stored=false;
    printf("Gears:\n");

    while((len=getline(&line,&capa, stdin))!= EOF)
    {
        if(!readLine(line, &arr, company, &stored))
        {
            printf("Invalid input\n");
            free(arr.data);
            return -1;
        }
    }

    free(line);
    free(arr.data);
    return 0;

}