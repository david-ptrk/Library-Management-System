#ifndef UTILITYS_HPP
#define UTILITYS_HPP

#include <chrono>
#include <ctime>
#include <sstream>

class Date
{
public:
    Date()
    {
        auto currentTime = std::chrono::system_clock::now(); // get the current time point

        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime); // convert the time point to a time_t object

        std::tm* localTime = std::localtime(&currentTime_t); // convert the time_t object to a tm structure

        // Extract individual components of the date and time
        year = localTime->tm_year + 1900; // Years since 1900
        month = localTime->tm_mon + 1;    // Months start from 0
        day = localTime->tm_mday;

        // hour = localTime->tm_hour;
        // minute = localTime->tm_min;
        // second = localTime->tm_sec;
    }

    int getYear() const
    {
        return year;
    }
    int getMonth() const
    {
        return month;
    }
    int getDay() const
    {
        return day;
    }

    std::string getDate() const
    {
        std::ostringstream output;
        output << getDay() << '-' << getMonth() << '-' << getYear();

        return output.str();
    }

    std::string getDate7() const
    {
        int dd = getDay();
        int mm = getMonth();
        int yy = getYear();

        bool leap = false;
        if(((yy % 100 == 0) && (yy % 400 == 0)) || ((yy % 100 != 0) && (yy % 4 == 0))) {
            leap = true;
        }

        dd += 7; // add 7 days to the date

        // Adjust the date if necessary
        if((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd > 30) {
            dd -= 30;
            ++mm;
        }
        else if((mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10) && dd > 31) {
            dd -= 31;
            ++mm;
        }
        else if(mm == 12 && dd > 31) {
            dd -= 31;
            ++mm;
            ++yy;
        }
        else if(mm == 2 && leap && dd > 29) {
            dd -= 29;
            ++mm;
        }
        else if(mm == 2 && !leap && dd > 28) {
            dd -= 28;
            ++mm;
        }

        // Adjust the year if the month is now January of the next year
        if (mm == 1) {
            ++yy;
        }

        std::ostringstream output;
        output << dd << '-' << mm << '-' << yy;

        return output.str();
    }
private:
    int year; 
    int month;
    int day;
};

#endif