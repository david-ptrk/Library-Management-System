#ifndef CONFIRMATION_HPP
#define CONFIRMATION_HPP

#include <iostream>
#include <fstream>
#include "encryption.hpp"

bool librarianLogin()
{
    std::ifstream dataFile{"librarian.txt", std::ios::in};
    if(!dataFile) {
        std::cerr << "file doesn't exists";
        exit(EXIT_FAILURE);
    }

    // reading librarian record form the file
    std::string fileRecord;
    getline(dataFile, fileRecord);

    std::string name, password;

    std::cout << "\nEnter your Name: ";
    // std::cin.ignore();
    getline(std::cin, name);
    std::cout << "Enter your Password: ";
    std::cin >> password;

    Password loginPerson{name, password};

    std::string thisData = loginPerson.getDetails();

    dataFile.close();

    if(fileRecord == thisData) {
        return true;
    }
    else {
        return false;
    }
}

#endif