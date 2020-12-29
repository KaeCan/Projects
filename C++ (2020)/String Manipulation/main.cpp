/*
1. HW4-CS1337-10-Kyle-Chan.cpp
2. Last changes made: 3/10/20
3. Name: Kyle Chan
4. Purpose: Manipulate and parse strings
5. Class: CS1337.010
6. Change log:

    3/10/20:
        +I lIteRAllY fINishEd tHe cODe

7. Notes:
    -Read in TongueTwister.txt, each line is one input
    -Store lines in vector OR read in each line one at a time
    -Each string:
        -Print the string
        -Report # of words (ideally parse string into a vector of words)
        -Count # of vowels and consonants
        -Count # of punctuation and other characters (might need a map, 2D array, switch statement, etc)
        -Convert string into Title Case
        -Convert string into tOGGLE cASE
        -Convert string into Sentence case (capital first letter of sentence and formal nouns)
        -Find longest word

    -OPTIONAL SENTENCE:
        It is just a meaningless, repetitive phrase that a linguist, Professor Henry Higgins (in the
        movie My Fair Lady) used as a mnemonic device to help the learner (“Liza”) learn the correct
        way to pronounce the diphthong “ai,” as in “aim” and “main,” rather than the Cockney
        pronunciation of it, which sounds like the “i” in “Rhine” and “spine.”

    -"LeAVE YoUr DEbugGING coDe iN uR program!"

8. Comments:
*/


#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

//word vector
vector<string> words(100, ""); //empty strings
vector<string> justWords(100, ""); //words without punctuation
int wordCount;

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

void getWordVector(string line){

    int word = 0;
    bool flag;

    //cout << "***getWordVector reached" << endl;

    for(int i = 0, wordIndex = 0; i < line.length() - 1; i++){

        wordIndex = i;
        flag = false;

        do{
            flag = true;
            words[word] += line.at(wordIndex); //COMMAS, PERIODS, QUESTION MARKS ARE INCLUDED
            wordIndex++;
        }
        while(wordIndex < line.length() && line.at(wordIndex) != ' ' && line.at(wordIndex) != '\n');//check for letters and apostrophes

        if(flag)
            word++;

        i = wordIndex;
        //cout << "***i: " << i << endl;
        //cout << "***wordIndex: " << wordIndex << endl;
    }


    /*cout << "***";
    for(int i = 0; i < words.size();i++){
        cout << words[i] + " ";
    }
    */

}

void displayVector(vector<string> vec){

    for(int i = 0; i < vec.size();i++){
        cout << vec[i] + " ";
    }

    cout << endl;
}


void titleCase(){

    vector<string> title(words);
    title.resize(wordCount + 1);

    /*cout << "***";
    displayVector(title);

    cout << endl << title.size();
    */

    for(int i = 0;i < title.size() - 1;i++){

    //cout << title[i] << endl;//***

        title[i].at(0) = toupper(title[i].at(0));

        /*if(title[i].length() > 1){
            for(int j = 1;j < title[i].length() - 1;j++){
                if(isalpha(title[i].at(j)))
                    tolower(title[i].at(j));

                cout << "***" + title[i] << endl;
            }
        }
        */
    }

    cout << "Title Case: ";
    displayVector(title);


}

void toggleCase(){

    vector<string> toggle(words);
    toggle.resize(wordCount + 1);

    for(int i = 0;i < toggle.size() - 1;i++){

        toggle[i].at(0) = tolower(toggle[i].at(0));

        for(int j = 1;j < toggle[i].length();j++){
            if(isalpha(toggle[i].at(j))){ //is letter
                toggle[i].at(j) = toupper(toggle[i].at(j));
            }
        }

    }

    cout << "Toggle Case: ";
    displayVector(toggle);

}

