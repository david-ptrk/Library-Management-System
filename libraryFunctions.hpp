// This header file consist of functions that can be selected by user in library. Each corresponds to a specific work as entered by user. Each function here is self implemented and is not depended on any other function in this file

#ifndef LIBRARYFUNCTIONS_HPP
#define LIBRARYFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "book.hpp" // consist of class 'Book' to make record of book
#include "librarianConfirmation.hpp" // for librarian login
#include ".\shared\student.hpp"

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
        bool available;

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

            available = true; // set availability to true

            Book newBookRecord{key, isbn, name, genre, available}; // make an object using above typed data

            booksFile.write(reinterpret_cast<const char *>(&newBookRecord), sizeof(Book)); // write this record in binary file

            std::cout << "Book Added" << std::endl; // successful message

            std::cout << "\nAdd another book(1 or 0): "; // if want to add more books
            std::cin >> next;
        }while(next == 1);
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
    system("cls");

    std::cin.ignore();
    if(librarianLogin()) {
        int delKey;
        
        system("cls");
        std::cout << "Enter Book's key to be deleted: ";
        std::cin >> delKey;

        std::ifstream inputFile{"bookRecords.dat", std::ios::in | std::ios::binary};
        if(!inputFile) {
            std::cerr << "Cannot open file to remove book";
            exit(EXIT_FAILURE);
        }

        std::ofstream outputFile{"temp.dat", std::ios::out | std::ios::binary};
        if(!outputFile) {
            std::cerr << "Cannot open file to remove book";
            inputFile.close();
            exit(EXIT_FAILURE);
        }

        int newKeys{0};
        bool flag = false;

        Book record;
        while(inputFile.read(reinterpret_cast<char *>(&record), sizeof(Book)))
        {
            if(record.getKey() != delKey) {
                record.setKey(newKeys++);
                outputFile.write(reinterpret_cast<const char *>(&record), sizeof(Book));
            }
            else {
                flag = true;
            }
        }

        if(flag == true) {
            std::cout << "Book Deleted" << '\n';
        }
        else {
            std::cout << "Book doesn't exist" << '\n';
        }

        inputFile.close();
        outputFile.close();

        remove("bookRecords.dat");
        rename("temp.dat", "bookRecords.dat");
    }
    else {
        std::cout << "\nAccess Denied";
    }

    return;
}

// 4 - check student details
void checkStudentDetails()
{
    system("cls");

    std::cin.ignore();
    if(librarianLogin()) {
        system("cls");

        std::cout << "1 - Search with RollNo" << '\t' << "2 - Display all Students" << std::endl << std::endl;

        const int LOWEST_OPTION{1};
        const int HIGHEST_OPTION{2};

        int searchChoice;
        do
        {
            std::cout << "? ";
            std::cin >> searchChoice;
        }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

        std::ifstream studentFile{"studentRecords.dat", std::ios::in | std::ios::binary};

        if(!studentFile) {
            std::cerr << "Cannot open file to read books";
            exit(EXIT_FAILURE);
        }

        switch(searchChoice)
        {
            case 1:
            {
                int rollNo;
                std::cout << "\nEnter roll no: ";
                std::cin >> rollNo;

                Student student;

                studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                while(studentFile)
                {
                    if(student.getRollNo() == rollNo) {
                        std::cout << "\nResult:\n";
                        std::cout << student;
                        break;
                    }
                    studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                }
            }
                break;
            case 2:
            {
                Student student;

                studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                    std::cout << "\nResult:\n";
                while(studentFile)
                {
                    std::cout << student.display() << '\n';
                    
                    studentFile.read(reinterpret_cast<char *>(&student), sizeof(Student));
                }
            }
                break;
            default:
                std::cerr << "control should not reach here";
                break;
        }

        studentFile.close();
    }
    else {
        std::cout << "\nAccess Denied";
    }

    return;
}

// 8 - Search A Book
void searchABook()
{
    system("cls");
    std::cout << "1 - Search with Key" << '\t' << "2 - Search with Name" << '\n' << "3 - Search with ISBN" << "\t" << "4 - Filter using genre" << '\n' << "5 - Get Full List" << std::endl << std::endl;

    const int LOWEST_OPTION{1};
    const int HIGHEST_OPTION{5};

    int searchChoice;
    do
    {
        std::cout << "? ";
        std::cin >> searchChoice;
    }while(searchChoice < LOWEST_OPTION || searchChoice > HIGHEST_OPTION);

    std::fstream booksFile{"bookRecords.dat", std::ios::in | std::ios::binary};

    if(!booksFile) {
        std::cerr << "Cannot open file to read books";
        exit(EXIT_FAILURE);
    }

    switch(searchChoice)
    {
        case 1: // search with key
        {
            int key;
            std::cout << "\nEnter key: ";
            std::cin >> key;

            Book libraryBook;

            booksFile.seekg(key * sizeof(Book));
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));

            std::cout << "\nResult:\n";
            std::cout << libraryBook.getDetails();
        }
            break;
        case 2: // search with name
        {
            std::string name;
            std::cout << "\nEnter name: ";
            std::cin.ignore();
            getline(std::cin, name);

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            while(booksFile)
            {
                if(libraryBook.getName() == name) {
                    std::cout << "\nResult:\n";
                    std::cout << libraryBook.getDetails();
                    break;
                }
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 3: // search with ISBN
        {
            std::string isbn;
            std::cout << "\nEnter ISBN: ";
            std::cin >> isbn;

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            while(booksFile)
            {
                if(libraryBook.getIsbn() == isbn) {
                    std::cout << "\nResult:\n";
                    std::cout << libraryBook.getDetails();
                    break;
                }
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 4: // Filter using genre
        {
            std::string genre;
            std::cout << "\nEnter Genre: ";
            std::cin >> genre;

            Book libraryBook;
            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            std::cout << "\nResult:\n";
            while(booksFile)
            {
                if(libraryBook.getGenre() == genre) {
                    std::cout << libraryBook.getDetails() << '\n';
                }
                booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            }
        }
            break;
        case 5: // diplay full list
        {
            Book libraryBook;

            booksFile.read(reinterpret_cast<char *>(&libraryBook), sizeof(Book));
            std::cout << "\nResult:\n";
            while(booksFile)
            {
                std::cout << libraryBook.getDetails() << std::endl;
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