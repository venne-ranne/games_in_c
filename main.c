﻿#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include "k.h"

void display_game_menu();
int reading_selection(int num_selection);

int main(){
	int cont_main_menu, selection;
	
	printf("\n----------Welcome to Games in C----------\n");
	printf("Choose one of the following options: \n");
	
	cont_main_menu = 1;
	
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

void display_game_menu(){
	int cont_game_menu, selection;
	
	cont_game_menu = 1;
	
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
			int tictaetoe_game();
		} else if (selection == 3){
			start_k_game();
		}
	}
}

int reading_selection(int num_selection){
	char input[10];  /* read the user input */
	int digit;
	
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

