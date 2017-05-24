#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include "k.h"
#include "tictactoe.h"
#include "guessgame.h"

void display_game_menu();
int reading_selection(int num_selection);

int main(){
     int cont_main_menu, selection;
	
     printf("\n----------Welcome to Games in C----------\n");
     printf("Let’s play a game in C! We have a selection of games: \n");
     printf("Guess My Number, Tic Tac Toe and K-Game games.\n");
     printf("Instruction: To quit any game, press 'Q' key. \n");
     printf("Choose one of the following options: \n");
	
     cont_main_menu = 1;    // represents if the program still running or not
	
     while (cont_main_menu == 1){
          printf("----------------Main Menu----------------\n");
          printf("|	1. Select A Game		|\n");
          printf("|	2. Quit				|\n");
          printf("-----------------------------------------\n");
          printf("Your selection: ");
          selection = reading_selection(2);
          if (selection == 1){
               display_game_menu();					
          } else{
               cont_main_menu = 0;		
          }
     }	
     return 0;
}

/*
 * Function: display_game_menu
 * --------------------------------
 * Display the game menu selection.
 */
void display_game_menu(){
     int cont_game_menu, selection;
	
     cont_game_menu = 1;    // represents if the user still on game menu or not
	
     while (cont_game_menu == 1){
          printf("----------------Game Menu----------------\n");
          printf("|	1. Guess My Number		|\n");
          printf("|	2. Tic Tac Toe			|\n");
          printf("|	3. K-Game			|\n");
          printf("|	4. Go Back Main Menu		|\n");
          printf("-----------------------------------------\n");
          printf("Your selection: ");
          selection = reading_selection(4);
		
          if (selection == 4){
               cont_game_menu = 0;		
          } else if (selection == 2){
               tictaetoe_game();
          } else if (selection == 3){
               start_k_game();
          } else {
               start_guess_game();
          }
     }
}

/*
 * Function: eading_selection
 * ----------------------------
 * Read the user input based on the number of options in the menu.
 * Will only return until the user put the right option number.
 * @param num_selection the number of option in the menu
 * @return the number of selection from the menu
 */
int reading_selection(int num_selection){
     char input[10];  /* read the user input */
     int digit;      /* the number selection */
	
     while (1 == 1){
          fgets(input, 10, stdin);
          if (strlen(input) > 2){
               printf("Invalid input. Enter the available options. \n");
               printf("Your selection: "); 
          } else if (isalpha(input[0])){
               printf("Your selection: (require an int)");
          } else {
               digit = input[0] - '0';
               if (digit >= 1 && digit <= num_selection){
                    return digit;
               } else {
                    printf("Invalid input. Enter the available options. \n");
                    printf("Your selection: ");
               }
          }
     }
}

