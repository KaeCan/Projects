/*GRADEBOOK #8
Program accepts and validates an input value, looking for an idNumber and testchoices (two strings per line)
It also prompts the user to create a 10 question long key to compare the student answers to.
Then, scores, marks, and statistics will be outputted into a separate output file.

*/


#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void getKey(char [], const int elems);

bool getTestData(ifstream&, string& idNumber, char [], const int questions);

string arrayToString(char [], const int letters);

void writeScore(ofstream&, char [], char[], string idNumber, double& sumScore, string studentTestChoices);

void stringToArray(char array[], string str, const int letters);




int main() {

    string inputTests, outputTests, currentIDNumber, testChoices;
    const int questions = 10;
    char keyArray[questions];
    char stuArray[questions];
    double sumScore = 0.0;
    int testCount = 0;

    cout << "Enter the name of the file that contains the examinations data: ";
    cin >> inputTests;

    ifstream inFile;
    inFile.open(inputTests);

    cout << "Enter the name of the file where you want the results stored: ";
    cin >> outputTests;

    ofstream outFile;
    outFile.open(outputTests);

    if(!inFile.fail()){

        if(!inFile.eof()){

            getKey(keyArray, questions);

            cout << endl << "Processing....." << endl;

            string keyString = arrayToString(keyArray, questions);

            outFile << setw(35) << right << "KEY: " << keyString << endl;

            while(!inFile.eof()){

                inFile >> currentIDNumber >> testChoices;

                if(!inFile.eof()){

                    stringToArray(stuArray, testChoices, questions);

                    if(getTestData(inFile, currentIDNumber, stuArray, questions)){

                        //write to output file
                        writeScore(outFile, keyArray, stuArray, currentIDNumber, sumScore, testChoices);
                        testCount++;

                    }

                }

            }

            cout << endl << testCount << " tests graded. Results can be found in " << outputTests << endl;

            outFile << setprecision(1) << fixed;
            outFile << endl << endl << "RESULTS:" << endl
                        << setw(8) << right << "Test count = "  << testCount << " Average = " << sumScore / double(testCount);

            outFile.close();
            inFile.close();
        }
        else{
            cout << endl << "Processing." << endl << inputTests + " was empty." << endl;

        }
    }
    else{
        cout << endl << "Error, unable to open file " + inputTests << endl;
    }

    return 0;

}

//Accepts the keyArray from main and prompts user to fill out the 10 question answer key
void getKey(char keyArray[], const int elems){

    char elemAns;

    for(int i = 1; i <= elems; i++){

        cout << "Enter the answer to question #" << i << ": ";
        cin >>  elemAns;

        elemAns = toupper(elemAns);

        if(elemAns == 'A' || elemAns == 'B' || elemAns == 'C' || elemAns == 'D' || elemAns == 'E' || elemAns == 'F' || elemAns == 'T'){

            keyArray[i-1] = elemAns;

        }
        else{
            cout << endl << "Error, " << elemAns << " is not a valid entry." << endl;
            i--;
        }

    }



}



//Validates all answer choices for each student and returns a bool validation
bool getTestData(ifstream& inFile, string& idNumber, char stuArray[], const int questions){

    bool validTest = true;

    //cout << endl << "**current id: " << idNumber << endl;    //dieinstead

    for(int i = 0; i < questions; i++){

     //   cout << "getTestData check with: " << stuArray[i] << endl;   //

        if(!(stuArray[i] == 'A' || stuArray[i]== 'B' || stuArray[i] == 'C' || stuArray[i] == 'D' || stuArray[i] == 'E' || stuArray[i] == 'F' || stuArray[i] == 'T')){

     //       cout <<"invalid check with letter: " << stuArray[i] << endl;   //

            validTest = false;

        }

    }

    return validTest;
}



//accepts an array, converts and returns it in the form of a string
string arrayToString(char array[], const int letters){

    string result = "";

    for(int i = 0; i < letters; i++){

        result += array[i];

    }

    //cout << "Converted an array to: " + result << endl;   //
    return result;

}



//takes all current and relevant data and outputs the marks and scores of each individual student into the output file
void writeScore(ofstream& outFile, char keyArray[], char stuArray[], string idNumber, double& sumScore, string studentTestChoices){

    const int letters = 10;
    int score = 0;
    string marks = "";

   // cout << "reach writeScore()" << endl;   //

    for(int i = 0; i < 10; i++){

        if(keyArray[i] == stuArray[i]){

       //     cout << stuArray[i] << "marked correct" << endl;  //
            score++;
            marks += "+";

        }
        else{
       //     cout << stuArray[i] << "marked incorrect" << endl; //
            marks += "X";
        }

    }

    outFile << "ID = " + idNumber + " Score = " << score << " Responses: " << studentTestChoices << endl
                << setw(35) << left << "Marks: " << marks << endl << endl;


    sumScore += score;
   // cout << "current sumScore: " << sumScore << endl; //
}



//accepts an array and string, then converts the string into a character array
void stringToArray(char array[], string str, const int letters){

   // cout << "entered stringToArray()" << endl;   //
  // cout << "using string: " << str << endl;  //

    for(int i = 0; i < letters; i++){

        array[i] = toupper(str.at(i));

     //   cout << "array[" << i << "]: " << array[i] << endl;   //

    }


}



