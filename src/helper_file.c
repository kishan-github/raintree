#include <helper_file.h>

// Check if the year is leap year or not.
bool check_leap_year(int year)
{
    // If a year is multiple of 400 then it is a leap year
    if (year % 400 == 0)
        return true;

    // Else If a year is muliplt of 100 then it is not a leap year
    if (year % 100 == 0)
        return false;

    // Else If a year is muliplt of 4 then it is a leap year
    if (year % 4 == 0)
        return true;

    return false;
}

// Get the no of days in a particular month of the year.
int days_in_month(int month, int year)
{
        switch(month)
        {
                case JAN:
                case MAR:
                case MAY:
                case JUL:
                case AUG:
                case OCT:
                case DEC:
                        return 31;
                case APR:
                case JUN:
                case SEP:
                case NOV:
                        return 30;
                case FEB:
                        if(check_leap_year(year))
                                return 29;
                        else
                                return 28;
                default:
                        printf("\nInvalid month value");
                        return MAX_MONTH;
        }
}

// Check the date entered by user is valid or not.
bool validate_date(date_t date)
{
        time_t t = time(NULL);
        struct tm date_time = *localtime(&t);

        // Check if the year exceeds the current year.
        if(date.year > (date_time.tm_year + 1900))
        {
                printf("\nYear can't be greater than current year.");
                return false;
        }

        // Check if month exceeds the current year's month.
        if( (date.year == (date_time.tm_year + 1900)) &&
            (date.month > (date_time.tm_mon + 1)))
        {
                printf("\nDate exceeded the current date");
                return false;
        }

        // Check if day exceeds the current date.
        if( (date.year == (date_time.tm_year + 1900)) &&
            (date.month == (date_time.tm_mon + 1)) &&
            (date.day > date_time.tm_mday) )
        {
                printf("\nDate exceeded the current date");
                return false;
        }

        // Month should be between 1-12.
        if( (date.month < JAN) || (date.month > DEC) )
        {
                printf("\nMonth value is incorrect.");
                return false;
        }

	// Date should be between 1-31.
	if( (date.day < 0) || (date.day > days_in_month(date.month, date.year)) )
        {
                printf("\nDate value is incorrect.");
                return false;
        }

        return true;
}

// Check that start date should be smaller than end date.
bool compare_dates(date_t s_date, date_t e_date)
{
	bool valid = true;

	if(s_date.year > e_date.year)
	{
		valid = false;
	}
	else if(s_date.month > e_date.month)
	{
		valid = false;
	}
	else if(s_date.day > e_date.day)
	{
		valid = false;
	}
	
	if(!valid)
		printf("\nStart date cannot be greater than end date. Please try again.");

	return valid;
}

// Create the command to get the file names and store them in "log_file_names.txt" file.
status_t get_log_file_names()
{
	char cmd[100] = "";
	int exit_status = 0;

	// Create the command.
	strcpy(cmd, "ls ");
	strcat(cmd, LOG_FILE);
	strcat(cmd, " -1 > ");
	strcat(cmd, LOG_FILE_NAME);

	// Execute the command.
	exit_status = system(cmd);

	if(exit_status == -1)
	{
		printf("\nSystem command (%s) failed.", cmd);
		return FAILURE;
	}

	return SUCCESS;
}

// Create the complete file name by appending f_name to ../log_files/
void create_file_name(char *f_name)
{
	char f_name_temp[100] = "";

	strcpy(f_name_temp, LOG_FILE);
	strcat(f_name_temp, f_name);
	strcpy(f_name, f_name_temp);
}

// Extract the date from the log data.
status_t get_date_from_log(char *buff, date_t *log_date)
{
        char *token = NULL;

        // Look for the '|' character in log as date is given between starting and ending '|'
        buff = strstr(buff, DELIMITER_LOG);
        if(!buff)
                return FAILURE;

        // Look for '(' in log which is the starting point of date.
        buff = strstr(buff, DELIMITER_START_DATE);
        if(!buff)
                return FAILURE;

        // Increment by 1 to skip the '(' character.
        buff++;
        if(!buff)
                return FAILURE;

        // (MONTH/DAY) : Get month.
        token = strtok(buff, DELIMITER_MONTH_DATE);
        if(!token)
                return FAILURE;

        log_date->month = atoi(token);

        // (MONTH/DAY) : Get day.
        token = strtok(NULL, DELIMITER_SPACE);
        if(!token)
                return FAILURE;

        log_date->day = atoi(token);

        return SUCCESS;
}

// Extract the computer name from the log data.
status_t get_computer_name(char *buff, char *c_name)
{
        int idx = 0;

        // Look for the ComputerName: string to get the name.
        buff = strstr(buff, COMPUTER_NAME);
        if(!buff)
                return FAILURE;

        // Iterate to reach the ':' character.
        while(buff[idx] != ':')
        {
                buff++;
                if(!buff)
                        return FAILURE;
        }

        // Get the Computer name.
        buff = strtok(buff, DELIMITER_SPACE);
        if(!buff)
                return FAILURE;

        // Increment to avoid the ':' character from name.
        buff++;
        if(!buff)
                return FAILURE;

        strcpy(c_name, buff);
        return SUCCESS;
}
