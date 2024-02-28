#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <string>
#include <cctype>
#include <sstream>

// class will encrypt the password entered by librarian
// password will be store on a sequential file along with librarian data
class Password
{
public:
    // contructor
    Password(std::string name, std::string password)
        : librarianName{name} {
            setPassword(password);
        }

    // setPassword to call encryption it is only member function accessed outside of class
    void setPassword(std::string value)
    {
        encryptPassword(value); // encrypt the password
        this->password = value; // store in data member

        return;
    }

    std::string getDetails(void) const
    {
        std::ostringstream output;
        output << librarianName << password;

        return output.str();
    }
private:
    // data member to store password
    // password will be store in encrypted form only
    std::string password;

    std::string librarianName;
    const int SHIFT_VALUE{7}; // shift key

    // utility functions

    void encryptPassword(std::string& value) // function to shift every letter in password
    {
        for(char& element : value)
        {
            if(islower(element)) {
                shiftCharacter(element, 'a', 'z'); // for lower-case letter
            }
            else if(isupper(element)) {
                shiftCharacter(element, 'A', 'Z'); // for upper-case letter
            }
            else if(isdigit(element)) {
                shiftCharacter(element, '0', '9'); // for digit in password
            }
        }

        return;
    }

    void shiftCharacter(char& character, char start, char end) // to shift individual letter by shift key
    {
        for(int i{1}; i <= SHIFT_VALUE; ++i)
        {
            ++character; // increment individual letter

            // if letter is greater than its range 
            if(character > end) { 
                character = start; // move to start of range
            }
        }

        return;
    }
};

#endif