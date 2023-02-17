/*
-----------------------------------------------------------------------------------
    Project 1 - DNA Profiling

    Course: CS 251, Fall 2022.
    System: Mac using Visual Studio Code
    Author: Pratik Patel
    UIN: 669224629

 --> Ourvector Analysis:
    Created an app that matches the DNA from the file given by user and if there
    is a match, display the person's name from whoever the DNA matches too.
    A total of four ourvector vectors created through the structural of the
    program. Each of them associated and designed to do a specific task as
    required.
    1. ourvector <string> &fileDatabaseVec, this is a string vector accepts all of
    the data read through the file and stored in this vector, basically it stores
    all of the Database from the file given from user.
    2. ourvector <char> &fileDNAVec, this is a character vector that stores the DNA
    of the given user file, and displays whenever the command demands
    3. ourvector <char> titleVec, this is also a character vector that has only the
    title of any Database file given, the reason I have to create this vector is
    because the Database vector display should not display the title of the vector
    and basically I could not find the way to eliminate the title in DB vector
    4. ourvector <int> longestConsecutive, this is an integer vector that stores
    the longest consecutive STRs, and later use them for search milestone to
    detect the DNA matched person.
    -> All of the variables created in the program were needed to store some temporary
    or referenced variables that reflect back into whatever the function is passed.
    counting_STRs() is the function where I needed to keep track of so many things
    at once that forces me to create few variables, each variable's job is to hold
    some specific item/element so that I can use them in ahead of the program.

    -> The total number of vectors created for the member function _stats at the
    end of the app, # of vectors created:   5, this are the total number of vectors 
    created, includes DNA, DB, longestCons., title, and index vectors. 
    The # of elements inserted: 252, these are the total amount of each DNA, title,
    DB, etc elements are inserted in variety of different vectors. 
    The # of elements accessed: 2013, this number represents the number of times 
    the program accessed the elements in-order to use or display them through the 
    procedure of the program.
    The vectors are created at the following lines:
    line 224, 296, 297, 298, 299. 

-----------------------------------------------------------------------------------
*/

#include "ourvector.h"
#include <fstream>
#include <sstream>

using namespace std;

//-----------------------------------------------------------------------------------
// display_Title() accepts no parameters and prints the title of the app
void display_Title() {
    cout << "Welcome to the DNA Profiling Application." << endl;
} // end of display_Title()


//-----------------------------------------------------------------------------------
// display_Database() accepts the Database vector and prints it out
void display_Database(ourvector<string> &displayVec) {
    if (displayVec.size() > 0)
    {
        cout << "Database loaded:" << endl;
        // nested loop that checks and replace the commas by spaces
        for (int i = 0; i < displayVec.size(); i++) {
            for (int j = 0; j < displayVec.at(i).size(); j++) {
                if (displayVec[i][j] == ',') {
                    cout << " ";
                } 
                else {
                    cout << displayVec[i][j];
                }
            }
            cout << endl;
        } // end nested for() loop
    }
    else {
        cout << "No database loaded.";
    }
} // end of display_Database()


//-----------------------------------------------------------------------------------
// display_DNA() accepts the DNA vector and prints it out
void display_DNA(ourvector<char> &displayVec) {
    // prints the vector items as long as the size is > 0
    if (displayVec.size() > 0) {
        cout << "\nDNA loaded:" << endl;
        for (int i = 0; i < displayVec.size() - 1; ++i) {
            cout << displayVec[i];
        }
    }
    else {
        cout << "\nNo DNA loaded.\n";
    }
} // end of display_DNA()


