#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//exactly one space between names
//the number of name was not limiterd
//33 slots for each name
//same-name->mark as absent or, noRe.
//after the P. R can"t be talken->bool rCan=false; after taking P
//blanc input correct->len<1 ->contiue

typedef struct
{
    char name[32];
    char sorted[32];
}Name;

typedef struct
{
    size_t capa;
    size_t len;
    Name *data;
}Student;

typedef struct
{
    size_t capa;
    size_t len;
    Student *data;
}Students;

void printStudents(Students students)
{
    //whole students
    for(size_t i=0;i<students.len;i++)
    {
        //fullname
        for(size_t j=0;j<students.data[i].len;j++)
        {
            printf("%s ", students.data[i].data[j].name);
        }
        printf("\n");
    }
}
void resizeStudent(Student *arr)//2darr-inner
{
        if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Name *)realloc(arr->data, sizeof(Name)*arr->capa);
    }
}
void resizeStudents(Students *arr)//2darr-outer
{
    if(arr->capa==arr->len)
    {
        arr->capa=arr->capa*2+10;
        arr->data=(Student *)realloc(arr->data, sizeof(Student)*arr->capa);
        for(size_t i=arr->len;i<arr->capa;i++)
        {
            arr->data[i] = {0};//initialize the inner d.a.arr struct
            resizeStudent(&arr->data[i]);//allocate using resize
        }
    }
}


void desStudents(Students *arr)
{
    for(size_t i=0;i<arr->len;i++)
    {
        free(arr->data[i].data);
    }
    free(arr->data);
}

void skipSpace(char **buf)
{
    while(isspace(**buf))
    {
        (*buf)++;
    }
}
bool readinput(Students *r, Students *p)
{
    printf("Students:\n");
    char *line=nullptr;
    size_t capa;
    ssize_t len;
    bool rCan=true;
    while((len=getline(&line, &capa, stdin))!=EOF)
    {
        char *line2=line;//having a copy pointer to iterate. line remains the same to ftrree
        //readLine
        if(len<1) continue;
        skipSpace(&line2);
        char symbol=line2[0];
        if(symbol !='R' && symbol !='P') break;
        else if(symbol == 'R' && !rCan) break;
        line2++;
        skipSpace(&line2);
        if(line2[0]!=':') 
        {
            break;
        }
        line2++;
        skipSpace(&line2);

        //readName
        //checking if there is no consecutive spaces in the string
        int rest_len=strlen(line2);
        for(int i=0;i<rest_len;i++)
        {
            if(isspace(line2[i]) && isspace(line2[i+1])) break;
        }
        char *str=line2;
        char *pch=strtok(str, " ");

        resizeStudents(r);

        if(symbol == 'R'&& rCan)
        {
            while(pch!=NULL)
            {
                resizeStudent(&r->data[r->len]);
                strcpy(r->data[r->len].data[r->data[r->len].len].name,
                        pch);
                pch=strtok(NULL, " ");
                r->data[r->len].len++;
            }
            r->len++;
        }
        else if(symbol == 'P')
        {   
            rCan=false;
            resizeStudents(p);
            while(pch!=NULL)
            {
                resizeStudent(&p->data[p->len]);
                strcpy(p->data[p->len].data[p->data[p->len].len].name,
                        pch);
                pch=strtok(NULL, " ");
                p->data[p->len].len++;
            }
            p->len++;
        }
    }
    //invalid input or end of the file
    free(line);
    return feof(stdin);
}
int main()
{
    Students r={0};
    Students p={0};

    if(!readinput(&r, &p))
    {
        printf("Invalid input.\n");
        desStudents(&r);
        desStudents(&p);
        return -1;
    }
    printf("------------------------\n");
    printStudents(r);
    printf("------------------------\n");
    printf("------------------------\n");
    printStudents(p);
    printf("------------------------\n");
        desStudents(&r);
        desStudents(&p);
    return 0;
}
