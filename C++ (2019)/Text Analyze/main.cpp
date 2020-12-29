/*GRADEBOOK #8
Prompts user to enter a file name to read. It will then display the number of words, long words (>=7 characters), and the percentage
of long words of total words. There will be error messages for empty and nonexistent files.
*/


#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

int readFile(string fileName);

int main() {

    string fileName;

    cout << "Enter the name of the file to be read." << endl;
    cin >> fileName;

    readFile(fileName);

    return 0;

}


//Takes in the name of the file and displays the number of words, long words, and the percentage of long words of total words
//in the file. If the file is empty, the function will output that it was empty. If the file with the name specified cannot be opened,
//and error message will be outputted.

int readFile(string fileName){

    ifstream inFile;
    string term;
    int wordCount = 0,
          bigWordCount = 0;
    double percentage;
    bool notEmpty = true;

    inFile.open(fileName);

    if(!inFile.fail()){

        while(inFile){
                inFile >> term;

                if(term != ""){
                    if(ispunct(term[0])){
                    wordCount--;
                    }
                    if(ispunct(term[term.length() -1])){
                        term.erase(term.length() -1);
                    }
                    if(term.length() >= 7){
                        bigWordCount++;
                    }
                    else{
                        wordCount++;
                    }
                }
                else{
                cout << endl << fileName + " was empty." << endl;
                notEmpty = false;
                }


        }
            wordCount--;

            percentage = 100 * (double(bigWordCount) / double(wordCount + bigWordCount));

            if(notEmpty){
                cout << endl << wordCount + bigWordCount << " words were found." << endl
                    << bigWordCount << " long words were found." << endl
                    << fixed << setprecision(2) << percentage << "% of the  words were considered long." << endl;
            }
    }
    else{
        cout << "Unable to open said file, or file does not exist." << endl;
    }
}








