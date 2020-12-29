/*
1. HW2-CS1337-Kyle-Chan.cpp
2. Last changes made 2/16/20
3. Name: Kyle Chan
4. Purpose: Create a word searching program that takes a text file input
5. Class: CS1337.010
6. Change log:

    2/13/20:
        +Checking valid file input
        +Dimensions input routine
        +2D char vector for word search input routine
    2/14/20:
        +Adjust char vector after input routine
        +word retrieval routine
        +cursor system for word searching
    2/15/20:
        +Word searching capabilities
        +Correctly finds all possible words
        +Vector for words not found
    2/16/20:
        +Multiple occurrences option
        +OPTIONAL: additional word capability
        +OPTIONAL: additional word puzzle capability
7. Notes:
    -Ask user for name and location of a file to read
        -The file has comment lines that start with #, data lines, and blank lines
        -The first input is the dimensions of the matrix of words
        -The second input is the word array itself
        -The subsequent inputs are words to look for in the matrix
    -Search for words
        -Report whether or not a word/phrase is found within the matrix
            -Record the starting coords and the direction (N, NW, SE, etc.)
            -Search for each word one at a time
    -Provide fault-tolerance when trying to open file
    -Report only words that are found, their locations, and their directions
        -Shove all words not found into a vector of strings that will be displayed at the end
    -Report coords in human-speak (i.e. the matrix is reported to start at (1,1))
    -Check for length issues before searching in a given direction
    -Add a Bool value that controls whether you search for multiple or just single occurrences
    -OPTIONAL: Add interactive capability that asks user to enter additional words at the end
    -OPTIONAL: Add capability to advance to another word puzzle once you've finished with the current one

    -main() can either be at top or bottom
    -special features/techniques should be pointed out with //Special Features

    -Submit both the file and folder name like:
        HW2-CS1337-Kyle-Chan.zip
8. Comments:
*/


#include<iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string fileName;
int ROWS = 100, COLUMNS= 100; //placeholder number until the input file changes it


//SPECIAL FEATURE
//I used a vector here b/c I wanted to have a global vector instead of passing an array around every function (and I realized you can't pass 2D arrays without pointers very easily)
vector<vector<char> > wordMatrix(ROWS, vector<char> (COLUMNS)); //2D vector represented by a vector sized ROWS, with each element being its own vector sized COLUMNS
//dynamic size means I can change the vector size to save memory


vector<string> wordNotFound; //can be cleared later

//SPECIAL FEATURE
enum eDirection {W, NW, N, NE, E, SE, S, SW}; //enums are more visual in that I know what I'm working with opposed to just arbitrary numbers
eDirection dir;

bool singleOccurence;
bool restart = false;

bool openForReading(ifstream &infile,string fileName) {

    infile.open(fileName);

    if (infile.good()){ //then the file opened just fine
        return true;
    }
    else {
        perror("Can't open the specified input file");

        cout << "The file name used was: " << fileName << endl;
        cout << "Enter another file name to use (or type 'quit'): ";

        getline(cin,fileName);

        if (fileName != "quit") { //maybe check for QUIT too
            cout << "--- The new file name is: " << fileName << endl;

            //note the use of recursion below
            return openForReading(infile,fileName);
        }
        else {
            cout << "Quitting at user's request." << endl;
            return false;
        }
    }
} //openForReading

void skipAnyCommentLines(ifstream &infile) {
    string textLine;
    char ch;

    ch = infile.peek();

    while (ch == '#' || ch == '\n') {
        getline(infile,textLine);
        ch = infile.peek();
    }
    //when we leave, we're at a non-comment, non-blank line
} //skipAnyCommentLines

void getWordMatrix(ifstream &infile){

        for(int currRow = 0; currRow < ROWS; currRow++){
            if(infile.peek() == '\n'){//ignore erroneous newlines if present
                infile.ignore();
            }
            for(int currCol = 0; currCol < COLUMNS; currCol++){
                wordMatrix[currRow][currCol] = infile.get();
                //cout << "***wordMatrix[" << currRow << "][" << currCol << "] = " << wordMatrix[currRow][currCol] << endl;
            }
        }


}//getWordMatrix

void adjustWordMatrixVector(){

    //I guess this really isn't necessary, but it'll help later to use the size of the vector in determining word search capabilities

    wordMatrix.resize(ROWS);
    for (int i = 0; i < ROWS; i++){
        wordMatrix[i].resize(COLUMNS);
    }

    //resizing each "row" vector to "column" sizes

}//adjustWordMatrixVector

