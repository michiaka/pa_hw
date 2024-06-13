#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */


bool isLeapyear(int y)
{
    if(y % 4000 == 0)return false;
    if(y % 400 == 0)return true;
    if(y % 1000 == 0)return false;
    if(y % 4 == 0)return true;

    return false;
}
bool isValidDay(int d, int m, int y)
{

    if(d < 1)
        return false;
    if(m == 2)
    {
        if(isLeapyear(y))
        {
            if(d > 29)
                return false;
        }
        else 
        {
            if(d > 28)
                return false;
        }
    }
    else if(m == 4 || m == 6 || m == 9 || m == 11)
    {
        return (d <= 30);
    }
    else
       { return (d <= 31);}

        return true;
}
bool isValidDate(int day, int month, int year)
{
    if(year < 2000 || (!((month >= 1) &&(month <= 12))) 
    || !isValidDay(day, month, year) ) 
    {
        return false;
    }
    return true;
}


int dateToIndex(int day, int month, int year, int *idx) {
    /* TODO: Your code here */
    if(!isValidDate(day, month, year))
        return 0;

    int totalDays = 0;

    int dayInMonth[] = {31, 28, 31, 30, 31, 30 , 31, 31, 30, 31, 30 , 31};
    for(int m = 1; m < month; m++)
    {
        totalDays += dayInMonth[m - 1];
        if(m == 2 && isLeapyear(year))
        {
            totalDays ++;
        }
    }

    totalDays += day;

    printf("day %d\n", totalDays);
    *idx = totalDays;

    return 1;
}

#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    return 0;
}
#endif /* __PROGTEST__ */

