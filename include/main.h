#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <helper_file.h>

#define START_DATE 1
#define END_DATE 2
#define CHECK_TEXT "Client is disconnected from agent"
#define MAX_FNAME_LENGTH 100
#define MAX_BUFFER_LENGTH 1000
#define MAX_CNAME_LENGTH 50

typedef struct log_details
{
	char *name;
	int no_of_disconnect;
	struct log_details *next;
}log_details_t;

void get_date();
void get_date_from_user(int check);
status_t check_log_file();
status_t check_log_file_data(char *f_name);
bool is_date_in_range(char *buff);
status_t add_to_list(char *c_name);
log_details_t* get_computer_handle(char *c_name);
void print_computer_names();
status_t arrange_list();
status_t swap_items(log_details_t **ptr, log_details_t **ptr_next);
#endif
