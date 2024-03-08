#ifndef UTILITYS_HPP
#define UTILITYS_HPP

#include <chrono>
#include <ctime>
#include <sstream>
#include "./shared/teacher.hpp"

class Date
{
    friend std::istream& operator>>(std::istream&, Date&);
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

    std::string getDate14() const
    {
        int dd = getDay();
        int mm = getMonth();
        int yy = getYear();

        bool leap = false;
        if(((yy % 100 == 0) && (yy % 400 == 0)) || ((yy % 100 != 0) && (yy % 4 == 0))) {
            leap = true;
        }

        dd += 14; // add 14 days to the date

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

    bool operator>=(const Date& other) const
    {
        if(year > other.year) {
            return true;
        }
        else if(year < other.year) {
            return false;
        }

        // If years are equal, compare months
        if(month > other.month) {
            return true;
        }
        else if(month < other.month) {
            return false;
        }

        // If months are equal, compare days
        return day >= other.day;
    }
private:
    int year; 
    int month;
    int day;
};

std::istream& operator>>(std::istream& input, Date& obj)
{
    std::string dateString;
    if (std::getline(input, dateString)) {
        std::istringstream dateStream(dateString);
        char delimiter;

        dateStream >> obj.day >> delimiter >> obj.month >> delimiter >> obj.year;
    }

    return input;
}


class MyTeacher : public Teacher
{
    friend std::ostream& operator<<(std::ostream&, const MyTeacher&); // overloaded stream extraction operator
    friend std::istream& operator>>(std::istream&, MyTeacher&); // overloaded stream insertion operator
public:
    MyTeacher() = default;
    MyTeacher(const std::string first, const std::string last, int age, const std::string card, bool gen, const std::string phone, const std::string department, const std::string rank, int code)
        : Teacher(first, last, age, card, gen, phone, department, rank) {
            setCode(code);
        }
    
    void setCode(int v)
    {
        code = v;
        return;
    }
    int getCode() const
    {
        return code;
    }

    std::string display() const
    {
        std::ostringstream output; // creating object of class 'ostringstream'
        output << Teacher::display() << ' ' << getCode(); // concatenate all data members with spaces in between

        return output.str(); // return it as string
    }
private:
    int code;
};

std::ostream& operator<<(std::ostream& output, const MyTeacher& teacher)
{
    output << "First Name: " << teacher.getFirstName() << "\nLast Name: " << teacher.getLastName() <<  "\nAge: " << teacher.getAge() << "\nID Card Number: " << teacher.getIdCard() << "\nGender: " << (teacher.getGender() ? "Male" : "Female") << "\nCode: " << teacher.getCode() << "\nPhone Number: " << teacher.getPhoneNumber() << "\nDepartment: " << teacher.getDepartment() << "\nRank: " << teacher.getRank() << '\n'; // display in a fixed format

    return output; // enablea cout << a << b << c
}
std::istream& operator>>(std::istream& input, MyTeacher& teacher)
{
    std::string first, last, idCard, phone, department, rank;
    int age, gender, code;
    
    input >> first >> last >> age >> idCard >> gender >> code >> phone; // input all data members
    getline(input, department);
    input >> rank;

    // calling set functions to ensure our c-type strings proper handling
    teacher.setFirstName(first);
    teacher.setLastName(last);
    teacher.setAge(age);
    teacher.setIdCard(idCard);
    teacher.setGender(gender);
    teacher.setCode(code);
    teacher.setPhoneNumber(phone);
    teacher.setDepartment(department);
    teacher.setRank(rank);

    return input; // enables cin >> a >> b >> c
}

#endif