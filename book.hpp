// This header file consist of class 'Book' that will hold book information before it is wrote to file or after it is read from file. Class is necessary to hold book information since this information is written in binary file with fixed length for each record i.e. book

#ifndef BOOK_HPP
#define BOOK_HPP

// preprocessor directives
#include <string>
#include <sstream>

class Book
{
public:
    // constructor provide default value for all attributes
    // it help to make object without providing autual data
    Book(int keyV = -1, std::string isbn = "", std::string name = "", std::string genre = "", bool availableV = false)
        : key{keyV}, available{availableV} {
        // functions must be call since 'string' must be converted to 'C-typed string'
        setIsbn(isbn);
        setName(name);
        setGenre(genre);
    }

    // for data memeber 'key'
    void setKey(int num)
    {
        this->key = num; // store key
    }
    int getKey() const
    {
        return key; // return key
    }

    // for data member 'name'
    void setName(std::string bookName)
    {
        size_t length = bookName.size(); // get size of string
        length = length < 100 ? length : 99; // size must be one less then size of 'name'
        bookName.copy(name, length); // copy characters from string to 'name'
        name[length] = '\0'; // add terminating letter at end of 'name'
    }
    std::string getName() const
    {
        std::string bookName{name}; // convert 'name' array to string
        return bookName; // return as string
    }

    // for data member 'genre'
    void setGenre(std::string bookGenre)
    {
        size_t length = bookGenre.size(); // get size of string
        length = length < 30 ? length : 29; // size must be one less then size of 'genre'
        bookGenre.copy(genre, length); // copy characters from string to 'genre'
        genre[length] = '\0'; // add terminating letter at end of 'genre'
    }
    std::string getGenre() const
    {
        std::string bookGenre{genre}; // convert 'genre' array to string
        return bookGenre; // return as string
    }

    // for data member 'isbn'
    void setIsbn(std::string isbnum)
    {
        size_t length = isbnum.size(); // get size of string
        length = length < 14 ? length : 13; // size must be one less then size of 'isbn'
        isbnum.copy(isbn, length); // copy characters from string to 'isbn'
        isbn[length] = '\0'; // add terminating letter at end of 'isbn'
    }
    std::string getIsbn() const
    {
        std::string bookIsbn{isbn}; // convert 'isbn' array to string
        return bookIsbn; // return as string
    }

    // for data member 'available'
    bool getAvailable() const
    {
        // this tell if book is available for issuing it to people
        return available;
    }

    // to concatenate all data
    std::string getDetails() const
    {
        std::ostringstream output;
        output << getKey() << ' ' << getName() << ' ' << getIsbn() << ' ' << getGenre() << ' ' << getAvailable(); // concatenate all member with spaces in between

        return output.str(); // return as string
    }
private:
    int key; // unique key of book
    bool available; // availability of book

    // 'c-type strings' are used since it is fixed sized, and fixed size is necessary for writing records in binary file
    char isbn[14]; // isbn of book
    char name[100]; // name of book
    char genre[30]; // genre of book
};

#endif