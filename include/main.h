#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define START_DATE 1
#define END_DATE 2
#define CHECK_TEXT "Client is disconnected from agent"
#define COMPUTER_NAME "ComputerName:"
#define DELIMITER_SPACE " "
#define DELIMITER_MONTH_DATE "/"
#define DELIMITER_LOG "|"
#define DELIMITER_START_DATE "("

typedef struct log_details
{
	char *name;
	int no_of_disconnect;
	struct log_details *next;
}log_details_t;

void get_date();
void get_date_from_user(int check);
void check_log_file();
void check_log_file_data(char *f_name);
bool is_date_in_range(char *buff);
void find_pattern(char *buff, int *day, int *month);
void get_computer_name(char *buff, char *c_name);
void add_to_list(char *c_name);
log_details_t* get_computer_handle(char *c_name);
void print_computer_names();
#endif
