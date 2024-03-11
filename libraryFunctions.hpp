// This header file consist of functions that can be selected by user in library. Each corresponds to a specific work as entered by user. Each function here is self implemented and is not depended on any other function in this file

#ifndef LIBRARYFUNCTIONS_HPP
#define LIBRARYFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "book.hpp" // definition of class 'Book' to make record of book
#include "librarianConfirmation.hpp" // for librarian login
#include ".\shared\student.hpp"  // defintion of class 'Student'
#include "utilitys.hpp" // definition of class 'Date' and 'MyTeacher'

// 1 - Add New Librarian
void addNewLibrarian()
{
    system("cls"); // clear screen

    std::cin.ignore(); // ignore last typed Enter

    // if librarian is logged in
    if(librarianLogin()) {
        std::string name, password; // to hold data

        system("cls"); // clear screen
        std::cout << "Enter New Librarian Name: "; // prompt for name
        getline(std::cin, name);
        std::cout << "Enter new Password (only letters or digits): "; // prompt for password
        password = getPassword();

        Password newPerson{name, password}; // create object of 'Password' using typed data

        std::fstream file{"librarian.txt", std::ios::in | std::ios::out | std::ios::app}; // open librarian file
        if(!file) {
            std::cerr << "librarian file doesn't open";
            exit(EXIT_FAILURE);
        }

        file << newPerson.getDetails() << '\n'; // print new librarian data in file as a record
        std::cout << "\nLibrarian Added"; // display message
    }
    // if not logged in
    else {
        std::cout << "\nAccess Denied"; // display message
    }

    return; // return control
}

// 2 - Add New Books
void addNewBooks()
{
    system("cls"); // clear screen

    std::cin.ignore(); // ignore last typed Enter

    // if librarian is logged in
    if(librarianLogin()) {
        std::fstream booksFile{"bookRecords.dat", std::ios::out | std::ios::in | std::ios::binary | std::ios::app}; // open books record file

        if(!booksFile) {
            std::cerr << "Cannot open file to add books";
            exit(EXIT_FAILURE);
        }

        // variables to hold information of book
        int key;
        std::string isbn;
        std::string name;
        std::string genre;
        int quantity;

        int next; // used by loop

        do
        {
            system("cls"); // clear screen

            //deciding key, since it is generated automatically
            booksFile.seekg(0, std::ios::end); // move to end of file
            int fileSize = booksFile.tellg(); // get size of file
            int numBooks = fileSize / sizeof(Book); // divide full file size to size of one record to get number of books
            key = numBooks > 0 ? numBooks : 0; // set key

            std::cout << "Enter ISBN: "; // prompt for isbn
            std::cin >> isbn;
            std::cout << "Enter Book Name: "; // prompt for name
            std::cin.ignore();
            getline(std::cin, name); // name may include spaces
            std::cout << "Enter Book Genre: "; // prompt for genre
            std::cin >> genre;
            std::cout << "Enter Quanity Available: ";
            std::cin >> quantity;

            Book newBookRecord{key, isbn, name, genre, quantity}; // make an object using above typed data

            booksFile.write(reinterpret_cast<const char *>(&newBookRecord), sizeof(Book)); // write this record in binary file

            std::cout << "Book Added" << std::endl; // successful message

            std::cout << "\nAdd another book(1 or 0): "; // if want to add more books
            std::cin >> next;
        }while(next == 1);

        booksFile.close();
    }
    // if not logged in
    else {
        std::cout << "\nAccess Denied"; // show message
    }

    return; // return control
}