string getWord(ifstream &infile){

    string strLine;

    getline(infile, strLine);

    //remove all whitespace between words in a line
    strLine.erase(remove(strLine.begin(), strLine.end(), ' '), strLine.end());

    //cout << "***size of word taken: " << strLine.size() << endl;

    return strLine;
}// getWord

void convertStrChar(char arr[], string str){

    for (int i = 0; i < str.size(); i++){
        arr[i] = (char)str.at(i);
    }

}//convertStrChar
bool seekWordStart(int &cursRow, int &cursCol, char arr[]){

    for(cursRow; cursRow < ROWS; cursRow++){
        //cout << "***running cursRow loop" << endl;
        if(cursCol == COLUMNS) //if the end of a row is reached, reset the column cursor to the beginning (whilst incrementing row cursor)
            cursCol = 0;
        for(cursCol; cursCol < COLUMNS; cursCol++){
            //cout << "***Checking coords: " << cursCol << ", " << cursRow << endl;
            if(wordMatrix[cursRow][cursCol] == arr[0]){
                return true; //first letter found
            }
        }
    }

    return false;


}//seekWordStart

bool wordCheck(int cursRow, int cursCol, char arr[], int moveLR, int moveUD, int wordLength){//big brain energy function

    //cout << "***reached wordCheck!" << endl;
    for(int currLetter = 1; currLetter < wordLength; currLetter++){
        //cursor should increment on first loop b/c the first letter was already confirmed (i.e. start on second letter)
        cursCol += moveLR; //move cursor in the direction it is searching in
        cursRow += moveUD;

        //cout << "***current coords: " << cursCol << ", " << cursRow << endl;
        if(wordMatrix[cursRow][cursCol] != arr[currLetter]){
            return false;
        }

    }
    //cout << "***Full word found!" << endl;
    return true;

}//wordCheck


bool searchDirection(int cursRow, int cursCol, char arr[], int wordLength){

    //Moving down is increasing rows
    //Moving right is increasing columns


    switch(dir){

        case W:
            //cout << "***searching W" << endl;
            if(cursCol + 1< wordLength) //check for word search boundaries
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, -1, 0, wordLength);
            break;

        case NW:
            //cout << "***searching NW" << endl;
            if(cursCol + 1< wordLength || cursRow + 1< wordLength)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, -1, -1, wordLength);
            break;

        case N:
            //cout << "***searching N" << endl;
            if(cursRow + 1< wordLength)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, 0, -1, wordLength);
            break;

        case NE:
            //cout << "***searching NE" << endl;
            if(cursRow + 1< wordLength || (cursCol + wordLength) > COLUMNS)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, 1, -1, wordLength);
            break;
        case E:
            //cout << "***searching E" << endl;
            if((cursCol + wordLength) > COLUMNS)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, 1, 0, wordLength);
            break;

        case SE:
            //cout << "***searching SE" << endl;
            if((cursCol + wordLength) > COLUMNS || (cursRow + wordLength ) > ROWS)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, 1, 1, wordLength);
            break;

        case S:
            //cout << "***searching S" << endl;
            if((cursRow + wordLength) > ROWS)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, 0, 1, wordLength);
            break;

        case SW:
            //cout << "***searching SW" << endl;
            if((cursRow + wordLength) > ROWS || cursCol + 1 < wordLength)
                return false;
            else
                return wordCheck(cursRow, cursCol, arr, -1, 1, wordLength);
            break;
    }


}//seekWord

