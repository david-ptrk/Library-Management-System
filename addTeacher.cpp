// Adding Teachers in file. This file is not to be used by librarian. This is just a test program to add teachers. Adding teachers is the working of admin

#include <iostream> //preprocessor directives
#include <fstream>
#include "utilitys.hpp"
using namespace std; //using directive

//main start here
int main()
{
    ofstream outputFile{"teacherRecords.dat", ios::out | ios::binary | ios::app};
    if(!outputFile) {
        cerr << "cannot open file";
        exit(EXIT_FAILURE);
    }

    MyTeacher teacher;
    int n;

    cout << "Enter teacher's details:\n";
    while(cin >> teacher)
    {
        cout << teacher;
        outputFile.write(reinterpret_cast<const char *>(&teacher), sizeof(MyTeacher));
        cout << "Done\n";

        cout << "\n1 or 0 ?";
        cin >> n;
        if(n == 0) {
            break;
        }
        
        cout << "\nEnter teacher's details:\n";
    }

    outputFile.close();

    return 0; //return main value
}
//main ends