// 3 - Remove Old Book
void removeOldBook()
{
    system("cls"); // clear screen

    std::cin.ignore(); // ignore last 'enter' from the stream

    // if librarian is logged in
    if(librarianLogin()) {
        std::ifstream inputFile{"bookRecords.dat", std::ios::in | std::ios::binary}; // open book records file
        if(!inputFile) {
            std::cerr << "Cannot open file to remove book";
            exit(EXIT_FAILURE);
        }

        // check if any book is issued to someone
        // int availFlag = 1;
        // Book checkBooks;
        // while(inputFile.read(reinterpret_cast<char *>(&checkBooks), sizeof(Book)))
        // {
        //     // if al copies of book is issued i.e. quanity = 0
        //     if(checkBooks.getQuantity() == 0) {
        //         availFlag = 0; // set flag to false
        //         break;
        //     }
        // }

        // // if flag is flag, at least one book is issued
        // if(availFlag == 0) {
        //     std::cout << "Not all books are available";
        //     return; // return control, and doesn't allow to remove old book
        // }

        inputFile.seekg(0, std::ios::beg); // seek to beginning of file

        int delKey;
        
        system("cls"); 
        std::cout << "Enter Book's key to be deleted: "; // prompt to enter key of book to be deleted
        std::cin >> delKey;

        std::ofstream outputFile{"temp.dat", std::ios::out | std::ios::binary}; // create a file 'temp.dat'
        if(!outputFile) {
            std::cerr << "Cannot open file to remove book";
            inputFile.close();
            exit(EXIT_FAILURE);
        }

        int newKeys{0}; // assigning new key to each book
        bool flag = false;

        Book record;
        while(inputFile.read(reinterpret_cast<char *>(&record), sizeof(Book))) // read a record from books' file
        {
            // is book's key is not equal to delKey
            if(record.getKey() != delKey) {
                record.setKey(newKeys++);
                // write the record in 'temp' file
                outputFile.write(reinterpret_cast<const char *>(&record), sizeof(Book));
            }
            else {
                // if a book's key matched don't write it into temp file and set flag to true, indicating that the book is founded
                flag = true;
            }
        }

        // if flag is true i.e. the delKey book is not written into temp file
        if(flag == true) {
            std::cout << "Book Deleted" << '\n';
        }
        else {
            std::cout << "Book doesn't exist" << '\n';
        }

        inputFile.close();
        outputFile.close();

        remove("bookRecords.dat"); // remove books' record file
        rename("temp.dat", "bookRecords.dat"); // rename temp file to books' record
    }
    else {
        // if librarian doesn't log in
        std::cout << "\nAccess Denied";
    }

    return;
}

// 4 - check student details
void checkStudentDetails()
{
    system("cls");

    std::cin.ignore();

    // if librarian is logged in
    if(librarianLogin()) {
        system("cls");

        std::cout << "1 - Search with RollNo" << '\t' << "2 - Display all Students" << '\n' << "0 - Return" << std::endl << std::endl;

        const int LOWEST_OPTION{0};
        const int HIGHEST_OPTION{2};

        int searchChoice;
        // validating the input number
        do
        {
            std::cout << "? ";
            std::cin >> searchChoice;
        }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

        if(searchChoice == 0) {
            return;
        }

        std::ifstream studentFile{"studentRecords.dat", std::ios::in | std::ios::binary}; // open student's records file

        if(!studentFile) {
            std::cerr << "Cannot open file to read books";
            exit(EXIT_FAILURE);
        }

        switch(searchChoice)
        {
            case 1: // display student with roll no
            {
                int rollNo;
                std::cout << "\nEnter roll no: "; // prompt to enter rollNo
                std::cin >> rollNo;

                Student student;

                studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student)); // read a record from file
                while(studentFile)
                {
                    // if rollNo matched
                    if(student.getRollNo() == rollNo) {
                        std::cout << "\nResult:\n";
                        std::cout << student; // display the student's details
                        break; // break through the loop
                    }

                    // if rollNo doesn't match, read next record, until the end of file
                    studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                }
            }
                break;
            case 2: // display all students;
            {
                Student student;

                // read a record from the file
                studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                std::cout << "\nResult:\n";
                while(studentFile) // while not 'end of file'
                {
                    std::cout << student.display() << '\n'; // display the record
                    
                    // read next record
                    studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                }
            }
                break;
            default: // because of validation, control should not reach here
                std::cerr << "control should not reach here";
                break;
        }

        studentFile.close(); // close the file
    }
    // if the librarian is not logged in
    else {
        std::cout << "\nAccess Denied";
    }

    return;
}

