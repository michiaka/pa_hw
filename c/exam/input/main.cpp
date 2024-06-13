#include<stdio.h>//1236
#include<stdlib.h>
#include<ctype.h>

int main()
{
    int data[3][3];
    int num1=0, num2=0, num3=0;
    int index1=0;
    // int index2=0;
    // bool wasdigit=false;
    char ch=0;
    scanf(" %c", &ch);
    while(scanf("%d%d%d %c", &num1, &num2, &num3, &ch) == 4
        && (ch == ',' || ch== ')'))
    {       
            data[index1][0]=num1;
            data[index1][1]=num2;
            data[index1][2]=num3;   
            index1++;
    }

    if(ch != ')')//loop gets out with the last symbol
    {
        printf("Invalid.\n");
        return -1;
    }
    if(!feof(stdin))//loop gets out with invalid format in the middle of the input
    {
        printf("Invalid.\n");
        return -1;
    }

    for(int i=0;i<3;i++)
    {
        for(int k=0;k<3;k++)
        {
            printf("%d ", data[i][k]);
        }
        printf("\n");
    }

    return 0;
}