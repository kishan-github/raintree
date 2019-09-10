#ifndef HELPER_FILE_H
#define HELPER_FILE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct date
{
        int day;
        int month;
        int year;
}date_t;

typedef enum month
{
        JAN = 1,
        FEB,
        MAR,
        APR,
        MAY,
        JUN,
        JUL,
        AUG,
        SEP,
        OCT,
        NOV,
        DEC,
        MAX_MONTH
}month_t;

bool check_leap_year(int year);
int days_in_month(int month, int year);
#endif