// 5 - Borrow A Book
void borrowABook()
{
    system("cls");
    // students are issued books for 7 days and teachers for 14 days
    std::cout << "1 - For Student" << '\t' << "2 - For Teacher" << '\n' << "0 - Return" << '\n' << std::endl;

    const int LOWEST_OPTION{0};
    const int HIGHEST_OPTION{2};

    int searchChoice;
    // validating input
    do
    {
        std::cout << "? ";
        std::cin >> searchChoice;
    }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

    if(searchChoice == 0) {
        return;
    }

    // if student want to borrow book
    if(searchChoice == 1) {
        int rollNo;

        std::cout << "\n\nEnter your roll no: "; // ask for student's roll no
        std::cin >> rollNo;

        std::ifstream studentFile{"studentRecords.dat", std::ios::in | std::ios::binary}; // open students' records file
        if(!studentFile) {
            std::cerr << "cannot open student's records";
            exit(EXIT_FAILURE);
        }

        Student student;
        bool studentExist = false; // to mark if student doesn't exist
        while(studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student))) // read a student record from file
        {
            // if roll no matches
            if(student.getRollNo() == rollNo) {
                studentExist = true; // student exist

                if(alreadyIssued(rollNo)) {
                    std::cout << "The Student already have a book issued";
                    studentFile.close();

                    return;
                }

                int key;

                std::cout << "Enter book key: "; // prompt to enter book key
                std::cin >> key;

                std::fstream bookFile{"bookRecords.dat", std::ios::in | std::ios::out | std::ios::binary}; // open books' records file
                if(!bookFile) {
                    std::cerr << "cannot open book's records";
                    studentFile.close();
                    exit(EXIT_FAILURE);
                }

                Book book;
                bool bookExist = false; // to mark if book doesn't exist
                while(bookFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) // read a book record
                {
                    // if the key of book matched with input key, and the book is available
                    if((book.getKey() == key) && (book.getQuantity() > 0)) {
                        bookExist = true; // book exist

                        Date today; // create object of 'Date' initialized with current date
                        std::cout << "\nBook Issued till " << today.getDate7(); // issue book for 7 days

                        std::fstream issueFile{"issued.txt", std::ios::out | std::ios::app}; // open issued file
                        if(!issueFile) {
                            std::cerr << "cannot open issue file";
                            // close all opened files
                            studentFile.close();
                            bookFile.close();
                            exit(EXIT_FAILURE);
                        }

                        // write data of student and issued book is file
                        issueFile << rollNo << ' ' << key << ' ' << today.getDate7() << '\n'; 

                        book.reduceOneQuantity();

                        // seek back to start of record
                        bookFile.seekp(static_cast<std::streamoff>(bookFile.tellp()) - sizeof(Book));
                        bookFile.write(reinterpret_cast<const char *>(&book), sizeof(Book));

                        break;
                    }
                }

                // if book doesn't exist
                if(bookExist == false) {
                    std::cout << "\nBook not found";
                }

                bookFile.close();
                break;
            }
        }

        studentFile.close();

        // if student doesn't exist
        if(studentExist == false) {
            std::cout << "\nStudent not found";
        }
    }
    // if teacher want to borrow a book
    else if(searchChoice == 2) {
        int code;

        std::cout << "\n\nEnter your code: "; // prompt to enter teacher's code
        std::cin >> code;

        std::ifstream teacherFile{"teacherRecords.dat", std::ios::in | std::ios::binary}; // open teachers' records file
        if(!teacherFile) {
            std::cerr << "cannot open teacher's records";
            exit(EXIT_FAILURE);
        }

        MyTeacher teacher;
        bool teacherExist = false; // to mark if teacher doesn't exist
        while(teacherFile.read(reinterpret_cast<char *>(&teacher), sizeof(MyTeacher))) // read a record from teacher file
        {
            // if code matched
            if(teacher.getCode() == code) {
                teacherExist = true; // teacher exists

                if(alreadyIssued(code)) {
                    std::cout << "The Teacher already have a book issued";
                    teacherFile.close();

                    return;
                }

                int key;

                std::cout << "Enter book key: "; // prompt to enter book key
                std::cin >> key;

                std::fstream bookFile{"bookRecords.dat", std::ios::in | std::ios::out | std::ios::binary}; // open books' records file
                if(!bookFile) {
                    std::cerr << "cannot open book's records";
                    teacherFile.close();
                    exit(EXIT_FAILURE);
                }

                Book book;
                bool bookExist = false; // to mark if book doesn't exist
                while(bookFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) // read a record from book file
                {
                    // if book key matched, and book is avaiable
                    if((book.getKey() == key) && (book.getQuantity() > 0)) {
                        bookExist = true; // book exists

                        Date today; // object of 'Date' will be initialized with current date
                        std::cout << "\nBook Issued till " << today.getDate14(); // issued for 14 days

                        std::fstream issueFile{"issued.txt", std::ios::out | std::ios::app}; // open issued file
                        if(!issueFile) {
                            std::cerr << "cannot open issue file";
                            // closing opened files
                            teacherFile.close();
                            bookFile.close();
                            exit(EXIT_FAILURE);
                        }

                        issueFile << code << ' ' << key << ' ' << today.getDate14() << '\n'; // write issued book and teacher details in issue file

                        book.reduceOneQuantity();

                        // seek back to start of the record
                        bookFile.seekp(static_cast<std::streamoff>(bookFile.tellp()) - sizeof(Book));
                        bookFile.write(reinterpret_cast<const char *>(&book), sizeof(Book)); 

                        break;
                    }
                }

                // is book doesn't exist
                if(bookExist == false) {
                    std::cout << "\nBook not found";
                }

                bookFile.close();
                break;
            }
        }

        teacherFile.close();

        // if teacher doesn't exist
        if(teacherExist == false) {
            std::cout << "\nTeacher not found";
        }
    }

    return;
}

