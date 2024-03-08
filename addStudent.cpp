// Adding Students in file. This file is not to be used by librarian. This is just a test program to add students. Adding students is the working of admin

#include <iostream> //preprocessor directives
#include <fstream>
#include ".\shared\student.hpp"
using namespace std; //using directive

//main start here
int main()
{
    ofstream outputFile{"studentRecords.dat", ios::out | ios::binary | ios::app};
    if(!outputFile) {
        cerr << "cannot open file";
        exit(EXIT_FAILURE);
    }

    Student student;
    int n;

    cout << "Enter student's details:\n";
    while(cin >> student)
    {
        cout << student;
        outputFile.write(reinterpret_cast<const char *>(&student), sizeof(Student));
        cout << "Done\n";

        cout << "\n1 or 0 ?";
        cin >> n;
        if(n == 0) {
            break;
        }
        
        cout << "\nEnter student's details:\n";
    }

    outputFile.close();

    return 0; //return main value
}
//main ends