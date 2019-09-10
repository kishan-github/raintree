#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define START_DATE 1
#define END_DATE 2

bool validate_date(date_t date);
void get_date_from_user(int check);
#endif
