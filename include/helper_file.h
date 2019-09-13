#ifndef HELPER_FILE_H
#define HELPER_FILE_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define LOG_FILE "../log_files/"

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
bool validate_date(date_t date);
bool compare_dates(date_t s_date, date_t e_date);
void get_log_file_names();
void create_file_name(char *f_name);
#endif
