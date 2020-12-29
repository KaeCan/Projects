/*
1. HW3-CS1337-10-KYLE-CHAN.cpp
2. Last changes made 2/26/20
3. Name: Kyle Chan
4. Purpose: Sort and interact with vectors
5. Class: CS1337.010
6. Change log:

    2/26/20:
        +Generate vectors
        +Sort Vectors
        +Bubble sort
        +User input value search
        +Duplicate search
        +Duplicate deletion

7. Notes:
    -Generate random numbers (~30-40), but ask for input
        -Ask how large the numbers should be (up to 20)
        -Store random numbers in vector1
        -Show vector1's contents, size, and capacity (unsorted)
    -Create a copy of original vector1 (vector2)
        -Sort using your choice of bubble of insertion
        -show contents of sorted vector2
    -Sort original vector1 using sort algorithm method in <algorithm>
        -sort(vec.begin(), vec.end());
        -Show vector contents (sorted)
    -With vector1
        -Create routine to search user inputted numbers
            -Report if it is found and how many times
                -RUN AT LEAST 5 TIMES, SEARCH FOR AT LEAST 2 NUMBERS NOT IN VECTOR (FINAL OUTPUT)
                -Use binary search method to find the first occurrence of the number
                -Count number of duplicates (if any)

    -10 extra points
        -After checking for all duplicates and asking for numbers to search, delete all duplicates in vector1
            -Cannot copy into second vector
            -Display new vector1
    -5 extra points
        -If you cannot delete all duplicates within vector1, copy unique elements into another vector


8. Comments:
*/


#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <windows.h>
#include <ctime>

using namespace std;

vector<int> vec1;
vector<int> vec2;

int vectorSize,
    rngLimit;



void rng(){

    srand(time(0));

    for (int i = 0; i < vectorSize; i++){
        vec1.push_back(rand() % (rngLimit + 1));
    }


}

void displayVectorInfo(vector<int> vec){

    for(int i = 0; i < vec.size(); i++){
        cout << vec[i] << "|";
    }

    cout << endl << "The Vector size is: " << vec.size()
         << endl << "The Vector's capacity is: " << vec.capacity() << endl;


}

void swap(int *first, int *second){

    int temp = *first;

    *first = *second;
    *second = temp;
}

void bubbleSortVec2(){

    for(int pass = 0; pass < vec2.size() - 1; pass++){

        for(int index = 0; index < vec2.size() - pass - 1; index++){//vec2.size - pass - 1 to eliminate redundancy

            if(vec2[index] > vec2[index+1]){
                swap(&vec2[index], &vec2[index+1]);
            }
        }
    }

}

int searchDuplicates(int seekVal){

    int count = 0;
    for(int i = 0; i < vec1.size(); i++){
        if(vec1[i] == seekVal)
            count++;
    }

    return count;
}

void searchForNumbers(){

    int userInput,
        count;

    do{

        cout << endl << "Type in any number to check for it in the Vector. Type -1 to continue. ";
        cin >> userInput;
        if(userInput > -1 && userInput < rngLimit){
            //seek userInput in vec1
            if(binary_search(vec1.begin(), vec1.end(), userInput)){
                count = searchDuplicates(userInput);

                cout << userInput << " can be found in the Vector!" << endl
                    //count duplicates
                     << "There are " << count << " instances of " << userInput << endl;

            }
            else{
                cout << userInput << " cannot be found in the Vector!" << endl;
            }
        }
        else{
            cout << userInput << " cannot be found in the Vector!" << endl;
        }

    }while(userInput != -1);

}

void deleteDuplicates(){

    for(int i = 0; i < vec1.size();i++){

        if(i > 0 && vec1[i] == vec1[i - 1]){
            vec1.erase(vec1.begin() + i);
            i--; //vector indexes get shifted after erase
        }


    }

}

int main(){

    //prompt user for vector size and number range
    cout << "How big do you want the vector to be? ";
    cin >> vectorSize;

    cout << "What is the biggest number you would like to generate? ";
    cin >> rngLimit;

    //push_back random numbers
    rng();

    //display vector1 info
    cout << endl << "Unsorted, original numbers." << endl;
    displayVectorInfo(vec1);

    //copy vector1 to vector2
    vec2 = vec1;

    //sort vector1 using algorithm method
    sort(vec1.begin(), vec1.end());
    //display vector1 info
    cout << endl << "Algorithm sorted, original numbers." << endl;
    displayVectorInfo(vec1);

    //sort vector2 with bubble sort
    bubbleSortVec2();

    //display vector2 info
    cout << endl << "Bubble sorted, copy of numbers." << endl;
    displayVectorInfo(vec2);

    //DONE WITH VECTOR2

    //Routine to search for user inputted numbers
    searchForNumbers();

    //Delete duplicate numbers
    cout << endl << "Deleting all duplicate numbers in Vector." << endl;
    deleteDuplicates();

    //display new vector1
    displayVectorInfo(vec1);

    return 0;
}
