#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED
#include <string>
#include <iostream>

class Animal{

    static int animalCount;
    std::string animalType;
    std::string animalName;
    std::string animalBreed;
    std::string animalColor;
    std::string animalHealth;
    std::string animalSound;
    std::string animalAge;
    std::string animalWeight;

    public:

        Animal(){animalCount++;};
        static int getAnimalCount(){return (animalCount);};
        void setAnimal(std::string type, std::string name, std::string age, std::string weight, std::string breed, std::string color, std::string health, std::string sound);

        void displayAnimal();

        std::string getType(){return animalType;};
        std::string getName(){return animalName;};
        std::string getAge(){return animalAge;};
        std::string getWeight(){return animalWeight;};
        std::string getBreed(){return animalBreed;};
        std::string getColor(){return animalColor;};
        std::string getHealth(){return animalHealth;};
        std::string getSound(){return animalSound;};

};

int Animal::animalCount = 0;

void Animal::setAnimal(std::string type, std::string name, std::string age, std::string weight, std::string breed, std::string color, std::string health, std::string sound){
    if(type != "")
        animalType = type;
    if(name != "")
        animalName = name;
    if(age != "")
        animalAge = age;
    if(weight != "")
        animalWeight = weight;
    if(breed != "")
        animalBreed = breed;
    if(color != "")
        animalColor = color;
    if(health != "")
        animalHealth = health;
    if(sound != "")
        animalSound = sound;
}

void Animal::displayAnimal(){

    std::cout << "Hi! I'm a " << animalType << ", and my name is " << animalName << "." << std::endl;

    if(animalAge != "")
        std::cout << "I'm " << animalAge << " years old." << std::endl;
    if(animalWeight != "")
        std::cout << "I weigh " << animalWeight << " pound(s)." << std::endl;
    if(animalBreed != "")
        std::cout << "I am a " << animalBreed << std::endl;
    if(animalColor != "")
        std::cout << "I am " << animalColor << std::endl;
    if(animalHealth == "good")
        std::cout << "I feel really healthy right now!" << std::endl;
    else
        std::cout << "I don't really feel the greatest at the moment :(" << std::endl;
    if(animalSound != "")
        std::cout << animalSound << "!!" << std::endl;


}
#endif // ANIMAL_H