// 6 - Return A Book
void returnABook()
{
    system("cls");
    std::cout << "1 - For Student" << '\t' << "2 - For Teacher" << '\n' << "0 - Return" << '\n' << std::endl;

    const int LOWEST_OPTION{1};
    const int HIGHEST_OPTION{2};

    int searchChoice;
    // input validation
    do
    {
        std::cout << "? ";
        std::cin >> searchChoice;
    }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

    if(searchChoice == 1) { // for student
        int rollNo;

        std::cout << "\n\nEnter your roll no: "; // enter your roll no
        std::cin >> rollNo;

        std::fstream issuedFile{"issued.txt", std::ios::in}; // open issue file
        if(!issuedFile) {
            std::cerr << "cannot open issued file";
            exit(EXIT_FAILURE);
        }

        int fRollNo, fKey;
        Date fDate;

        bool flag = false;
        while(issuedFile >> fRollNo >> fKey >> fDate) // read record from issued file
        {
            // if roll no matched
            if(fRollNo == rollNo) {
                std::fstream bookFile{"bookRecords.dat", std::ios::in | std::ios::out | std::ios::binary}; // open books file
                if(!bookFile) {
                    std::cerr << "cannot open books file";
                    issuedFile.close();
                    exit(EXIT_FAILURE);
                }

                Book book;
                while(bookFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) // read a record from books' file
                {
                    // if key matched
                    if(book.getKey() == fKey) {
                        book.increaseOneQuantity();

                        // seek back to start of record
                        bookFile.seekp(static_cast<std::streamoff>(bookFile.tellp()) - sizeof(Book));
                        bookFile.write(reinterpret_cast<const char *>(&book), sizeof(Book));

                        Date toDay; // get current date
                        if(fDate >= toDay) { // if returned date is greated today i.e. not reached last date
                            std::cout << "Book returned";
                        }
                        // if returned date is crossed
                        else {
                            std::cout << "Date exceeded, try to return book on time\nBook returned";
                        }

                        break;
                    }
                }

                bookFile.close();

                flag = true; // mark flag to true, since record in issue file is founded
                break;
            }
        }

        issuedFile.seekg(0, std::ios::beg); // seek to beginning of file

        // if no record in issued file found
        if(flag != true) {
            std::cout << "No book issued";
        }
        // if a record is founded
        else {
            std::ofstream file{"temp.txt", std::ios::out}; // create a temp file
            if(!file) {
                std::cerr << "cannot open file";
                // close other files
                issuedFile.close();
                
                exit(EXIT_FAILURE);
            }

            int fRollNo, fKey;
            std::string fDate;
            while(issuedFile >> fRollNo >> fKey >> fDate) // read record from issued file
            {
                // if roll no doesn't match
                if(fRollNo != rollNo) {
                    file << fRollNo << ' ' << fKey << ' ' << fDate << '\n'; // write in temp file
                }
            }

            file.close();
            issuedFile.close();

            remove("issued.txt"); // delete issued file
            rename("temp.txt", "issued.txt"); // rename temp file to issued 
        }
    }
    // for teacher
    else if(searchChoice == 2) {
        int code;

        std::cout << "\n\nEnter your code: "; // prompt to enter code
        std::cin >> code;

        std::fstream issuedFile{"issued.txt", std::ios::in}; // open issued file
        if(!issuedFile) {
            std::cerr << "cannot open issued file";
            exit(EXIT_FAILURE);
        }

        int fCode, fKey;
        Date fDate;

        bool flag = false; // to mark if a book is returned
        while(issuedFile >> fCode >> fKey >> fDate) // read a record from the issued file
        {
            // if code matched
            if(fCode == code) {
                std::fstream bookFile{"bookRecords.dat", std::ios::in | std::ios::out | std::ios::binary};
                if(!bookFile) {
                    std::cerr << "cannot open books file";
                    issuedFile.close();
                    exit(EXIT_FAILURE);
                }

                Book book;
                while(bookFile.read(reinterpret_cast<char *>(&book), sizeof(Book))) // read record from books' records file
                {
                    // if key matched
                    if(book.getKey() == fKey) {
                        book.increaseOneQuantity();

                        // seek to start of record
                        bookFile.seekp(static_cast<std::streamoff>(bookFile.tellp()) - sizeof(Book));
                        bookFile.write(reinterpret_cast<const char *>(&book), sizeof(Book));

                        Date toDay; // get current date
                        if(fDate >= toDay) { // if return date is greater than today
                            std::cout << "Book returned";
                        }
                        // if returned date is crossed
                        else {
                            std::cout << "Date exceeded, try to return book on time\nBook returned";
                        }

                        break;
                    }
                }

                bookFile.close();

                flag = true; // mark true to indicate that a book is returned
                break;
            }
        }

        issuedFile.seekg(0, std::ios::beg); // seek to beginning to file

        // if no book is returned
        if(flag != true) {
            std::cout << "No book issued";
        }
        // if a book is returned
        else {
            std::ofstream file{"temp.txt", std::ios::out};
            if(!file) {
                std::cerr << "cannot open file";
                issuedFile.close();
                exit(EXIT_FAILURE);
            }

            int fCode, fKey;
            std::string fDate;
            while(issuedFile >> fCode >> fKey >> fDate) // read record from issued file
            {
                // if code doesn't match
                if(fCode != code) {
                    // write record in temp file
                    file << fCode << ' ' << fKey << ' ' << fDate << '\n';
                }
            }

            file.close();
            issuedFile.close();

            remove("issued.txt"); // remove issued file
            rename("temp.txt", "issued.txt"); // rename temp file to issued
        }
    }

    return;
}

