/*
1. HW6-CS1337-Kyle-Chan.cpp
2. Last changes made 5/4/20
3. Name: Kyle Chan
4. Purpose:Organize and process a data sheet by storing the values into classes and subclasses
5. Class: CS1337.010
6. Change log:

    4/30/20:
        +Started setting up file input
    5/2/20:
        +Finish file input setup and begin working on header files
    5/3/20:
        +Continue header file implementation
        +Finished Data intake process and routine
    5/4/20:
        +Begin and finish reporting the data from the classes

7. Notes:
    -Type,name,age,weight,breed,color,health
    -Make sure to exclude the first line of data sheet (labels only)
    -Include static variable for classes count
    -Separate header and cpp files for classes and subclasses
    -Cats and Dogs inherit from Animals class
    -Vectors for all the three classes
    -Read line by line from data
    -Create introduction method for animal class (cats and dogs also inherit from it)
    -Report 1:
        -Total animals, cats, and dogs created from data
    -Report 2:
        -Cat report with introduction method
    -Report 3:
        -Dog report with introduction method
    -Report 4:
        -All "good" health dogs and cats
8. Comments:
    !MY REPORTS ARE A LITTLE OUT OF ORDER!
    (Report order: 2/3, 1, 4)
*/


#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

#include "animal.h"
#include "cat.h"
#include "dog.h"

using namespace std;


vector<Animal> animalList;
vector<Cat> catList;
vector<Dog> dogList;

static int animalVecIndex = 0,
           catVecIndex = 0,
           dogVecIndex = 0;

bool openForReading(ifstream &infile,string fileName) {

    infile.open(fileName);

    if (infile.good()){ //then the file opened just fine
        return true;
    }
    else {
        perror("Can't open the specified input file");

        cout << "The file name used was: " << fileName << endl;
        cout << "Quitting program..." << endl;
        return false;
    }
} //openForReading
void getFirstLine(ifstream &infile){

    //process past first line (extraneous)
    string junk;
    getline(infile, junk, '\n');

}


void getAnimalData(ifstream &infile){

    //parse each word separated by commas or a newline


    string type;
    string name,
           age,
           weight,
           breed,
           color,
           health,
           sound;


    //8 possible data inputs
    getline(infile, type, ',');
    //cout << type + " ";
    getline(infile, name, ',');
    //cout << name + " ";
    getline(infile, age, ',');
    //cout << age + " ";
    getline(infile, weight, ',');
    //cout << weight + " ";
    getline(infile, breed, ',');
    //cout << breed + " ";
    getline(infile, color, ',');
    //cout << color + " ";
    getline(infile, health, ',');
    //cout << health + " ";
    getline(infile, sound, '\n');
    //cout << sound << endl;

    if(type == "cat"){
        //cout << "kat" << endl;
        Cat *catPtr = new Cat;
        catList.emplace_back(*catPtr); //push_back was causing problems for me?? emplace_back works just as well
        catList[catVecIndex].setAnimal(type,name,age,weight,breed,color,health,sound);
        catList[catVecIndex].displayAnimal();
        cout << "-======================-" << endl;
        catVecIndex++;

    }
    else if(type == "dog"){
        Dog *dogPtr = new Dog;
        dogList.emplace_back(*dogPtr);
        dogList[dogVecIndex].setAnimal(type,name,age,weight,breed,color,health,sound);
        dogList[dogVecIndex].displayAnimal();
        cout << "-======================-" << endl;
        dogVecIndex++;
    }
    else if(type == ""){//occurs at eof
        return;
    }
    else{
        //cout << "+++++++" << endl;
        Animal *aniPtr = new Animal;
        animalList.emplace_back(*aniPtr);
        animalList[animalVecIndex].setAnimal(type,name,age,weight,breed,color,health,sound);

        //debug
       /* cout << animalList[animalVecIndex].getType() << endl
             << animalList[animalVecIndex].getName() << endl
             << animalList[animalVecIndex].getAge() << endl
             << animalList[animalVecIndex].getWeight() << endl
             << animalList[animalVecIndex].getBreed() << endl
             << animalList[animalVecIndex].getColor() << endl
             << animalList[animalVecIndex].getHealth() << endl
             << animalList[animalVecIndex].getSound() << endl;*/

        animalVecIndex++;
        //cout << "+++++++" << endl;
    }

}

int main(){

    ifstream infile;
    if(openForReading(infile, "Animal Shelter Data-04.csv")){

        //cout << "file opened successfully" << endl;

        getFirstLine(infile);
        while(!infile.eof()){ //process/organize all animal data
            getAnimalData(infile); //Reports 2 and 3
        }

        cout << "+++++++" << endl;//Report 1

        cout << "there are " << animalList[animalVecIndex].getAnimalCount() << " animals in total." << endl;
        cout << "there are " << catList[catVecIndex].getCatCount() << " cats." << endl;
        cout << "there are " << dogList[dogVecIndex].getDogCount() << " dogs." << endl;

        cout << "+++++++" << endl;

        int totCats = catVecIndex + 1; //Report 4
        int totDogs = dogVecIndex + 1;
        int totAnimals = animalVecIndex + 1;

        cout << "These are all of the animals ready for adoption!" << endl;
        cout << "Cats:" << endl;
        for(int i = 0; i < totCats; i++){
            if(catList[i].getHealth() == "good")
                cout << "-" << catList[i].getName() << endl;
        }

        cout << "+++++++" << endl;
        cout << "Dogs:" << endl;
        for(int i = 0; i < totDogs; i++){
            if(dogList[i].getHealth() == "good")
                cout << "-" << dogList[i].getName() << endl;
        }

        cout << "+++++++" << endl;
        cout << "Others:" << endl;
        for(int i = 0; i < totAnimals; i++){
            if(animalList[i].getHealth() == "good")
                cout << "-" << animalList[i].getName() << endl;
        }
    }


    infile.close();

    return 0;
}
