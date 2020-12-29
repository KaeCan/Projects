/* GRADEBOOK #8
Program creates a menu for a fraction quiz tutor in which there are 10-question quizzes
for addition, subtraction, multiplication, and division. It will continue to loop back to the
after each quiz until the user wishes to exit.

The quiz itself will be displayed in a neat and visual manner that allows the user to input a fraction
in the format of [numerator] / [denominator]. At the end of each quiz, there will be a display showing
how many questions out of 10 the user got correct.
*/


#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void addFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom);

void subFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom);

void multFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom);

void divFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom);

int gcd(int a, int b);

void quizzer(char letter);

void displayFractions(int num1, int denom1, int num2, int denom2, int ansNum, int ansDenom, int &counter, char letter);

char oper(char letter);



int main() {

    char menuLetter;

    srand(time(0));

    while(menuLetter != 'Q'){
        cout << "Welcome to the fraction tutor!" << endl << endl;

        cout << left << setw(10) << " " << "A - Fraction Addition Quiz" << endl
                << setw(10) << " " << "S - Fraction Subtraction Quiz" << endl
                << setw(10) << " " << "M - Fraction Multiplication Quiz" << endl
                << setw(10) << " " << "D - Fraction Division Quiz" << endl
                << setw(10) << " " << "Q - Quit the program" << endl << endl
                << "Enter the letter for your selection [A, S, M, D, Q]: ";

        cin >> menuLetter;
        menuLetter = toupper(menuLetter);
        if(menuLetter != 'Q'){
                quizzer(menuLetter);
        }


    }

    cout << endl << "Goodbye!" << endl;

    return 0;

}

//Takes two numbers and returns the greatest common divisor

int gcd(int a, int b){

    while(a != b){
        if(a > b){
            a = a - b;
        }

        else{
            b = b - a;
        }
    }

    return a;
}


//Takes the sum of two fractions (suffixed by 1 or 2) and defines a resulting fraction

void addFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom){

    resultNum = num1 * denom2 + num2 * denom1;
    resultDenom = denom1 * denom2;

    int divisor = gcd(resultNum, resultDenom);

    resultNum /= divisor;
    resultDenom /= divisor;



    return;
}


//Takes the difference of two fractions (suffixed by 1 or 2) and defines a resulting fraction

void subFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom){

    resultNum = num1 * denom2 - num2 * denom1;
    resultDenom = denom1 * denom2;

    int divisor = gcd(resultNum, resultDenom);

    resultNum /= divisor;
    resultDenom /= divisor;

    return;
}


//Takes the product of two fractions (suffixed by 1 or 2) and defines a resulting fraction

void multFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom){

    resultNum = num1 * num2;
    resultDenom = denom1 * denom2;

    int divisor = gcd(resultNum, resultDenom);

    resultNum /= divisor;
    resultDenom /= divisor;

    return;
}


//Takes the quotient of two fractions (suffixed by 1 or 2) and defines a resulting fraction

void divFractions(int num1, int denom1, int num2, int denom2, int &resultNum, int &resultDenom){

    resultNum = num1 * denom2;
    resultDenom = denom1 * num2;

    int divisor = gcd(resultNum, resultDenom);

    resultNum /= divisor;
    resultDenom /= divisor;

    return;
}


//Accepts the letter issued by the user when on the menu, and directs the user to the corresponding type of quiz

void quizzer(char letter){

    int num1, num2, denom1, denom2, ansNum, ansDenom,
          counter = 0;
    bool validMenuSelection = true;

    switch (letter){

        case 'A':
            for (int i =1; i < 11; i++){

                cout << endl << "Question " << i << ": What is the result of the following?" << endl << endl;

                num1 = rand() % 10 + 1;
                num2 = rand() % 10 + 1;
                denom1 = rand() % 10 + 1;
                denom2 = rand() % 10 + 1;

                addFractions(num1, denom1, num2, denom2, ansNum, ansDenom);

                displayFractions(num1, denom1, num2, denom2, ansNum, ansDenom, counter, letter);

            }
            break;

        case 'S':
            for (int i =1; i < 11; i++){

                cout << endl << "Question " << i << ": What is the result of the following?" << endl << endl;

                num1 = rand() % 10 + 1;
                num2 = rand() % 10 + 1;
                denom1 = rand() % 10 + 1;
                denom2 = rand() % 10 + 1;

                subFractions(num1, denom1, num2, denom2, ansNum, ansDenom);

                displayFractions(num1, denom1, num2, denom2, ansNum, ansDenom, counter, letter);

            }

            break;

        case 'M':
            for (int i =1; i < 11; i++){

                cout << endl << "Question " << i << ": What is the result of the following?" << endl << endl;

                num1 = rand() % 10 + 1;
                num2 = rand() % 10 + 1;
                denom1 = rand() % 10 + 1;
                denom2 = rand() % 10 + 1;

                multFractions(num1, denom1, num2, denom2, ansNum, ansDenom);

                displayFractions(num1, denom1, num2, denom2, ansNum, ansDenom, counter, letter);

            }

            break;

        case 'D':
            for (int i =1; i < 11; i++){

                cout << endl << "Question " << i << ": What is the result of the following?" << endl << endl;

                num1 = rand() % 10 + 1;
                num2 = rand() % 10 + 1;
                denom1 = rand() % 10 + 1;
                denom2 = rand() % 10 + 1;

                divFractions(num1, denom1, num2, denom2, ansNum, ansDenom);

                displayFractions(num1, denom1, num2, denom2, ansNum, ansDenom, counter, letter);

            }

            break;

        default:
                cout << endl << "Incorrect letter!" << endl;
                validMenuSelection = false;
    }

   if(validMenuSelection){
         cout << endl << "You got " << counter << " of 10 correct." << endl;

        if(counter == 10){
            cout << "Great job!" << endl << endl;
        }
        else{
            cout << "Keep practicing!" << endl << endl;
        }
   }

}


//Takes all the fractions, score counter, and menu letter to create a neat display for the fraction quiz

void displayFractions(int num1, int denom1, int num2, int denom2, int ansNum, int ansDenom, int &counter, char letter){

    int userNum, userDenom;

    cout << right << setw(3) << num1 << setw(7) << num2 << endl
                        << "---- " << oper(letter) << " ----" << endl
                        << setw(3) << denom1 << setw(7) << denom2 << endl << endl
                        << "Enter your answer in the form numerator / denominator: ";

                cin >> userNum;
                cin.ignore();
                cin >> userDenom;

                if(userNum == ansNum && userDenom == ansDenom){

                    cout << endl << "That is correct!" << endl;
                    counter++;
                }
                else {

                    cout << endl << "I am sorry, that is not correct." << endl << endl
                            << right << setw(3) << num1 << setw(7) << num2 << setw(7) << ansNum << endl
                            << "---- " << oper(letter) << " ---- = ----" << endl
                            << setw(3) << denom1 << setw(7) << denom2 << setw(7) << ansDenom << endl << endl;
                }


}


//Accepts the letter issued by the user when on the menu, and returns a corresponding operator for the type of quiz

char oper(char letter){

    switch(letter){
        case 'A':
            letter = '+';
            break;

        case 'S':
            letter = '-';
            break;

        case 'M':
            letter = '*';
            break;

        case 'D':
            letter = 246;

    }

    return letter;
}
