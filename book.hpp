// This header file consist of class 'Book' that will hold book information before it is wrote to file or after it is read from file. Class is necessary to hold book information since this information is written in binary file with fixed length for each record i.e. book

#ifndef BOOK_HPP
#define BOOK_HPP

// preprocessor directives
#include <string>
#include <sstream>
#include <iomanip>
// #include <exception>

class Book
{
public:
    // constructor provide default value for all attributes
    // it help to make object without providing autual data
    Book(int keyV = -1, std::string isbn = "", std::string name = "", std::string genre = "", int quantityV = 0)
        : key{keyV} {
            setQuantity(quantityV);

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
        length = length < 50 ? length : 49; // size must be one less then size of 'name'
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
        length = length < 15 ? length : 14; // size must be one less then size of 'genre'
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

    // for data member 'quantity'
    void setQuantity(int n)
    {
        if(n < 0) {
            throw std::invalid_argument{"book quantity cannot be less than zero"};
        }

        quantity = n;
        return;
    }
    int getQuantity() const
    {
        // this tell if book is available for issuing it to people
        return quantity;
    }
    void reduceOneQuantity()
    {
        --quantity;
    }
    void increaseOneQuantity()
    {
        ++quantity;
    }

    // to concatenate all data
    std::string getDetails() const
    {
        std::ostringstream output;
        output << std::setw(3) << getKey() << std::setw(50) << getName() << std::setw(18) << getIsbn() << std::setw(18) << getGenre() << std::setw(15) << getQuantity();

        return output.str(); // return as string
    }
private:
    int key; // unique key of book
    int quantity; // number of same book available

    // 'c-type strings' are used since it is fixed sized, and fixed size is necessary for writing records in binary file
    char isbn[14]; // isbn of book
    char name[50]; // name of book
    char genre[15]; // genre of book
};

#endif