//-----------------------------------------------------------------------------------
// display_Process() accepts title vector and longest consecutive strike vectors and
// prints out whether or not the DNA was processed
void display_Process(ourvector<char> &titleVec, ourvector<string> longestConsecutive) {
    int min = 0;
    if (longestConsecutive.size() > 0) {
        cout << "\nDNA processed, STR counts:\n";
        // loop through to check the element is comma or endline, displays the long.consecutive
        for (int i = 5; i < titleVec.size(); i++) {
            // cout << titleVec[i] << endl;
            if (titleVec[i] != ',' && titleVec[i] != '\n') {
                cout << titleVec[i];
            }
            else {
                cout << ": ";
                if (min < longestConsecutive.size()) {
                    cout << longestConsecutive[min] << endl;
                    min++;
                }
            }
        } // end for()
        cout << ": " << longestConsecutive[longestConsecutive.size() - 1] << endl;
    } // end main-if() statement
    else {
        cout << "\nNo DNA has been processed.\n";
    }
} // end of display_Process()


//-----------------------------------------------------------------------------------
// reading_Database_Into_Vec() accepts DB and title Vector with filename and reads the file
void reading_Database_Into_Vec(string filename, ourvector<string> &fileDatabaseVec, ourvector<char> &titleVec) {
    // reading a file and storing into a vector
    string character;
    string line;
    ifstream myFile(filename);

    if (myFile.is_open()) {
        // store the first line of the file, known as title
        getline(myFile, line, '\n');
        for (int i = 0; i < line.size(); i++) {
            titleVec.push_back(line[i]);
        }
        // push_back the rest of the file into a vector
        while (getline(myFile, line, '\n')) {
            fileDatabaseVec.push_back(line);
        } // end of while() loop
        myFile.close(); // close the file
    } // end mian-if() statement
    // prints when the file is unable to locate/open successfully
    else {
        cout << "Error: unable to open '" << filename << "'" << endl;
    }
} // end of reading_Database_Into_Vec()


//-----------------------------------------------------------------------------------
// reading_Database_Into_Vec() accepts only DNA vector and filename to read the file
// and store the DNA into DNA vector
void reading_DNA_Into_Vec(string filename, ourvector<char> &fileDNAVec) {
    // reading a file and storing into a DNA vector
    char character;
    ifstream myFile(filename);
    if (myFile.is_open()) {
        while (!myFile.eof()) {
            myFile.get(character);
            fileDNAVec.push_back(character);
        } // end of while() loop
    }
    else {
        cout << "Error: unable to open '" << filename << "'" << endl;
    }
} // end of reading_Database_Into_Vec()


//-----------------------------------------------------------------------------------
// counting_STRs accepts DNA, title and long.consecuitve vectors and two int variables
// algorithm that finds the longest consecutive word
void counting_STRs(ourvector<char> &fileDNAVec, ourvector<char> titleVec, int startIndex, int endIndex, ourvector<string> &longestConsecutive) {
    int index = startIndex + 1;
    int strFound = 0;
    int longestCons = 0;
    int temp;

    // loop through the DNA vector and find if the STRs exist in the DNA
    // if so, keep finding and see what's the longest consecutive number of time
    // it goes through DNA and match the STRs
    for (int i = 0; i < fileDNAVec.size(); i++) {
        // compare each element of the DNA to the first element of the STRs
        if (fileDNAVec.at(i) == titleVec[index]) {
            if (index == startIndex + 1) {
                temp = i;
            }
            index++;
        }
        // otherwise, if the above statement isn't ture, then initialize to the next element
        else {
            if (index != startIndex + 1) {
                i = temp;
            }
            index = startIndex + 1;
            strFound = 0;
        } // end of if-else() statement

        // compare if the STRs first element is the end of the STR
        if (index == endIndex) {
            strFound++;
            index = startIndex + 1;
            if (strFound >= longestCons) {
                longestCons = strFound;
            }
        }
    } // end for() loop
    longestConsecutive.push_back(to_string(longestCons));
} // end of counting_STRs()


