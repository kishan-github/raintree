#ifndef HELPER_FILE_H
#define HELPER_FILE_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define LOG_FILE "../log_files/"
#define COMPUTER_NAME "ComputerName:"
#define DELIMITER_SPACE " "
#define DELIMITER_MONTH_DATE "/"
#define DELIMITER_LOG "|"
#define DELIMITER_START_DATE "("
#define LOG_FILE_NAME "log_file_names.txt"

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

typedef enum status
{
	SUCCESS,
	FAILURE
}status_t;

bool check_leap_year(int year);
int days_in_month(int month, int year);
bool validate_date(date_t date);
bool compare_dates(date_t s_date, date_t e_date);
status_t get_log_file_names();
void create_file_name(char *f_name);
status_t get_date_from_log(char *buff, date_t *log_date);
status_t get_computer_name(char *buff, char *c_name);
#endif
