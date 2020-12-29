#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED
#include <string>

#include "animal.h"

class Cat : public Animal{

    static int catCount;
    std::string animalType;
    std::string animalName;
    std::string animalBreed;
    std::string animalColor;
    std::string animalHealth;
    std::string animalSound;
    std::string animalAge;
    std::string animalWeight;

    public:

    Cat(){catCount++;};
    static int getCatCount(){return catCount;};

};

int Cat::catCount = 0;
#endif // CAT_H_INCLUDED