// 7 - Renew Date
void renewDate()
{
    system("cls");
    std::cout << "1 - For Student" << '\t' << "2 - For Teacher" << '\n' << "0 - Return" << '\n' << std::endl;

    const int LOWEST_OPTION{0};
    const int HIGHEST_OPTION{2};

    int searchChoice;
    // input validation
    do
    {
        std::cout << "? ";
        std::cin >> searchChoice;
    }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

    if(searchChoice == 0) {
        return;
    }

    // for student
    if(searchChoice == 1) {
        int rollNo;

        std::cout << "\n\nEnter your roll no: "; // prompt to enter roll no
        std::cin >> rollNo;

        std::fstream issuedFile{"issued.txt", std::ios::in}; // open issue file
        if(!issuedFile) {
            std::cerr << "cannot open issued file";
            exit(EXIT_FAILURE);
        }

        int fRollNo, fKey;
        Date fDate;

        bool flag = false;
        while(issuedFile >> fRollNo >> fKey >> fDate) // read record from issued file
        {
            // if roll no matched
            if(fRollNo == rollNo) {
                flag = true; // mark flag as true
                break;
            }
        }

        // seek to beginning
        issuedFile.seekg(0, std::ios::beg);

        // if such student doesn't exist 
        if(flag != true) {
            std::cout << "No book issued";
        }
        // if student exists
        else {
            std::ofstream file{"temp.txt", std::ios::out}; // create a temp file
            if(!file) {
                std::cerr << "cannot open file";
                issuedFile.close();
                exit(EXIT_FAILURE);
            }

            int fRollNo, fKey;
            std::string fDate;
            while(issuedFile >> fRollNo >> fKey >> fDate) // read a record from issued file
            {
                // if roll no doesn't match
                if(fRollNo != rollNo) {
                    file << fRollNo << ' ' << fKey << ' ' << fDate << '\n'; // write record in temp file
                }
                // if roll no matched
                else {
                    Date today; // get current date
                    file << fRollNo << ' ' << fKey << ' ' << today.getDate7() << '\n'; // write record with today+7 days
                }
            }

            file.close();
            issuedFile.close();

            remove("issued.txt"); // delete issued file
            rename("temp.txt", "issued.txt"); // rename temp to issued
        }
    }
    // for teacher
    // the below code work same as the one for teacher. the only different is teacher renewed returned date is +14
    else if(searchChoice == 2) {
        int code;

        std::cout << "\n\nEnter your code: ";
        std::cin >> code;

        std::fstream issuedFile{"issued.txt", std::ios::in};
        if(!issuedFile) {
            std::cerr << "cannot open issued file";
            exit(EXIT_FAILURE);
        }

        int fCode, fKey;
        Date fDate;

        bool flag = false;
        while(issuedFile >> fCode >> fKey >> fDate)
        {
            if(fCode == code) {
                flag = true;
                break;
            }
        }

        issuedFile.seekg(0, std::ios::beg);

        if(flag != true) {
            std::cout << "No book issued";
        }
        else {
            std::ofstream file{"temp.txt", std::ios::out};
            if(!file) {
                std::cerr << "cannot open file";
                exit(EXIT_FAILURE);
            }

            int fCode, fKey;
            std::string fDate;
            while(issuedFile >> fCode >> fKey >> fDate)
            {
                if(fCode != code) {
                    file << fCode << ' ' << fKey << ' ' << fDate << '\n';
                }
                else {
                    Date today;
                    // write with 14 days ahead from today
                    file << fCode << ' ' << fKey << ' ' << today.getDate14() << '\n';
                }
            }

            file.close();
            issuedFile.close();

            remove("issued.txt");
            rename("temp.txt", "issued.txt");
        }
    }

    return;
}

