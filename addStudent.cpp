// Adding Students in file. This file is not to be used by librarian. This is just a test program to add students. Adding students is the working of admin

// preprocessor directives
#include <iostream>
#include <fstream>
#include ".\shared\student.hpp" // definition of class 'Student'

using namespace std; //using directive

//main start here
int main()
{
    // opening students records file. if file doesn't exist create a new file
    ofstream outputFile{"studentRecords.dat", ios::out | ios::binary | ios::app};
    if(!outputFile) {
        cerr << "cannot open file";
        exit(EXIT_FAILURE);
    }

    Student student; // object of 'Student' class
    int n; // using in loop's condition

    cout << "Enter student's details:\n"; // prompt to enter details
    while(cin >> student) // input details in object of 'Student'
    {
        cout << student; // display the details on console
        outputFile.write(reinterpret_cast<const char *>(&student), sizeof(Student)); // write the details in file as a record
        cout << "Done\n";

        cout << "\n1 or 0 ?"; // prompt to ask for more students
        cin >> n;
        if(n == 0) { // if no i.e '0'
            break; // break through the loop
        }
        
        cout << "\nEnter student's details:\n"; // else prompt to add next student's details
    }

    outputFile.close(); // close the file

    return 0; //return main value
}
//main ends