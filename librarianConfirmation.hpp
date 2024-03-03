// This header file consist of functions that will be used at time of librarian login. The functions 'librarianLogin' is called anywhere we went to login librarian. This file consist of all functionalities it needs except password encryption

#ifndef CONFIRMATION_HPP
#define CONFIRMATION_HPP

// preprocessor directives
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "encryption.hpp"

enum IN
{
    IN_BACK = 8, // ASCII value for Backspace
    IN_RET = 13 // ASCII value for Enter/Return
};

// return the password entered by user
// hide password typed by character supplied in 'sp'
std::string getPassword(char sp = '*')
{
    std::string password = ""; // to store password
    char ch_ipt; // to store character as it is typed

    // loop continues until Enter key is pressed
    while(true)
    {
        ch_ipt = getch(); // input a character

        // if Enter is pressed
        if(ch_ipt == IN::IN_RET) {
            std::cout << std::endl; // print a newline
            return password; // return password
        }
        // if Backspace is pressed and password is not empty
        else if((ch_ipt == IN::IN_BACK) && (password.length() != 0)) { 
            password.pop_back(); // remove character from end of string
            std::cout << "\b \b"; // update console by backspace

            continue; // move to next iteration
        }
        // if Backspace is pressed and password is empty
        else if((ch_ipt == IN::IN_BACK) && (password.length() == 0)) {
            continue; // do nothing move to next iteration
        }

        // if any other key is pressed
        password.push_back(ch_ipt); // push it onto string
        std::cout << sp; // and display 'sp' character on screen in place of charcter typed
    }
}

// call this function simply when you want to login a librarian
// all input and checking is performed by it
// return bool value to indicate if login was successful or not
bool librarianLogin()
{
    std::ifstream dataFile{"librarian.txt", std::ios::in}; // open librarian file
    // if file doesn't exist
    if(!dataFile) {
        std::cerr << "file doesn't exists";
        exit(EXIT_FAILURE); // exit since no librarian exist, exist is necessary because new librarian is not made as startup of application
    }

    std::string name, password; // to hold user typed data

    std::cout << "\nEnter your Name: "; // prompt to enter name
    getline(std::cin, name); // used 'getline' because name may consist of space
    std::cout << "Enter your Password: "; // prompt to enter password
    password = getPassword(); // call 'getPassword' so it can hide typed password

    Password loginPerson{name, password}; // creating object of Password, because this class can automatically encrypt the password
    std::string thisData = loginPerson.getDetails(); // get concatenated name and password(encrypted) 

    std::string fileRecord; // to hold librarian data from file

    // loop until all lines of file
    while(getline(dataFile, fileRecord)) // get a line from file, since name and password (of one librarian) are stored in one line
    {
        // if it match with typed data
        if(fileRecord == thisData) { 
            dataFile.close(); // close the file
            return true; // and return true, since data matched and authentication is done
        }
    }
    // if the loop ends and not one record in file matched with typed data

    dataFile.close(); // close the file
    return false; // and return false, since no data matched
}

#endif