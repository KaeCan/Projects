#include "animal.h"

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
