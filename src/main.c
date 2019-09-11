#include <main.h>
#include <helper_file.h>

date_t s_date;	// Start date.
date_t e_date;	// End date.

// Main function.
int main()
{
	get_date();

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

		//printf("\n s date = %d, %d, %d\ne date = %d, %d, %d", s_date.day, s_date.month, s_date.year, e_date.day, e_date.month, e_date.year);
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
