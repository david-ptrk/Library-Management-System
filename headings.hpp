#ifndef HEADING_HPP
#define HEADING_HPP

#include <iostream>
#include <fstream>
#include <conio.h>
#include "encryption.hpp"
#include "libraryFunctions.hpp"

void startingInstructions(void); // welcome page of library
void newLibrarian(void); // function to create new Librarian
void showOptions(void); // navigation options of library
void doFunction(int); // call proper function as specified by user

void startinginstructions(void)
{
    // welcome display
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "      Welcome to Library Management System      " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    // try to open librarian.txt
    std::ifstream dataFile{"librarian.txt", std::ios::in};
    if(!dataFile) { // if file doesn't exist, no librarian exit
        newLibrarian(); // create new librarian
    }
    else { // if file exist, at least one librarian exist
        std::string name, password; 

        std::cout << "\nLibrarian Login\n"; // login
        std::cout << "\nEnter your Name: "; 
        getline(std::cin, name);
        std::cout << "Enter your Password: ";
        std::cin >> password;

        // using Password class so that password will be save in encryted form
        Password oldPerson{name, password};

        // getting librarian record from object i.e. this login information
        std::string thisData = oldPerson.getDetails();

        // reading librarian record form the file
        std::string fileRecord;
        getline(dataFile, fileRecord);

        // if librarian credential match, grant him access
        if(fileRecord == thisData) {
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

    std::cout << "\nLibrarian Signup\n";
    std::cout << "\nEnter your Name: ";
    getline(std::cin, name);
    std::cout << "Enter new Password (only letters or digits): ";
    std::cin >> password;

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
    std::cout << "Librarian's Access:\n";
    std::cout << "1 - Add Another Librarian" << '\t' << "2 - Add New Books" << '\n' << "3 - Remove Old Books" << "\t\t" << "4 - Check Student Details" << std::endl;

    std::cout << "\nPublic's Access:\n";
    std::cout << "5 - Borrow A Book" << "\t\t" << "6 - Return A Book" << '\n' << "7 - Renew Return Date" << "\t\t" << "8 - Search A Book" << '\n' << "9 - Exit Library\n" << std::endl;

    int num;
    do
    {
        std::cout << "? ";
        std::cin >> num;
    }while(num < 1 || num > 9);

    if(num != 9) {
        doFunction(num);
    }
    
    std::cout << "\nThankYou!" << std::endl;
    exit(EXIT_SUCCESS);
}

void doFunction(int choice)
{
    switch(choice)
    {
        case 1: // new librarian

            break;
        case 2: // new books

            break;
        case 3: // remove books

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

            break;
        default:
            // control should not reach here
            std::cerr << "control shoulf not reach here";
            break;
    }

    getch();
    system("cls");
    showOptions();
}

#endif