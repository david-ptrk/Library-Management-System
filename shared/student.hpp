// This file consist of definition of class 'Student'. It inherit publically from class 'Person'. It provide default and argumented constructor. It also provide 'display' functions to return all data of student as a record. It also have overloaded stream insertion and stream extraction operator. Try to carefully understand their definition before using them.

#ifndef STUDENT_HPP
#define STUDENT_HPP

// preprocessor directives
#include <string>
#include <exception>
#include "person.hpp"

class Student : public Person {
    friend std::ostream& operator<<(std::ostream&, const Student&); // overloaded stream extraction operator
    friend std::istream& operator>>(std::istream&, Student&); // overloaded stream insertion operator

private:
    // it uses c-type strings to hold string data
    // as it helps to write fixed length records
    int rollNo;
    char phoneNumber[12];
    char department[25];
    int semester;

public:
    Student() = default; // default constructor
    Student(const std::string first, const std::string last, int age, const std::string card, bool gen, int roll, const std::string phone, const std::string department, int sem) // constructor with arguments
        : Person(first, last, age, card, gen) {
            // calling respective set functions
            setRollNo(roll);
            setPhoneNumber(phone);
            setDepartment(department);
            setSemester(sem);
    }

    const int PHONE_LENGTH{12}; // size of 'phoneNumber'
    const int DEPARTMENT_LENGTH{25}; // size of 'department'

    void setRollNo(int roll) {
        if(roll <= 0) { // roll no must not be zero or negative
            throw std::invalid_argument{"roll no must be >= 1"};
        }

        this->rollNo = roll;
        return;
    }
    int getRollNo() const {
        return this->rollNo;
    }

    void setPhoneNumber(const std::string phone) {
        size_t length = phone.size(); // getting size of 'phone'
        length = length < PHONE_LENGTH ? length : (PHONE_LENGTH - 1); // length must be one less than 'phoneNumber' length
        phone.copy(this->phoneNumber, length); // copy one less than length in 'phoneNumber'
        this->phoneNumber[length] = '\0'; // add null character at end of 'phoneNumber;
        return;
    }
    std::string getPhoneNumber() const {
        std::string number{this->phoneNumber}; // create string of 'phoneNumber'
        return number;
    }

    void setDepartment(const std::string depart) {
        size_t length = depart.size(); // getting size of 'depart'
        length = length < DEPARTMENT_LENGTH ? length : (DEPARTMENT_LENGTH - 1); // length must be one less than 'department' lengthh
        depart.copy(this->department, length); // copy one less than length in 'department'
        this->department[length] = '\0'; // add null character at end of 'department'
        return;
    }
    std::string getDepartment() const {
        std::string depart{this->department}; // create string of 'department'
        return depart;
    }

    void setSemester(int sem) {
        if(sem <= 0 || sem > 8) { // semester must be 1-8
            throw std::invalid_argument{"semester must be 1-8"};
        }

        this->semester = sem;
        return;
    }
    int getSemester() const {
        return this->semester;
    }

    // 'display' return as a concatenated record of all data members
    std::string display() const {
        std::ostringstream output; // creating object of class 'ostringstream'
        output << Person::display() << ' ' << getRollNo() << ' ' << getPhoneNumber() << ' ' << getDepartment() << ' ' << getSemester(); // concatenate all data members with spaces in between

        return output.str(); // return it as string
    }
};

std::ostream& operator<<(std::ostream& output, const Student& student) {
    output << "First Name: " << student.getFirstName() << "\nLast Name: " << student.getLastName() <<  "\nAge: " << student.getAge() << "\nID Card Number: " << student.getIdCard() << "\nGender: " << (student.getGender() ? "Male" : "Female") << "\nRoll No: " << student.getRollNo() << "\nPhone Number: " << student.getPhoneNumber() << "\nDepartment: " << student.getDepartment() << "\nSemester: " << student.getSemester() << "\n"; // display in a fixed format

    return output; // enablea cout << a << b << c
}

std::istream& operator>>(std::istream& input, Student& student) {
    std::string first, last, idCard, phone, department;
    int age, gender, roll, sem;
    
    input >> first >> last >> age >> idCard >> gender >> roll >> phone; // input all data members
    std::cin.ignore();
    getline(input, department); // department name can take space
    input >> sem;

    // calling set functions to ensure our c-type strings proper handling
    student.setFirstName(first);
    student.setLastName(last);
    student.setAge(age);
    student.setIdCard(idCard);
    student.setGender(gender);
    student.setRollNo(roll);
    student.setPhoneNumber(phone);
    student.setDepartment(department);
    student.setSemester(sem);

    return input; // enables cin >> a >> b >> c
}

#endif