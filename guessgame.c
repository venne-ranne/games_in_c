#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "guessgame.h"

#define MAX_ATTEMPT 5
#define START 1
#define END 100

/*
 * This function returns 1 if the user want to restart a new game, 
 * otherwise it will exit the program. Only options y/Y/n/N are recognized.
 */
int restartGame(){
    char ch;
    printf("Play again? [Y/N]: ");
    
    while (1 == 1){
        if (!isalpha(ch)){
            ch = getchar();
    	} else {
            if (ch == 'Y' || ch == 'y'){
                return 1;
            } else if (ch == 'N' || ch == 'n'){
                getchar();
                printf("See you later!\n");
                return 0;
            } else {
                printf("Play again? [Y/N]: ");
                ch = getchar();
            }
        }
    }
}

/*
 * This function will return a randomly generated number in the interval start-end.
 */
int get_secret(const int start, const int end){
    /* Intializes random number generator */
    srand(time(NULL));
    return (rand() % end) + start;
}

/*
 * This function returns the guess number from the user input.
 */
int get_guess(const int attempt){
    char input[10];
    int guess;
    printf("Your %d. guess: ", attempt);
    scanf("%d", &guess);
    return guess;

}

/*
 * This function checks if the game is win or not. Returns 1 if the game is won, otherwise 0.
 * It will also print out the result of the guess.
 */
int has_game_won(const int secret, const int guess){
    // if the guess number is correct or not
    if (guess == secret){
        printf("Congratulation! You found it!\n");
        return 1;
    } 

    // print out the result of the guess
    if (guess > secret) printf("Hmm... My number is smaller than yours.\n");
    else printf("Hmm... My number is bigger than yours.\n");
    
    return 0;
}

int start_guess_game(){
    int guessNumber, secretNumber, i, cont_game;
	
    for (i = 1; i <= MAX_ATTEMPT; i++){
        /* if it is the first round, generate the secret number */
        if (i == 1){
            printf("Pick a number between %d and %d. You have max. %d attempts.\n", START, END, MAX_ATTEMPT);
            secretNumber = get_secret(START, END);
        }
        
        guessNumber = get_guess(i);
        
        // if the game is won or max attempts are used, 
        // then ask if the user want to restart the game or not
        if (has_game_won(secretNumber, guessNumber) == 1){
            cont_game = restartGame();
            if (cont_game == 1) i = 0;
            else return 0;
        } else if (i == MAX_ATTEMPT){
            printf("Game over. My number was %d\n", secretNumber);
            cont_game = restartGame();
            if (cont_game == 1) i = 0;
            else return 0;
        }
     }
     return 0;
}