// 8 - Search A Book
void searchABook()
{
    system("cls");
    std::cout << "1 - Search with Key" << '\t' << "2 - Search with Name" << '\n' << "3 - Search with ISBN" << "\t" << "4 - Filter using genre" << '\n' << "5 - Get Full List" << '\t' << "0 - Return" << std::endl << std::endl;

    const int LOWEST_OPTION{0};
    const int HIGHEST_OPTION{5};

    int searchChoice;
    // input validation
    do
    {
        std::cout << "? ";
        std::cin >> searchChoice;
    }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

    if(searchChoice == 0) {
        return;
    }

    std::fstream booksFile{"bookRecords.dat", std::ios::in | std::ios::binary}; // open books' records file

    if(!booksFile) {
        std::cerr << "Cannot open file to read books";
        exit(EXIT_FAILURE);
    }

    switch(searchChoice)
    {
        case 1: // search with key
        {
            int key;
            std::cout << "\nEnter key: "; // prompt to enter key
            std::cin >> key;

            Book libraryBook;

            // since file is binary, and books are sorted wrt key
            // seek directly to book
            booksFile.seekg(key * sizeof(Book));
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book)); // read the record

            std::cout << '\n';
            std::cout << std::setw(3) << "Key" << std::setw(50) << "Name" << std::setw(18) << "ISBN" << std::setw(18) << "Genre" << std::setw(15) << "Quantity" << '\n';
            std::cout << libraryBook.getDetails(); // display the record
        }
            break;
        case 2: // search with name
        {
            std::string name;
            std::cout << "\nEnter name: "; // prompt to enter book's name
            std::cin.ignore();
            getline(std::cin, name); // name may include spaces

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book)); // read a record from file
            while(booksFile)
            {
                // if name matches
                if(libraryBook.getName() == name) {
                    std::cout << '\n';
                    std::cout << std::setw(3) << "Key" << std::setw(50) << "Name" << std::setw(18) << "ISBN" << std::setw(18) << "Genre" << std::setw(15) << "Quantity" << '\n';
                    std::cout << libraryBook.getDetails(); // display the record
                    break;
                }

                // else read the next record, until the end of file
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 3: // search with ISBN
        {
            std::string isbn;
            std::cout << "\nEnter ISBN: "; // prompt to enter isbn of book
            std::cin >> isbn;

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book)); // read a record from the file
            while(booksFile)
            {
                // if isbn matches
                if(libraryBook.getIsbn() == isbn) {
                    std::cout << '\n';
                    std::cout << std::setw(3) << "Key" << std::setw(50) << "Name" << std::setw(18) << "ISBN" << std::setw(18) << "Genre" << std::setw(15) << "Quantity" << '\n';
                    std::cout << libraryBook.getDetails(); // display the record
                    break;
                }

                // else read the next record, until the end of file
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 4: // Filter using genre
        {
            std::string genre;
            std::cout << "\nEnter Genre: "; // prompt to enter genre of book
            std::cin >> genre;

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book)); // read a record from file
            std::cout << '\n';
            std::cout << std::setw(3) << "Key" << std::setw(50) << "Name" << std::setw(18) << "ISBN" << std::setw(18) << "Genre" << std::setw(15) << "Quantity" << '\n';
            while(booksFile)
            {
                // if genre matches
                if(libraryBook.getGenre() == genre) {
                    std::cout << libraryBook.getDetails() << '\n'; // display the record
                    // no break since we want to display all books with the genre
                }

                // read next record until the end of file
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 5: // diplay full list
        {
            Book libraryBook;

            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book)); // read a record
            std::cout << '\n';
            std::cout << std::setw(3) << "Key" << std::setw(50) << "Name" << std::setw(18) << "ISBN" << std::setw(18) << "Genre" << std::setw(15) << "Quantity" << '\n';
            while(booksFile)
            {
                std::cout << libraryBook.getDetails() << std::endl; // display it without any condition, since all record are to be displayed

                // read next record, until the end of file
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        default: // control shouldn't reach here
            std::cerr << "control should not reach here";
            break;
    }

    booksFile.close();
    return;
}

#endif