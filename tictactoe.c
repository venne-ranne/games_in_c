#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tictactoe.h"
#include "guessgame.h"
#define WIN_PIECES 3    /* the number of 'X' or 'O' in a row for win */

int tictaetoe_game(){
    int size = -1, cont_game, pos_x, pos_y;
    char input[10];  /* read the user input */
    char player = 'A';
			pos_x = -1, pos_y = -1;
    printf("Enter the size of field (only range from 3-10): ");
    scanf("%d", &size);
    // only size between 3 and 10 is accepted
    while (size < 3 || size > 10){
        printf("Only enter a number between 3 and 10: ");
        scanf("%d", &size);
    }
    getchar();
	
    // create the 2D board based on the given size
    // initialise the board with SPACEs
    char board[size][size];
    reset_board(size, board);
	
    // continue if the game is not solved yet and still have empty spaces
    while (is_solved(size, board) != 1 && is_game_over(size, board) != 1){
        printf("Player %c [COL ROW or Q to quit]: ", player);
        
        // read the user input
        cont_game = get_position(player, input);
        if (cont_game == 0){
	  ask_save_game(size, board);
          return 0;		
        } else{
            pos_x = input[0] - '0';
            pos_y = input[2] - '0';
        }

        // only redraw the board if it is successfully added
        if (add_cross(size, board, pos_x, pos_y, player) == 1){
            draw(size, board);
        }
		
        // check if the added cross win the game or not
        if (is_solved(size, board) == 1){
            printf("Player %c won!\n", player);
            cont_game = restartGame();
            if (cont_game == 1){
                reset_board(size, board);
                player = 'B';
            } else return 0;
        }
        player = player != 'A' ? 'A' : 'B';     // change player for next round
    }

    draw(size, board);
    printf("Game Over!!! It's a draw.\n");
    return 0;
}

/*
 * Function: reset_board
 * ----------------------------
 * Reset the board with SPACEs.
 */
void reset_board(const int size, char field[][size]){
    for (int i = 0; i < size; i++){
        for (int j =0; j < size; j++){
            field[i][j] = ' ';
        }
    }
    draw(size, field); // draw the 2D board
}

/*
 * Function: get_position
 * ----------------------------
 * Get the values of column and row that entered by the user.
 */
int get_position(const char player, char input[]){
    while (1 == 1){
        fgets(input, 10, stdin);
        if (strlen(input) == 2 && (input[0] == 'Q' || input[0] == 'q')){
            return 0;
        } else if (strlen(input) > 4 || strlen(input) < 4 || isalpha(input[0])){
            printf("Invalid input. Enter the column and row only.\n");
            printf("Player %c [COL ROW or Q to quit]: ", player);
        } else {
            return 1;
        }
    }
}

/*
 * Function: draw
 * ----------------------------
 * Draws the current 2D board (starts from the top right).
 */
void draw(const int size, char field[][size]){
    printf("\n");
    drawBorder_line(size);

    // add the values in the 2D array
    for (int r = size-1; r >= 0; r--){
        printf("%d ", r+1);
        for (int c = 0; c < size; c++){
            printf("|%c", field[r][c]);
        }
        printf("|\n");  // the end of the board
        drawBorder_line(size);
    }
	
    // draw the number labels
    printf("  ");
    for (int i = 1; i <= size; i++) printf(" %d", i);
    printf("\n");
}

/*
 * Function: drawBorder_line
 * ----------------------------
 * Draws the border line of the board.
 */
void drawBorder_line(const int size){
    printf("  ");
    for (int i = 0; i < size; ++i) printf("+-");
    printf("+\n");
}

/*
 * Function: add_cross
 * ----------------------------
 * Add a cross to the board based on the given position. The given position must
 * within the index range of the board.
 *
 * returns: -1 if the given position is out of bound, 1 if successfully added to the board,
 * or 0 if the position is occupied
 */
