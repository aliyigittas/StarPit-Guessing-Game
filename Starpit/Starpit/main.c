//
//  main.c
//  Starpit
//
//  Created by Ali Yiğit Taş on 15.06.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int GuessNumber;
int SeperatedNumber[4];
int RandomNumber[4];
int PlusSign;
int NegativeSign;
int menu;
int back;
int GuessCount = 0;
bool GameOver;
bool GameStarted;
bool IsFourDigit;

static void HomeScreen(){ //Main Menu
    
    printf(":'######::'########::::'###::::'########::'########::'####:'########:\n");
    printf("'##... ##:... ##..::::'## ##::: ##.... ##: ##.... ##:. ##::... ##..::\n");
    printf(" ##:::..::::: ##:::::'##:. ##:: ##:::: ##: ##:::: ##:: ##::::: ##::::\n");
    printf(". ######::::: ##::::'##:::. ##: ########:: ########::: ##::::: ##::::\n");
    printf(":..... ##:::: ##:::: #########: ##.. ##::: ##.....:::: ##::::: ##::::\n");
    printf("'##::: ##:::: ##:::: ##.... ##: ##::. ##:: ##::::::::: ##::::: ##::::\n");
    printf(". ######::::: ##:::: ##:::: ##: ##:::. ##: ##::::::::'####:::: ##::::\n");
    printf(":......::::::..:::::..:::::..::..:::::..::..:::::::::....:::::..:::::\n");

    printf("\nWelcome to number guessing game StarPit!\n\n");
    printf("1.Start Game\n\n");
    printf("2.How to Play\n\n");
    printf("3.Exit\n\n");
    printf("Your Selection:");
    scanf("%d",&menu);
    
    switch (menu) {
        case 1: //Starts Game
            GameStarted = true;
            break;
        case 2: //How to Play
            system("clear || cls");
            printf("Thank you for playing StarPit.\n\n");
            printf(">  In this game, you need to predict 4-digit number generated from AI.\n");
            printf(">  After you make your guess, the program will give you a hint based on your guess.\n");
            printf(">  Hints looks like this ‘+1 / -2’. This means one number is in the right place, but two numbers are in wrong place, and one number is not in the number that you are trying to predict.\n");
            printf(">  If you reach ‘+4 / -0’ you will win the game and the program ends.\n\n");
            printf("Reminder: Program does not use same digits in same number when generating random number. So, you do not have to use same digits in one prediction.\n");
            printf("\n");
            printf("FUTURE UPDATES:\n");
            printf("\n");
            printf(">  2 player mode\n");
            printf(">  And some other new features...\n");
            printf("\nPress 0 and enter to go back.\n");
            scanf("%d",&back);
            switch (back) {
                case 0: //Backs to HomeScreen
                    system("clear || cls");
                    HomeScreen();
                    break;
            }
        case 3: //Terminates program.
            return;
        default: //If user enters unexpected input, function repeats.
            system("clear || cls");
            printf("Please make a selection between 1-3\n\n");
            HomeScreen();
            return;
    }
}

static void GenerateRandomNumber(){
    int lower = 1, upper = 9, count = 4;
    
    for (int i = 0; i < count; i++) {
        RandomNumber[i] = (rand() % (upper - lower + 1)) + lower; //Generates 4 random digits between 1 and 9
        //printf("%d", RandomNumber[i]); //If you want to see answer uncomment this line.
    }
    printf("\n");
    if (RandomNumber[0] == RandomNumber[1] || RandomNumber[0] == RandomNumber[2]
        || RandomNumber[0] == RandomNumber[3] || RandomNumber[1] == RandomNumber[2] || RandomNumber[1] == RandomNumber[2]
        || RandomNumber[1] == RandomNumber[3] || RandomNumber[2] == RandomNumber[3]){//checks the random number for repeated digits and zero at the beginning.
        
        //printf("Random number does not match our criterias. Generating again...\n");
        system("clear || cls");
        GenerateRandomNumber();
    }
}

static void TakeInput(){
    printf("Guess Count: %d\n",GuessCount);
    printf("Enter number here:");
    scanf("%d",&GuessNumber);
    
    if (GuessNumber >= 1000 && GuessNumber <= 9999){ //checks the number is 4-digit or not
        IsFourDigit = true;
        for (int i=3;i>=0;i--){
            int mod = GuessNumber % 10;  //Take the last digit
            SeperatedNumber[i] = mod;    //transfer last digit to array
            GuessNumber = GuessNumber / 10;  //remove the last "0" digit
        }
        if (SeperatedNumber[0] == SeperatedNumber[1] || SeperatedNumber[0] == SeperatedNumber[2]
            || SeperatedNumber[0] == SeperatedNumber[3] || SeperatedNumber[1] == SeperatedNumber[2] || SeperatedNumber[1] == SeperatedNumber[2]
            || SeperatedNumber[1] == SeperatedNumber[3] || SeperatedNumber[2] == SeperatedNumber[3]){ //checks the user guess is matching our criterias or not
            
            printf("Please do not use same numbers in the input!\n");
            printf("\n");
            TakeInput();
        }

    }else {
        printf("Please enter 4-digit number!\n\n");
        IsFourDigit = false;
    }
    
    
}

static void Compare(){
    
    for (int i=0;i<4;i++){
        if (SeperatedNumber[i] == RandomNumber[i]){ //checks digits in the correct position or not
            PlusSign++;
            
        }else if (SeperatedNumber[i] == RandomNumber[0] || SeperatedNumber[i] == RandomNumber[1]
                  || SeperatedNumber[i] == RandomNumber[2] || SeperatedNumber[i] == RandomNumber[3]){ //checks other positions for given digit
            NegativeSign++;
        }
    }
    printf("Hint: +%d / -%d\n", PlusSign, NegativeSign);
    printf("\n");
    GuessCount++;
    
    if (PlusSign==4){ // If user guessed correctly game stops.
        GameOver = true;
    }else{
        GameOver = false;
    }
    
    PlusSign=0; NegativeSign=0; //resetting values for next usage
}


int main() {
    system("clear || cls");
    HomeScreen();
    if (GameStarted == true){
        srand((int)time(0));
        GenerateRandomNumber();
        
        while (GameOver == false){
            TakeInput();
            if (IsFourDigit == true){
                Compare();
            }
        }
        
        if (GameOver == true){
            printf("Congratulations!\nYou found the number correctly with %d guesses!\n", GuessCount);
            
            GameStarted = false;
        }
    }
 
    return 0;
}
