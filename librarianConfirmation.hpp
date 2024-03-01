#ifndef CONFIRMATION_HPP
#define CONFIRMATION_HPP

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "encryption.hpp"

enum IN
{
    IN_BACK = 8,
    IN_RET = 13
};

std::string getPassword(char sp = '*')
{
    std::string password = "";
    char ch_ipt;

    while(true)
    {
        ch_ipt = getch();

        if(ch_ipt == IN::IN_RET) {
            std::cout << std::endl;
            return password;
        }
        else if((ch_ipt == IN::IN_BACK) && (password.length() != 0)) {
            password.pop_back();
            std::cout << "\b \b";

            continue;
        }
        else if((ch_ipt == IN::IN_BACK) && (password.length() == 0)) {
            continue;
        }

        password.push_back(ch_ipt);
        std::cout << sp;
    }
}

bool librarianLogin()
{
    std::ifstream dataFile{"librarian.txt", std::ios::in};
    if(!dataFile) {
        std::cerr << "file doesn't exists";
        exit(EXIT_FAILURE);
    }

    std::string name, password;

    std::cout << "\nEnter your Name: ";
    getline(std::cin, name);
    std::cout << "Enter your Password: ";
    password = getPassword();

    Password loginPerson{name, password};
    std::string thisData = loginPerson.getDetails();

    std::string fileRecord;
    while(getline(dataFile, fileRecord))
    {
        if(fileRecord == thisData) {
            dataFile.close();
            return true;
        }
    }
    
    dataFile.close();
    return false;
}

#endif