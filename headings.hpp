// This header file 'headings.hpp' consist of basic functions and implementations until a librarian is logged in. It also provide functionalities to display navigation options. This file is starting and ending point of application. Any of other files is not capable to start or end application.

#ifndef HEADING_HPP
#define HEADING_HPP

#include <iostream>
#include <fstream>
#include <conio.h>
#include "encryption.hpp" // consist of class 'Password'
#include "libraryFunctions.hpp" // consist of library internal functions
#include "librarianConfirmation.hpp" // librarian login functions

void startingInstructions(void); // welcome page of library
void newLibrarian(void); // function to create new Librarian
void showOptions(void); // navigation options of library
void doFunction(int); // call proper function as specified by user

void startingInstructions()
{
    // welcome display
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "      Welcome to Library Management System      " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::ifstream dataFile{"librarian.txt", std::ios::in}; // try to open librarian.txt

    // if file doesn't exist, no librarian exists
    if(!dataFile) {
        newLibrarian(); // create new librarian
    }
    // if file exist, at least one librarian exists
    else {
        std::cout << "\nLibrarian Login\n"; // librarian login
        
        // call 'librarianLogin' to perform login, it return true or false 
        if(librarianLogin()) {
            // if librarian is logged in
            // show options since he is librarian

            system("cls"); // clear screen
            showOptions(); // show navigation options
        }
        // else show message since he is not librarian
        else {
            std::cout << "\nAccess Denied" << std:: endl;
        }
    }

    dataFile.close(); // close the file 
    return; // return control
}

void newLibrarian(void) // to create new librarian
{
    std::ofstream dataFile{"librarian.txt", std::ios::out}; // create new file
    // if file is not created, exit the program
    if(!dataFile) {
        std::cerr << "cannot create file";
        exit(EXIT_FAILURE);
    }

    std::string name, password; // to hold typed data

    // new librarian signup
    std::cout << "\nLibrarian Signup\n"; 
    std::cout << "\nEnter your Name: "; // prompt to enter name
    getline(std::cin, name); // using 'getline' to insert spaces
    std::cout << "Enter new Password (only letters or digits): "; // prompt to enter password
    password = getPassword(); // using 'getPassword' to hide it from console

    // create Password object to encrypt password 
    Password newPerson{name, password};
    dataFile << newPerson.getDetails() << std::endl; // store the data in file
    
    // show options since he is new librarian
    system("cls"); // clear screen
    showOptions(); 

    dataFile.close(); // close the file

    return; // return control
}

void showOptions() // library navigation
{
    // these options will require librarian password again
    std::cout << "Librarian's Access:\n";
    std::cout << "1 - Add Another Librarian" << '\t' << "2 - Add New Books" << '\n' << "3 - Remove Old Books" << "\t\t" << "4 - Check Student Details" << std::endl;

    // these options will not require password again
    // anyone can check them
    std::cout << "\nPublic's Access:\n";
    std::cout << "5 - Borrow A Book" << "\t\t" << "6 - Return A Book" << '\n' << "7 - Renew Return Date" << "\t\t" << "8 - Search A Book" << '\n' << "9 - Exit Library\n" << std::endl;

    const int LOWEST_OPTION{1};
    const int HIGHEST_OPTION{9};

    int num;
    // loop until a number in range of lowest-highest is entered
    do
    {
        std::cout << "? ";
        std::cin >> num;
    }while(num < LOWEST_OPTION || num > HIGHEST_OPTION);

    // option 9 is exit library
    // so if 9 is entered do not call 'doFunction'
    if(num != 9) {
        // call 'doFunction; which will in response call function associated with entered number
        doFunction(num);
    }
    
    // if 9 is entered by user
    // exit the library
    std::cout << "\nThankYou!" << std::endl;

    exit(EXIT_SUCCESS); // exit the application, this is ending point of application
}

void doFunction(int choice) // to call specified function as entered by user
{
    // send control to case as entered by user
    switch(choice)
    {
        case 1: // new librarian
            addNewLibrarian();
            break;
        case 2: // new books
            addNewBooks();
            break;
        case 3: // remove books
            removeOldBook();
            break;
        case 4: // check student details
            checkStudentDetails();
            break;
        case 5: // borrow a book

            break;
        case 6: // return a book

            break;
        case 7: // renew date

            break;
        case 8: // search books
            searchABook();
            break;
        default:
            // control should not reach here
            std::cerr << "control should not reach here";
            break;
    }

    std::cout << "\n\nPress any key to continue..."; // it is displayed at end of working of every option
    getch(); // wait for a key
    system("cls"); // clear screen

    // again show options
    showOptions();
}

#endif