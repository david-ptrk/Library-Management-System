#ifndef HEADING_HPP
#define HEADING_HPP

#include <iostream>
#include <fstream>
#include "encryption.hpp"

void newLibrarian(void);

void starting_instructions(void)
{
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "      Welcome to Library Management System      " << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::ifstream dataFile{"librarian.txt", std::ios::in};
    if(!dataFile) {
        newLibrarian();
    }
    else {
        std::string name, password;

        std::cout << "\nEnter your Name: ";
        getline(std::cin, name);
        std::cout << "Enter your Password: ";
        std::cin >> password;

        Password oldPerson{name, password};

        std::string thisData = oldPerson.getDetails();

        std::string fileRecord;
        getline(dataFile, fileRecord);

        if(fileRecord == thisData) {
            std::cout << "Access Granted" << std::endl;
        }
        else {
            std::cout << "Access Denied" << std:: endl;
        }
    }

    dataFile.close();
    return;
}

void newLibrarian(void)
{
    std::ofstream dataFile{"librarian.txt", std::ios::out};
    if(!dataFile) {
        std::cerr << "cannot create file";
        exit(EXIT_FAILURE);
    }

    std::string name, password;

    std::cout << "\nNew Librarian Record" << std::endl;
    std::cout << "Enter your Name: ";
    getline(std::cin, name);
    std::cout << "Enter new Password (only letters or digits): ";
    std::cin >> password;

    Password newPerson{name, password};
    dataFile << newPerson.getDetails() << std::endl;
    std::cout << "\nNew Record Created" << std::endl;

    dataFile.close();

    return;
}

#endif