//-----------------------------------------------------------------------------------
// Process_DNA() accepts DNA, title and long.consecutive vectors and process the STRs into DNA
// as per user's request to look up the DNA that matches with the longest consecutive times
void process_DNA(ourvector<char> &fileDNAVec, ourvector<char> &titleVec, ourvector<string> &longestConsecutive) {
    ourvector<int> indexVec;
    // loop through the title vector and whenever ther is comma,
    // push_back each element index into the index vector
    for (int i = 0; i < titleVec.size(); i++) {
        if (titleVec[i] == ',') {
            indexVec.push_back(i);
        }
    }
    // push back the size of the title vector into the index vector
    indexVec.push_back(titleVec.size());
    for (int j = 0; j < indexVec.size() - 1; j++) {
        // calling an above counting_STRs() that sends three vectors and two parameters for algorithms
        counting_STRs(fileDNAVec, titleVec, indexVec[j], indexVec[j + 1], longestConsecutive);
    }
} // end of process_DNA()


//-----------------------------------------------------------------------------------
// search_DNA() accepts Database and long.consecutive vector and process the
// which DNA corresponds to whom from the file, display their name
void search_DNA(ourvector<string> fileDatabaseVec, ourvector<string> longestConsecutive) {
    string tempVar;
    ourvector<string> personsNames, foundedPerson;
    ourvector<string> num;

    // load_db small.txt load_dna 1.txt process display search
    for (int i = 0; i < fileDatabaseVec.size(); i++)
    {
        // using the stringstream to check the string
        // stores that into new vector named personNames
        stringstream ss(fileDatabaseVec[i]);
        getline(ss, fileDatabaseVec[i], ',');
        personsNames.push_back(fileDatabaseVec[i]);

        getline(ss, fileDatabaseVec[i], '\n');
        num.push_back(fileDatabaseVec[i] + ',');
    } // end for() loop
    
    // below each for loops dedicated to do its own functional
    // job as provided, it loops through and push_back or append
    // the required elemts in the above mentioned vectors
    for (int j = 0; j < longestConsecutive.size(); j++) {
        tempVar.append(longestConsecutive[j] + ',');
    }
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == tempVar) {
            foundedPerson.push_back(personsNames[i]);
        }
    }
    // as long as foundedPerson()'s size is >0 it will display the founded match
    if (foundedPerson.size() <= 0) {
        cout << "Not found in database." << endl;
        return;
    }
    else {
        cout << "Found in database! DNA matches: ";
        for (int i = 0; i < foundedPerson.size(); i++) {
            cout << foundedPerson[i];
        }
    }
    cout << endl;

} // end of search_DNA()


//-----------------------------------------------------------------------------------
int main() {

    // variables
    string userCommand, filename;

    // all created vectors...
    ourvector<char> titleVec;
    ourvector<string> fileDatabaseVec;
    ourvector<char> fileDNAVec;
    ourvector<string> longestConsecutive;
    longestConsecutive.clear();
    display_Title();

    // do-while() loop that atleast runs once and associate the
    // user command to their appropriate function
    do {
        cout << "Enter command or # to exit: ";
        cin >> userCommand;

        if (userCommand == "load_db") {
            cin >> filename;
            cout << "Loading database..." << endl;
            fileDatabaseVec.clear();
            reading_Database_Into_Vec(filename, fileDatabaseVec, titleVec);
        }

        if (userCommand == "load_dna") {
            cin >> filename;
            cout << "Loading DNA..." << endl;
            fileDNAVec.clear();
            reading_DNA_Into_Vec(filename, fileDNAVec);
        }

        if (userCommand == "process") {
            cout << "Processing DNA..." << endl;
            process_DNA(fileDNAVec, titleVec, longestConsecutive);
        }

        if (userCommand == "search") {
            cout << "Searching database..." << endl;
            search_DNA(fileDatabaseVec, longestConsecutive);
        }

        if (userCommand == "display") {
            display_Database(fileDatabaseVec);
            display_DNA(fileDNAVec);
            display_Process(titleVec, longestConsecutive);
        }

    } while (userCommand != "#");
    // end of while() loop

    return 0;
} // end of main()