#include <main.h>

date_t s_date;	// Start date.
date_t e_date;	// End date.
log_details_t *log_data; // Head of the linked list containing name and no of disconnect.

// Main function.
int main()
{
	// Get the date from user, validate it and compare start and end date.
	get_date();

	// Get log file names in a log_file_names.txt file.
	get_log_file_names();

	// Check the content of each log file.
	check_log_file();

	// Print all computer names with there no of disconnect.
	print_computer_names();
	return 0;
}

// Get start and end date from user and compare them.
void get_date()
{
	do
	{
		printf("\nPlease enter start date.");
		// Get the start date.
		get_date_from_user(START_DATE);

		printf("\nPlease enter end date.");
		// Get the end date.
		get_date_from_user(END_DATE);
	}while(!compare_dates(s_date, e_date));
}

// Get date from user.
void get_date_from_user(int check)
{
        int day = 0;
        int month = 0;
        int year = 0;
        date_t temp_date;

        while(1)
        {
                printf("\nEnter the date in format DD MM YYYY : ");
                while(scanf("%d%d%d", &day, &month, &year) != 3)
                {
                        printf("\nNon numeric value encountered.\nPlease enter date again : ");
                        while(getchar() != '\n');
                        continue;
                }

                memset(&temp_date, 0, sizeof(temp_date));
                temp_date.day = day;
                temp_date.month = month;
                temp_date.year = year;
                if(validate_date(temp_date))
                        break;
        }
        if(check == START_DATE)
        {
                s_date.day   = day;
                s_date.month = month;
                s_date.year  = year;
        }
        else
        {
                e_date.day   = day;
                e_date.month = month;
                e_date.year  = year;
	}
}

// Check content of each file.
status_t check_log_file()
{
	FILE *fptr = NULL;
	char f_name[100];

	fptr = fopen("log_file_names.txt", "r");
	if(!fptr)
	{
		printf("\nUnable to open file.");
		return FAILURE;
	}

	while(fscanf(fptr,"%s", f_name) == 1)
	{
		create_file_name(f_name);
		check_log_file_data(f_name);
	}

	fclose(fptr);
	return SUCCESS;
}

// Check data of log file f_name.
status_t check_log_file_data(char *f_name)
{
	FILE *fptr = NULL;
	char buff[1000] = "";
	char c_name[50] = "";

	fptr = fopen(f_name, "r");
	if(!fptr)
	{
		printf("\nUnable to open file - %s.", f_name);
		return FAILURE;
	}

	while(fgets(buff, sizeof(buff), fptr) != NULL)
	{
		if(!strstr(buff, CHECK_TEXT))
			continue;

		if(!is_date_in_range(buff))
			continue;

		get_computer_name(buff, c_name);
		add_to_list(c_name);
	}
	fclose(fptr);
	return SUCCESS;
}

// Check if the date in the logs is in the range of user start and end date.
bool is_date_in_range(char *buff)
{
	date_t log_date;

	memset(&log_date, 0, sizeof(log_date));
	if(get_date_from_log(buff, &log_date) == FAILURE)
		return false;

	if( (log_date.month < s_date.month) || (log_date.month > e_date.month))
		return false;

	if( (log_date.day < s_date.day) || (log_date.day > e_date.day))
		return false;

	return true;
}

// Extract the date from the log data.
status_t get_date_from_log(char *buff, date_t *log_date)
{
	buff = strstr(buff, DELIMITER_LOG);
	if(!buff)
		return FAILURE;

	buff = strstr(buff, DELIMITER_START_DATE);
	if(!buff)
		return FAILURE;

	buff++;
	if(!buff)
		return FAILURE;

	log_date->month = atoi(strtok(buff, DELIMITER_MONTH_DATE));
	log_date->day = atoi(strtok(NULL,DELIMITER_SPACE));

	return SUCCESS;
}

// Extract the computer name from the log data.
void get_computer_name(char *buff, char *c_name)
{
	//int idx = 0;

	buff = strstr(buff, COMPUTER_NAME);
	/*while(buff[idx++] != ':')
		buff++;*/
	buff += 13;
	buff = strtok(buff, DELIMITER_SPACE);
	strcpy(c_name, buff);
}

// Add the c_name computer to the list.
status_t add_to_list(char *c_name)
{
	log_details_t *data = NULL;
	log_details_t *ptr = NULL;

	data = get_computer_handle(c_name);
	if(data)
	{
		data->no_of_disconnect++;
	}
	else
	{
		ptr = malloc(sizeof(log_details_t));
		if(ptr == NULL)
		{
			printf("\nMemory allocation failed.");
			return FAILURE;
		}

		ptr->name = malloc(sizeof(char) * strlen(c_name));
		if(ptr->name == NULL)
		{
			printf("\nMmeory allocation failed.");
			free(ptr);
			return FAILURE;
		}

		strcpy(ptr->name, c_name);
		ptr->no_of_disconnect = 1;
		ptr->next = log_data;
		log_data = ptr;
	}
	return SUCCESS;
}

// Get the node address if computer name (c_name) is already available in the list.
log_details_t* get_computer_handle(char *c_name)
{
	log_details_t *data = log_data;

	if(data == NULL)
		return NULL;

	while(data)
	{
		if(!strcmp(data->name, c_name))
			return data;
		data = data->next;
	}

	return NULL;
}

// Display the computer name and there corresponding disconnect count.
void print_computer_names()
{
	log_details_t *ptr = log_data;

	while(ptr)
	{
		printf("\n%s %d", ptr->name, ptr->no_of_disconnect);
		ptr = ptr->next;
	}
}
