// This header file consist of functions that can be selected by user in library. Each crossponds to a specific work as entered by user

#ifndef LIBRARYFUNCTIONS_HPP
#define LIBRARYFUNCTIONS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "book.hpp"
#include "librarianConfirmation.hpp"

// 1 - Add New Librarian
void addNewLibrarian()
{
    system("cls");

    std::cin.ignore();
    if(librarianLogin()) {
        std::string name, password;

        system("cls");
        std::cout << "Enter New Librarian Name: ";
        getline(std::cin, name);
        std::cout << "Enter new Password (only letters or digits): ";
        password = getPassword();

        Password newPerson{name, password};

        std::fstream file{"librarian.txt", std::ios::in | std::ios::out | std::ios::app};
        if(!file) {
            std::cerr << "librarian file doesn't open";
            exit(EXIT_FAILURE);
        }

        file << newPerson.getDetails() << '\n';
        std::cout << "\nLibrarian Added";
    }
    else {
        std::cout << "\nAccess Denied";
    }

    return;
}

// 2 - Add New Books
void addNewBooks()
{
    system("cls");

    std::cin.ignore();
    if(librarianLogin()) {
        std::fstream booksFile{"bookRecords.dat", std::ios::out | std::ios::in | std::ios::binary | std::ios::app};

        if(!booksFile) {
            std::cerr << "Cannot open file to add books";
            exit(EXIT_FAILURE);
        }

        int key;
        std::string isbn;
        std::string name;
        std::string genre;
        bool available;

        int next;

        do
        {
            system("cls");

            //deciding key
            booksFile.seekg(0, std::ios::end);
            int fileSize = booksFile.tellg();
            int numBooks = fileSize / sizeof(Book);
            key = numBooks > 0 ? numBooks : 0;

            std::cout << "Enter ISBN: ";
            std::cin >> isbn;
            std::cout << "Enter Book Name: ";
            std::cin.ignore();
            getline(std::cin, name);
            std::cout << "Enter Book Genre: ";
            std::cin >> genre;

            available = true;

            Book newBookRecord{key, isbn, name, genre, available};

            booksFile.write(reinterpret_cast<const char *>(&newBookRecord), sizeof(Book));

            std::cout << "Book Added" << std::endl;

            std::cout << "\nAdd another book(1 or 0): ";
            std::cin >> next;
        }while(next == 1);
    }
    else {
        std::cout << "\nAccess Denied";
    }

    return;
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