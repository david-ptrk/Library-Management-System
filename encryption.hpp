// This header file consist of class Password. This class is used to encrpyt user password. As an object of class Password is instantiated, the password is already stored in encrypted form.

#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

// preprocessor directives
#include <string>
#include <cctype>
#include <sstream>
#include <exception>

// class will encrypt the password entered by librarian
// if return name and encryted password concatenated
class Password
{
public:
    // contructor
    Password(std::string name, std::string password) // cannot instantiate object without name and password supplied
        : librarianName{name} {
            setPassword(password); // call 'setPassword' to encrypt it
        }

    // setPassword can be accessed outside of class
    void setPassword(std::string value)
    {
        encryptPassword(value); // call 'encryptPassword' to encrypt the password
        this->password = value; // store in data member 'password'

        return; // return control
    }

    // to return encryted password attached with user name
    std::string getDetails(void) const
    {
        std::ostringstream output;
        output << librarianName << password; // concatenate both

        return output.str(); // return them as string
    }
private:
    // data member to store password
    // password will be store in encrypted form only
    std::string password;

    // data member to store name
    std::string librarianName;

    // shift key
    // it is used to encrypt the password
    const int SHIFT_VALUE{7};

    // utility functions
    void encryptPassword(std::string& value) // function to shift every letter in password
    {
        // loop to interate over every character of 'value' i.e. password entered by user
        for(char& element : value)
        {
            // if character is lower-case
            if(islower(element)) {
                shiftCharacter(element, 'a', 'z'); // to shift character in range a-z
            }
            // if character is upper-case
            else if(isupper(element)) {
                shiftCharacter(element, 'A', 'Z'); // to shift character in range A-Z
            }
            // if character is digit
            else if(isdigit(element)) {
                shiftCharacter(element, '0', '9'); // to shift character in range 0-9
            }
            // no other character is allowed
            else {
                throw std::runtime_error{"password must be between a-z, A-Z, 0-9"}; // throw an exception
            }
        }

        return; // return control
    }

    void shiftCharacter(char& character, char start, char end) // to shift each individual letter by shift key
    {
        for(int i{1}; i <= SHIFT_VALUE; ++i)
        {
            ++character; // increment individual letter

            // if letter is greater than its range 
            if(character > end) { 
                character = start; // move to start of range
            }
        }

        return; // return control
    }
};

#endif