int add_cross(const int size, char field[][size], const int x, const int y, const char player){
    if (x <= 0 || x > size || y <= 0 || y > size){
        printf("Wrong position!\n");
        return -1;
    }
	
    if (player == 'A'){
        if (field[y-1][x-1] != 'X' && field[y-1][x-1] != 'O'){
            field[y-1][x-1] = 'X';
            return 1;
        }
    } else {
        if (field[y-1][x-1] != 'X' && field[y-1][x-1] != 'O'){
            field[y-1][x-1] = 'O';
            return 1;
        }
    }
	
    printf("%c is already there!\n", field[y-1][x-1]);
    return 0;
}

/*
 * Function: is_solved
 * ----------------------------
 * To check whether the current game is already solved or not.
 * The board must contains three 'X' in a row for winning.
 *
 * returns: 1 if the board is solved, otherwise 0.
 */
int is_solved(const int size, char field[][size]){
    if (is_row_contains(size, field) == 1 || is_col_contains(size, field) == 1){
        return 1;
    }
    return 0;
}

/*
 * Function: is_game_over
 * ----------------------------
 * To check whether the current game is still have empty places left.
 *
 * returns: 1 if it is game over, otherwise 0.
 */
int is_game_over(const int size, char field[][size]){
    for (int r = size-1; r >= 0; r--){
        for (int c = 0; c < size; c++){
            if (field[r][c] == ' ') return 0;
        }
    }
    return 1;
}


/*
 * Function: is_row_contains
 * ----------------------------
 * Go through row by row (from top to bottom) to check if a row
 * has at least three 'X' in a row. While going through the rows, it
 * will check the diagonal direction (downward right) at the same time.
 *
 * returns: 1 if it is solved, otherwise 0.
 */
int is_row_contains(const int size, char field[][size]){
    char current_pcs, next_pcs;
    int count;
	
    for (int r = size-1; r >= 0; r--){
        current_pcs = field[r][0];
        count = current_pcs != ' ' ? 1 : 0;
        for (int c = 0; c < size-1; c++){
            next_pcs = field[r][c+1];
			
            // check if the diagonal (downward right) contains three 'X' or not
            if (is_diagonal_contains(size, field, c, r) ==  1 && current_pcs != ' '){
                return 1;
            }

            // if the current piece is same as the next piece, which is on the right side,
            // and both are not SPACE, then incremmet the count
            // otherwise reset the counter
            if (current_pcs == next_pcs && current_pcs != ' ')
                count++;
            else count = 0;
			
            if (count >= WIN_PIECES) return 1;
			
            // update the current_pcs with the next_pcs
            // update the counter when it was reset and the next_pcs is not a SPACE
            current_pcs = field[r][c+1];
            count = (count == 0 && current_pcs != ' ') ? 1 : count;
        }
    }
    return 0;
}

/*
 * Function: is_col_contains
 * ----------------------------
 * Go through column by column (from left to right) to check if a column
 * has at least three 'X' in a column. While going through the columns, it
 * will check the non-diagonal direction (upward right) at the same time.
 *
 * returns: 1 if it is solved, otherwise 0.
 */
int is_col_contains(const int size, char field[][size]){
    char current_pcs, next_pcs;
    int count;
	
    for (int c = 0; c < size; c++){
        current_pcs = field[0][c];
        count = current_pcs != ' ' ? 1 : 0;
        for (int r = 0; r < size-1; r++){
            next_pcs = field[r+1][c];
			
            // check if the diagonal (upward right) contains three 'X' or not
            if (is_anti_diagonal_contains(size, field, c, r) == 1  && current_pcs != ' '){
                return 1;
            }

            // if the current piece is same as the next piece, which is on the right side,
            // and both are not SPACEs, then incremmet the count
            // otherwise reset the counter
            if (current_pcs == next_pcs && current_pcs != ' ')
                count++;
            else count = 0;
			

            if (count >= WIN_PIECES) return 1;
			
            // update the current_pcs with the next_pcs
            // update the counter when it was reset and the next_pcs is not a SPACE
            current_pcs = field[r+1][c];
            count = (count == 0 && current_pcs != ' ') ? 1 : count;
			
        }
    }
    return 0;
}

/*
 * Function: is_diagonal_contains
 * ----------------------------
 * Go through diagonally (downward right) direction from the given x and y indices, and check
 * if it has at least three 'X' in a non-diagonal direction.
 * This function will only check to the maximum pieces to win from the given indices,
 * and if the given indices is a SPACE then it will not continue.
 * e.g. the given indices is c=0, r=3 (array's index), then last one to check is c=2, r=1
 * since it is checking the next piece in the loop.
 *
 * returns: 1 if it is solved, otherwise 0.
 */
