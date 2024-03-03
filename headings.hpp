// This header file 'headings.hpp' consist of basic functions and implementations until a librarian is loged in.

#ifndef HEADING_HPP
#define HEADING_HPP

#include <iostream>
#include <fstream>
#include <conio.h>
#include "encryption.hpp" // consist of class Password
#include "libraryFunctions.hpp" // consist of library internal functions
#include "librarianConfirmation.hpp"

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

    // try to open librarian.txt
    std::ifstream dataFile{"librarian.txt", std::ios::in};

    if(!dataFile) { // if file doesn't exist, no librarian exists
        newLibrarian(); // create new librarian
    }
    else { // if file exist, at least one librarian exists
        std::cout << "\nLibrarian Login\n"; // login
        
        if(librarianLogin()) {
            // show options since he is librarian
            system("cls");
            showOptions();
        }
        // else show error message
        else {
            std::cout << "\nAccess Denied" << std:: endl;
        }
    }

    dataFile.close(); // close the file 
    return;
}

void newLibrarian(void) // to create new librarian
{
    std::ofstream dataFile{"librarian.txt", std::ios::out}; // create new file
    if(!dataFile) {
        std::cerr << "cannot create file";
        exit(EXIT_FAILURE);
    }

    std::string name, password;

    // new librarian signup
    std::cout << "\nLibrarian Signup\n";
    std::cout << "\nEnter your Name: ";
    getline(std::cin, name);
    std::cout << "Enter new Password (only letters or digits): ";
    password = getPassword();

    // create Password object to encrypt password and store it in file
    Password newPerson{name, password};
    dataFile << newPerson.getDetails() << std::endl;
    
    // show options since he is new librarian
    system("cls");
    showOptions();

    dataFile.close();

    return;
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
    do
    {
        std::cout << "? ";
        std::cin >> num;
    }while(num < LOWEST_OPTION || num > HIGHEST_OPTION);

    // option 9 is exit library
    // so if 9 is entered do not call doFunction
    if(num != 9) {
        // call doFunction which will in response call function associated with entered number
        doFunction(num);
    }
    
    // exit the library
    std::cout << "\nThankYou!" << std::endl;
    exit(EXIT_SUCCESS);
}

void doFunction(int choice) // to call specified function as entered by user
{
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

    std::cout << "\n\nPress any key to continue...";
    getch(); // wait for a key
    system("cls"); // clear screen

    // again show options
    showOptions();
}

#endif