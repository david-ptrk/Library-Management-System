// Adding Teachers in file. This file is not to be used by librarian. This is just a test program to add teachers. Adding teachers is the working of admin

#include <iostream> //preprocessor directives
#include <fstream>
#include "utilitys.hpp" // defintion of class 'MyTeacher'

using namespace std; //using directive

//main start here
int main()
{
    // opening teacher's records file. if file doesn't exist create new file
    ofstream outputFile{"teacherRecords.dat", ios::out | ios::binary | ios::app};
    if(!outputFile) {
        cerr << "cannot open file";
        exit(EXIT_FAILURE);
    }

    MyTeacher teacher; // object of class 'MyTeacher'
    int n;

    cout << "Enter teacher's details:\n"; // prompt to enter teacher's details
    while(cin >> teacher) // input in object
    {
        cout << teacher; // display on console
        outputFile.write(reinterpret_cast<const char *>(&teacher), sizeof(MyTeacher)); // write in binary file as record
        cout << "Done\n";

        cout << "\n1 or 0 ?"; // for more teacher's details
        if(n == 0) { // if no i.e. '0'
            break; // break through the loop
        }
        
        cout << "\nEnter teacher's details:\n"; // else prompt to enter next teacher's details
    }

    outputFile.close(); // close the file

    return 0; //return main value
}
//main ends