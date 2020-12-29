#ifndef DOG_H_INCLUDED
#define DOG_H_INCLUDED
#include <string>

#include "animal.h"

class Dog : public Animal{

    static int dogCount;
    std::string animalType;
    std::string animalName;
    std::string animalBreed;
    std::string animalColor;
    std::string animalHealth;
    std::string animalSound;
    std::string animalAge;
    std::string animalWeight;

    public:

    static int getDogCount(){return dogCount;};
    Dog(){dogCount++;}

};

int Dog::dogCount = 0;
#endif // DOG_H_INCLUDED