int is_diagonal_contains(const int size, char field[][size], int pos_x, int pos_y){
    // check if it is within the range or not
    if (pos_x+(WIN_PIECES-1) >= size || pos_y-(WIN_PIECES-1) < 0){
        return 0;
    }
	
    char current_pcs = field[pos_y][pos_x];
    char next_pcs;
    int count = current_pcs != ' ' ? 1 : 0;
	
    for (int i = 1; i < WIN_PIECES; i++){
        next_pcs = field[pos_y-i][pos_x+i];
		
        // if the current piece is same as the next piece, which is on the downward right side,
        // and both are not SPACEs, then incremmet the count
        // otherwise reset the counter
        if (current_pcs == next_pcs && current_pcs != ' ')
            count++;
        else count = 0;

        if (count >= WIN_PIECES) return 1;
		
        // update the current_pcs with the next_pcs
        current_pcs = field[pos_y-i][pos_x+i];
    }
    return 0;
}

/*
 * Function: is_anti_diagonal_contains
 * ----------------------------
 * Go through anti-diagonally (upward right) direction from the given x and y indices, and check
 * if it has at least three 'X' in a non-diagonal direction.
 * This function will only check to the maximum pieces to win from the given indices,
 * and if the given indices is a SPACE then it will not continue.
 * e.g. the given indices is c=0, r=0 (array's index), then last one to check is c=2, r=2
 * since it will is checking the next piece in the loop.
 *
 * returns: 1 if it is solved, otherwise 0.
 */
int is_anti_diagonal_contains(const int size, char field[][size], int pos_x, int pos_y){
    // check if it is within the range or not
    if (pos_x+(WIN_PIECES-1) >= size || pos_y+(WIN_PIECES-1) >= size){
        return 0;
    }
	
    char current_pcs = field[pos_y][pos_x];
    char next_pcs;
    int count = current_pcs != ' ' ? 1 : 0;
	
    for (int i = 1; i < WIN_PIECES; i++){
        next_pcs = field[pos_y+i][pos_x+i];
		
        // if the current piece is same as the next piece, which is on the upward right side,
        // and both are not SPACEs, then incremmet the count
        // otherwise reset the counter
        if (current_pcs == next_pcs && current_pcs != ' ')
            count++;
        else count = 0;
		

        if (count >= WIN_PIECES) return 1;
		
        // update the current_pcs with the next_pcs
        current_pcs = field[pos_y+i][pos_x+i];
    }
    return 0;
	
}

/**
 * Ask if the user want to save the current game or not before quitting the game.
 * @param game reference to the game object
 */
void ask_save_game(const int size, char field[][size]){
    char input[10];
    printf("Do you want to save game [Y/N]: ");
	
    while(1 == 1){
        fgets(input, 10, stdin);
        if (strlen(input) > 2){
            printf("Player (Y or N key only): ");
        } else if (input[0] == 'Y' || input[0] == 'y'){
            FILE *fp;
            fp = fopen("tictactoe_game.txt", "w");
            if (save_tictactoe_game(size, field, fp)){
                printf("Game saved under \"tictactoe_game.txt.\"\n");
            }
            return;
        } else if (input[0] == 'N' || input[0] == 'n'){
            return;
        } else {
            printf("Player (Y or N key only): ");
        }
    }
}

bool save_tictactoe_game(const int size, char field[][size], FILE *file){
    int row, col, i;
    char *str;
	
    str = (char *) malloc(24);
	
    if (file == NULL){
        printf("Saving error!");
        return false;
    }
    
    // saved the current board as string
    for (row = 0, i = 0; row < size; row++){
        for(col = 0; col < size; col++){
            str[i++] = (field[row][col] == ' ') ? 'T':field[row][col];
        }
    }
	
    str[i] = '\0'; /* to terminate string properly */
    
    // save the string of the game state and score
    fprintf(file,"%s", str);
    free(str);
    fclose(file);
    return true;

}
