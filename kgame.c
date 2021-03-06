#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "k.h"

#define INPUT_SIZE 30

char input[INPUT_SIZE]; /* read the user input */

int start_k_game(){
    struct game game;
    struct game *pgame = &game;
    int slide_dir, row, col;
    bool add_new_tile, has_updated;

	// initialise the score & the board with SPACEs
	for (row = 0; row < SIZE; row++){
		for(col = 0; col < SIZE; col++){
			game.board[row][col] = ' ';
		}
	}
	game.score = 0;
	
	  printf("\n***************** WELCOME TO K-GAME *****************\n");
		printf("Instruction: Use WASD keys to slide.\n");
	
    add_new_tile = start_new_game(pgame);
    has_updated = true;
	
    while(is_move_possible(game) || has_empty_tile(game)){
        if (has_empty_tile(game) && add_new_tile && has_updated){
            add_random_tile(pgame);
        }
			
        if (has_updated){
            printf("  Score: %d", game.score);
            render(game);
        } 
		
	// get the slide direction from stdin	
        slide_dir = direction_to_slide();
        if(slide_dir == 5){
					return 0;
        } else if (slide_dir == 1 || slide_dir == 2){
            has_updated = update(pgame, slide_dir == 1 ? -1:1, 0);
        } else {
            has_updated = update(pgame, 0, slide_dir == 3 ? -1:1);
        }
		
        // check if the game is win or not
        // then ask if want to start a new game or not
        if (is_game_won(game) && has_updated){
            render(game);
            printf("Congratulation! You won!\n");
            reset_game_board(pgame);
            start_new_game(pgame);
        }
        add_new_tile = true;
    }

    render(game);
    printf("You run out of moves. Game over!\n");
    return 0;
}

void reset_game_board(struct game *game){
	 int row, col;
    // initialise the score & the board with SPACEs
    for (row = 0; row < SIZE; row++){
        for(col = 0; col < SIZE; col++){
            game->board[row][col] = ' ';
        }
    }
    game->score = 0;
}


/**
 * Reads the command from the user. Check if the player want to start a new game
 * or open an existing file. 
 * @param game reference to the game object
 * @return true, if a new game is start, otherwise false.
 */
bool start_new_game(struct game *game){
    printf("To start a new game, press ENTER key.\n");
    printf("To continue a saved game, press 'C' key.\n");
    printf("Command [ENTER/C]: ");
    fgets(input, INPUT_SIZE, stdin);
	
    while(1 == 1){
        if (input[0] == 10 && strlen(input) == 1){
            return true;
        } else if ((input[0] == 'C' || input[0] == 'c') && strlen(input) == 2){
            // open a file and read the saved game
            FILE *fp;
            fp = fopen("saved_game.txt", "r");
            return read_saved_game(game, fp);
				} else {
            printf("Command [ENTER/C key only]: " );
            fgets(input, INPUT_SIZE, stdin);	
        }
    }
}

/**
 * Reads the slide direction that the player entered. 
 * Returns an integer between 1 and 4 based on the direction slide.
 * @param game reference to the game object
 * @return 1, if the slide direction is up,
 * @return 2, if the slide direction is down,
 * @return 3, if the slide direction is left,
 * @return 4, if the slide direction is right,
 */
int direction_to_slide(const struct game game){
    printf("Player [WASD to slide/Q to quit]: ");
    fgets(input, INPUT_SIZE, stdin);
	
    while (1 == 1){
        if (!isalpha(input[0])){
            fgets(input, INPUT_SIZE, stdin);
        } else if (strlen(input) > 2){
            printf("Player [WASD key to slide/Q to quit]: ");
            fgets(input, INPUT_SIZE, stdin);
        } else {
            if (input[0] == 'W' || input[0] == 'w'){
                return 1;
            } else if (input[0] == 'S' || input[0] == 's'){
                return 2;
            } else if (input[0] == 'A' || input[0] == 'a'){
                return 3;
            } else if (input[0] == 'D' || input[0] == 'd'){
                return 4;
            } else if (input[0] == 'Q' || input[0] == 'q'){
                save_game_before_quit(game);
                return 5;
            } else {
                printf("Player (WASD or Q key only): " );
                fgets(input, INPUT_SIZE, stdin);
            }
        }
    }
}

/**
 * Ask if the user want to save the current game or not before quitting the game.
 * @param game reference to the game object
 */
void save_game_before_quit(const struct game game){
    printf("Do you want to save game [Y/N]: ");
    fgets(input, INPUT_SIZE, stdin);
	
    while(1 == 1){
        if (strlen(input) > 2){
            printf("Player (Y or N key only): ");
            fgets(input, INPUT_SIZE, stdin);
        } else if (input[0] == 'Y' || input[0] == 'y'){
            FILE *fp;
            fp = fopen("kgame.txt", "w");
            if (save_game(game, fp)){
                printf("Game saved under \"kgame.txt.\"\n");
            }
            return;
        } else if (input[0] == 'N' || input[0] == 'n'){
            return;
        } else {
            printf("Player (Y or N key only): ");
            fgets(input, INPUT_SIZE, stdin);
        }
    }
}

