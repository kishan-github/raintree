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
