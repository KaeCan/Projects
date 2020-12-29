/*
1. SnakeGame Cleanup - SnakeGame Cleanup - Revised.cpp
2. Last changes made 1/28/20
3. Name: Kyle Chan
4. Purpose: Revise and optimize the code while implementing more extensions to the original game
5. Class: CS1337.010
6. Change log:

    1/16/20:
        +add comments to clarify various aspects of the game
        +revise variable names to clarify their purpose in the program
        +modulate the code by creating separate functions for various tasks
    1/19/20:
        +added library "ctime"
-------------------------------------------------------------------------------------------
    1/27/20:
        +added multiple-fruit capability
        +added restart/exit option
    1/28/20:
        +added pause option
        +added case insensitivity
        +added option for wall collisions
        +added instructions at startup
        +DISCRETIONARY: added a win notification when max tail length is reached and stops the game

7. Notes:
    -Refactor the logic in some parts into separate functions to make the code more intuitive
    -Add comments to clarify any confusing logic
    -Change variable names to make their purpose more apparent
    -Revise and fix Logic()
    -Attempt to find a bug that makes the snake disappear
    -Add multiple-fruit capabilities
    -Add a restart/exit option at the end of a game
    -Add option to make gameOver when snake hits the wall
    -Make input routine case-INsensitive
    -Add an input option P to pause the game and wait for another key input
    -Print instructions at the beginning of the game
    -Maybe Add any other features deemed useful
8. Comments:
*/


#include <iostream> //for cout and cin
#include <conio.h> //for _kbhit, _getch
#include <windows.h> //for sleep and time
#include <ctime> //for time(0)
using namespace std;
bool gameOver;
bool restart = false;
bool wallCollisions = false;

//establish the size of the box the game will take place in
const int width = 20;
const int height = 20;

//changed the program to take more than one fruit
int snakeHeadX, snakeHeadY, score; //x and y are snake's head coords

const int maxFruits = 5;                                                                                      //CHANGE THIS FOR # OF FRUITS ON SCREEN
int fruitX[maxFruits], fruitY[maxFruits];

const int maxTailLength = 100;                                                                             //CHANGE THIS FOR MAX TAIL LENGTH
int tailX[maxTailLength], tailY[maxTailLength]; //used to store data on the current size of the snake