void printDirection(){

    switch(dir){

        case W:
            cout << "W)" << endl;
            break;
        case NW:
            cout << "NW)" << endl;
            break;
        case N:
            cout << "N)" << endl;
            break;
        case NE:
            cout << "NE)" << endl;
            break;
        case E:
            cout << "E)" << endl;
            break;
        case SE:
            cout << "SE)" << endl;
            break;
        case S:
            cout << "S)" << endl;
            break;
        case SW:
            cout << "SW)" <<endl;
            break;
    }

}
void wordRoutine(ifstream &infile, string userWord = ""){

    int cursRow = 0;
    int cursCol = 0;
    bool wordFound = false;
    string strLine;

    //get the word
    if(userWord == "") //if there is no user input for a word to search for, retrieve one from the file
        strLine = getWord(infile);
    else{
        strLine = userWord;
    }
    //convert the string word into a char array for seeking
    char phrase[strLine.size()];
    convertStrChar(phrase, strLine);

    //cout << "***converted string to char array is: ";
   /* for (int i = 0; i < strLine.size(); i++){
        cout << strLine.at(i);
    }
    cout << endl;
*/

    //search for it (return a bool)
    //report the bool to evaluate
    while(cursRow < ROWS && cursCol < COLUMNS ){
        //cout << "***cursor continuing at " << cursCol << ", " << cursRow << endl;
        if(seekWordStart(cursRow, cursCol, phrase)){
           // cout << "***First letter of " << strLine << " found  at " << cursCol << ", " << cursRow << endl;
            for (int dirInt = W; dirInt <= SW; dirInt++){ //cycle directions starting with W and ending with SW (max 8 loops)
                dir = static_cast<eDirection>(dirInt);
                if(searchDirection(cursRow, cursCol, phrase, strLine.size())){ //if false, cycle to next direction
                    cout << strLine << " found at " << cursRow + 1<< ", " << cursCol + 1<< ": (direction = ";
                    printDirection();
                    wordFound = true;
                    break;
                }
            }
            if(singleOccurence){
                if(wordFound)
                    break; //do not continue to search if word is already found
            }
        }
        if(cursCol + 1 != COLUMNS) //move cursor to next letter to prepare for next word search
            cursCol++;
        else{
            cursCol = 0;
            cursRow++;
        }


    }
    if(!wordFound){
        if(userWord == ""){
            //cout << "***" << strLine << " not detected in word search" << endl;
            //push_back strLine to wordNotFound
            wordNotFound.push_back(strLine + "\n");
        }
        else
            cout << userWord << " not detected in word search" << endl;
    }


}//wordRoutine


void drawWordSearch(){

    cout << "Nbr Rows: " << ROWS << ";    Nbr Cols: " << COLUMNS;

    for(int currRow = 0; currRow < ROWS; currRow++){
        cout << endl;
        for(int currCol = 0; currCol < COLUMNS; currCol++){
            cout << wordMatrix[currRow][currCol] << " "; //the space makes the output look more symmetrical / visually appealing
        }
    }

    cout << endl << endl;
} //drawWordSearch
void startMenu(){

    char userInput;
    bool validInput = true;

    do{
        cout << "Would you like to search for multiple occurrences of a word? Please enter Y / N: ";
        cin >> userInput;

        if (tolower(userInput) == 'y'){
            singleOccurence = false;
            validInput = true;
        }
        else if (tolower(userInput) == 'n'){
            singleOccurence = true;
            validInput = true;
        }
        else {
            validInput = false;
        }

    }while(!validInput);


}//startMenu
string convertToUpper(string userWord){

    string newStr = "";

    for(int i = 0; i < userWord.size(); i++){
        newStr += toupper(userWord.at(i));
    }

    return newStr;
}//converToUpper
void endMenu(ifstream &infile){ //SPECIAL FEATURE

    int userInput;
    bool validInput = false;
    string userWord;

    do{
        cout << "Choose one of the following:" << endl << "1. Search for additional words" << endl << "2. Search a different word puzzle" << endl << "3. Exit" << endl;
        cin >> userInput;

        switch(userInput){

            case 1:
                cout << "What word would you like to search for? ";
                cin >> userWord;
                wordRoutine(infile, convertToUpper(userWord));
                break; //validInput = false to make program return back to endMenu when word is searched for

            case 2:
                restart = true;
                validInput = true;
                break;

            case 3:
                restart = false;
                validInput = true;
                break;

        }

    }while(!validInput);


}//endMenu
int main(){

    ifstream infile;

    do{
        //get input file
        //check for a valid file opening
        cout << "Enter file name to use: ";
        cin >> fileName;

        if(openForReading(infile, fileName)){

            startMenu();

            skipAnyCommentLines(infile); //skip to dimensions
            //cursor starts at dimensions data line (FIRST INPUT)
            infile >> ROWS >> COLUMNS;
            // cout << "***inputted rows: " << ROWS << " | inputted columns: " << COLUMNS << endl;


            skipAnyCommentLines(infile); // skip to word search
            //cursor starts at char array
            getWordMatrix(infile);
            adjustWordMatrixVector();

            //write rows, columns, and word search to console
            drawWordSearch();

            skipAnyCommentLines(infile); //skip to words to search
            //cursor starts at words to search for
            while(!infile.eof()){
                //cout << "***running routine" << endl;
                wordRoutine(infile);
                skipAnyCommentLines(infile); // skip blank lines
            }

            cout << endl << "Words not found:" << endl;
            for(int i = 0; i < wordNotFound.size(); i++){
                cout << wordNotFound[i];
            }

            infile.close(); //close in the case another file is to be checked
            wordNotFound.clear(); //clear vector for subsequent runs

            endMenu(infile); //SPECIAL FEATURE

        }
    }while(restart);

    return 0;
}

//
