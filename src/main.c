#include <main.h>
#include <helper_file.h>

date_t s_date;	// Start date.
date_t e_date;	// End date.

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

	// Day should be between 1-31.
	if( (date.day < 0) || (date.day > days_in_month(date.month, date.year)) )
	{
		printf("\nDate value is incorrect.");
		return false;
	}

	return true;
}

// Get date from the user.
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

int main()
{
	printf("\nPlease enter start date.");
	// Get the start date.
	get_date_from_user(START_DATE);

	printf("\nPlease enter end date.");
	// Get the end date.
	get_date_from_user(END_DATE);

	//printf("\n s date = %d, %d, %d\ne date = %d, %d, %d", s_date.day, s_date.month, s_date.year, e_date.day, e_date.month, e_date.year);
	return 0;
}