void sentenceCase(string line){

    for(int i = 1;i < line.length();i++){ //leave first letter alone

        if(line.at(i) == '.' || line.at(i) == '?'){
            if(line.at(i) != line.length() - 1){
                i += 3; //first letter of sentence left alone
                continue;
            }
        }
        else{
            if(isalpha(line.at(i))){
                line.at(i) = tolower(line.at(i));
            }
        }

    }

    cout << "Sentence Case: " + line;

}
void getJustWordsVector(string line){

    int word = 0;
    bool flag;

    for(int i = 0, wordIndex = 0; i < line.length() - 1; i++){

        wordIndex = i;
        flag = false;

        do{
            flag = true;
            if(isalpha(line.at(wordIndex))){ //DOES NOT HAVE ANY PUNCTUATION
                justWords[word] += line.at(wordIndex);
            }
            wordIndex++;
        }
        while(wordIndex < line.length() && line.at(wordIndex) != ' ' && line.at(wordIndex) != '\n');//check for letters and apostrophes

        if(flag)
            word++;

        i = wordIndex;
    }

}

void longestWord(string line){

    getJustWordsVector(line);

    vector<string> longest(justWords); //use vector with no punctuations in vector contents
    longest.resize(wordCount + 1);

    vector<string> longWords;

    longWords.push_back(longest[0]);

    for(int i = 1;i < longest.size() - 1;i++){ //check for FIRST largest word
        if(longest[i].length() > longWords[0].length()){
            longWords[0] = longest[i];
        }
        //cout << "***Longest word so far: " << longWords[0];
    }

    for(int i = 0;i < longest.size() - 1;i++){ //check for words of same length
        if(longest[i].length() == longWords[0].length()){
            if(longest[i] != longWords[0])
                longWords.push_back(longest[i]);
        }

    }

    cout << "Longest Word(s): ";
    displayVector(longWords);

}

void sentenceManip(string line){

    //get word vector
    getWordVector(line);

    //title case
    titleCase();

    //toggle case
    toggleCase();

    //sentence case
    sentenceCase(line);

    //sentence case with exceptions (formal nouns)
    cout << endl << "Sentence Case (with exceptions): ";
    displayVector(words);

    //longest word
    longestWord(line);
}

void countWords(string line){

    int count = 1; //first word

    for(int i = 0; i < line.length(); i++){
        if(line.at(i) == ' ' || line.at(i) == '\n'){
            count++;
        }
    }


    cout << "Number of words: " << count << endl;

    wordCount = count;
}


void countLetters(string line){

    int count = 0;

    for(int i = 0; i < line.length(); i++){

        if((line.at(i) >= 65 && line.at(i) <= 90) || (line.at(i) >= 97 && line.at(i) <= 122)){ //all letters
            count++;
        }
    }

    cout << "Number of letter: " << count << endl;

}

void countVowsConsPunct(string line){

    int vowelCount = 0,
        consCount = 0,
        punctCount = 0;

    for(int i = 0; i < line.length(); i++){

        if((line.at(i) >= 65 && line.at(i) <= 90) || (line.at(i) >= 97 && line.at(i) <= 122)){ //only letters
            switch(tolower(line.at(i))){

                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                    vowelCount++;
                    break;
                default:
                    consCount++; //anything not a vowel is a consonant
            }
        }
        else if(line.at(i) != ' ' && line.at(i) != '\n') //only punctuation left
            punctCount++;
    }

    cout << "Number of vowels: " << vowelCount << endl
         << "Number of consonants: " << consCount << endl
         << "Number of punctuation symbols: " << punctCount << endl;

}

int main(){

    string textLine, inputFile;

    //read in input text file
    cout << "specify what file to use as input: ";
    cin >> inputFile;

    ifstream infile;

    if(openForReading(infile, inputFile)){

        while(!infile.eof()){

            cout << "---------------------------------------------" << endl;

            getline(infile, textLine);
            cout << endl << textLine << endl;

            countWords(textLine);

            countLetters(textLine);

            countVowsConsPunct(textLine);

            sentenceManip(textLine);

            fill(words.begin(), words.end(), ""); //reset vectors for next line
            fill(justWords.begin(), justWords.end(), "");
        }
    }

    infile.close();
    return 0;
}