int tailLength;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Instructions(){

    cout << "Welcome to the Snake Game." << endl << endl;
    Sleep(2000);
    cout << "Use W, A, S, and D to control your snake." << endl;
    Sleep(1000);
    cout << "Press X to exit your current game." << endl;
    Sleep(1000);
    cout << "Press P to pause the game." << endl << endl;
    Sleep(1000);

}
void startMenu(){ //Let player choose to turn on/off wall collisions

    char userInput;
    bool validInput = true;

    do{
        cout << "Would you like to play with wall collisions? Please enter Y / N: ";
        cin >> userInput;

        if (tolower(userInput) == 'y'){
            wallCollisions = true;
            validInput = true;
        }
        else if (tolower(userInput) == 'n'){
            wallCollisions = false;
            validInput = true;
        }
        else {
            validInput = false;
        }

    }while(!validInput);


}
void spawnFruit(){

    //a fruit is randomly generated somewhere in the box
    srand(time(0)); //seeds current time into RNG

    for (int i = 0; i < maxFruits; i++){

    fruitX[i] = rand() % width;
    fruitY[i] = rand() % height;

    }
}
void resetTail(){

    for (int i = 0; i < maxTailLength; i++){ //take the entire tail out of the play area to avoid redrawing
        tailX[i] = width + 2;
        tailY[i] = height + 2;
    }

}
void Setup()
{
    restart = false;
    gameOver = false;
    dir = STOP; //the snake begins not moving

    //snake's head begins in the center of the box
    snakeHeadX = width / 2;
    snakeHeadY = height / 2;

    resetTail();

    tailLength = 0;

    spawnFruit();

    score = 0;
}
void drawHorizontalLine()
{
     for (int i = 0; i < width+2; i++) //width+2 b/c the border extends beyond the play area
        cout << "#";
    cout << endl;
}
bool drawFruits(int row, int column){

    bool yesFruit = false;

    for (int i = 0; i < maxFruits; i++){

        if (row == fruitY[i] && column == fruitX[i]){ //current coords is where one of the fruit belongs
            yesFruit = true;
        }

    }

    return yesFruit;

}
void drawPlayArea(){

    for (int row = 0; row < height; row++) //rows of y
    {
        for (int column = 0; column < width; column++) //columns of x
        {

            if (column == 0) //new line is started
                cout << "#"; //draw border character

            if (row == snakeHeadY && column == snakeHeadX) //current coords is where the snake head belongs
                cout << "O"; //draw snake head

            //else if (row == fruitY && column == fruitX) //current coords is where the fruit belongs
            else if (drawFruits(row, column)){
                cout << "F"; //draw fruit

            }
            else
            {
                bool printed = false; //anything is printed
                for (int snakeBodyPart = 0; snakeBodyPart < tailLength; snakeBodyPart++)
                {
                    if (tailX[snakeBodyPart] == column && tailY[snakeBodyPart] == row) //current coords is where a snake body part belongs
                    {
                        cout << "o"; //draw snake body
                        printed = true;
                    }
                }
                if (!printed)//if nothing is drawn on current coords
                    cout << " ";
            }


            if (column == width - 1)  //current coords is the end of play area
                cout << "#";
        }
        cout << endl;
    }

}
void Draw()
{

    system("cls"); //system("clear");

    drawHorizontalLine();//top of play area

    drawPlayArea(); //everything in between

    drawHorizontalLine(); //bottom of play area

    cout << "Score:" << score << endl;

    if(tailLength == maxTailLength){
        cout << endl << "You've reached max tail length! You've won!" << endl;  //win notification if max tail length reached
        gameOver = true;
    }
}
void pause(){

    cout << endl << "Press any key to resume the game." << endl;

    system("pause");

}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
        case 'A':
            dir = LEFT;
            break;
        case 'd':
        case 'D':
            dir = RIGHT;
            break;
        case 'w':
        case 'W':
            dir = UP;
            break;
        case 's':
        case 'S':
            dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = true;
            break;
        case 'p':
        case 'P':
            pause();
            break;
        }
    }
}
void updateFruit(){

    for (int i = 0; i < maxFruits; i++){

        if (snakeHeadX == fruitX[i] && snakeHeadY == fruitY[i]) //increment score and replace fruit if it is eaten, then increase tail length
        {
            score += 10;
            fruitX[i] = rand() % width;
            fruitY[i] = rand() % height;
            tailLength++;
        }

    }

}
void updateSnake(){
    int prevX = tailX[0]; //placeholder for the previous coords of the "neck" in the last frame
    int prevY = tailY[0];

    int prev2X, prev2Y; //placeholder for the coords of the body part below the "neck" (2 under the snake head)



    if(score != 0){

    tailX[0] = snakeHeadX; //the "neck" goes where the head used to be in the last frame
    tailY[0] = snakeHeadY;

    }


    for (int i = 1; i < tailLength; i++) //"inching" each body part one over the previous frame in the input direction
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

}
void checkSnakeAtBorder(){

    //if (x > width || x < 0 || y > height || y < 0)
    //  gameOver = true;

    if (wallCollisions){

        if (snakeHeadX >= width || snakeHeadX < 0) gameOver = true; //walls are fatal
        if (snakeHeadY >= width || snakeHeadY < 0) gameOver = true;
    }
    else{
        if (snakeHeadX >= width) snakeHeadX = 0; else if (snakeHeadX < 0) snakeHeadX = width - 1; //move snake head to opposite side if it touches a border
        if (snakeHeadY >= height) snakeHeadY = 0; else if (snakeHeadY < 0) snakeHeadY = height - 1;
    }
}
void checkSnakeCollision(){



    for (int i = 0; i < tailLength; i++){ //gameover if snake head touches its tail
        if (tailX[i] == snakeHeadX && tailY[i] == snakeHeadY){
            //cout << "Tail Coords: **" << tailX[i]  << " " << tailY[i] << endl;
            //cout << "checkSnakeCollision: gameOver set to true**" << endl;
            gameOver = true;
        }
    }
}
void Logic()
{
    updateSnake();

    switch (dir)   //origin (0, 0) coords are at top left corner of map
    {
        case LEFT:
        snakeHeadX--;
        break;
    case RIGHT:
        snakeHeadX++;
        break;
    case UP:
        snakeHeadY--;
        break;
    case DOWN:
        snakeHeadY++;
        break;
    default:
        break;
    }

    checkSnakeAtBorder();

    checkSnakeCollision();

    updateFruit();

}
void endMenu(){
    char userInput;
    bool validInput = true;

    do{
        cout << "Would you like to play another game? Please enter Y / N: ";
        cin >> userInput;

        if (tolower(userInput) == 'y'){
            //cout << "restart set to true**" << endl;
            restart = true;
            validInput = true;
        }
        else if (tolower(userInput) == 'n'){
            validInput = true;
        }
        else {
            //cout << "validInput set to false**" << endl;
            validInput = false;
        }

    }while(!validInput);
}
int main()
{
    Instructions(); //run once
    do{
            startMenu();
            Setup();
        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            Sleep(10); //sleep(10);
        }
        endMenu();
    }while(restart);
    return 0;
}
