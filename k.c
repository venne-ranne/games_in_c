#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
	
    do{
       row = rand() % 4;
       col = rand() % 4;
    } while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    int tile = 'A' + (rand() % 2);
    game->board[row][col] = tile;
}

void render(const struct game game){
    int row, col;
	
    drawBorder(SIZE);
    for (row = 0; row < SIZE; row++){
        printf("  |");
        for(col = 0; col < SIZE; col++){
            printf(" %c |", game.board[row][col]);
        }
        drawBorder(SIZE);
    }
}

void drawBorder(const int size){
    printf("\n  ");
    for (int i = 0; i < size; ++i){
        printf("+---");
    }
    printf("+\n");
}

bool is_move_possible(const struct game game){
    char right_tile, bottom_tile, current_tile;
    int row, col;
	
    // check the board from left to right starting the top row.
    // check two adjacent tiles at once (right and bottom pieces of the current_tile)
    for (row = 0; row < SIZE-1; row++){
        for(col = 0; col < SIZE; col++){
            current_tile = game.board[row][col];
            right_tile = (col == SIZE-1)? 'X': game.board[row][col+1];
            bottom_tile = game.board[row+1][col];
            if (current_tile == ' ' || right_tile == ' ' || bottom_tile == ' '){
                return true;
            } else if (current_tile == right_tile || current_tile == bottom_tile){
                return true;
            }
        }
    }
    return false;
}

bool is_game_won(const struct game game){
    int row, col;

    // check the board from left to right starting the top row.
    for (row = 0; row < SIZE; row++){
        for(col = 0; col < SIZE; col++){
            if (game.board[row][col] == 'K'){
                return true;
            }
        }
	}
	
    return false;
}


bool update_on_x(struct game *game, int start_x, int end_x){
    int row, col, i, j, score;
    char tile, next_tile;
    bool is_updated, is_shifted;

    i = start_x == 0 ? 1:-1;
    is_updated = false,
    is_shifted = false;
	
    for (row = 0; row != SIZE; row++){
        is_shifted = (shift_tiles_on_x(game, start_x, end_x+i, row) || is_shifted) ? true: false;
        for (col = start_x; col != end_x; (start_x == 0) ? col++:col--){
            tile = game->board[row][col];
            next_tile = game->board[row][col+i];
			
            // since the SPACEs between the tiles of a row is shifted
            // e.g. |A| |C|D| --> |A|C|D| |
            // So, if the next tile is SPACE, then stops updating
            if (next_tile == ' ') break;
            if (tile == next_tile){
                game->board[row][col] = game->board[row][col]+1;
                game->board[row][col+i] = ' '; // replaced the merged tile with SPACE
                // game->score += (int)(pow(2.0, tile-64.0)*2); // update the current score
                score = 2;
                for (j = 1; j < tile-64; j++){
                    score = score * 2;
		}
                game->score += score;
                shift_tiles_on_x(game, start_x, end_x+i, row);
                is_updated = true;
            }
			
        }
    }
    return (is_updated || is_shifted);
}

bool update_on_y(struct game *game, int start_y, int end_y){
    int row, col, i, j, score;
    char tile, next_tile;
    bool is_updated, is_shifted;
	
    i = start_y == 0 ? 1:-1;
    is_updated = false,
    is_shifted = false;
    j = 0;
	
    for (col = 0; col != SIZE; col++){
        is_shifted = (shift_tiles_on_y(game, start_y, end_y+i, col) || is_shifted) ? true: false;
        for (row = start_y; row != end_y; (start_y == 0) ? row++:row--){
            tile = game->board[row][col];
            next_tile = game->board[row+i][col];
			
            // since the SPACEs between the tiles of a column is shifted
            // e.g. |A| |C|D| --> |A|C|D| |
            // So, if the next tile is SPACE, then stops updating
            if (next_tile == ' ') break;
            if (tile == next_tile){
                game->board[row][col] = game->board[row][col]+1;
                game->board[row+i][col] = ' '; // replaced the merged tile with SPACE
                score = 2;
                for (j = 1; j < tile-64; j++){
                    score = score * 2;
		}
                //game->score += (int)(pow(2.0, tile-64.0)*2); // update the current score
                game->score += score;
                shift_tiles_on_y(game, start_y, end_y+i, col);
                is_updated = true;
            }
			
        }
    }
    return (is_updated || is_shifted);
}

bool update(struct game *game, int dy, int dx){
    bool has_updated;
	
    // first, get rid the SPACEs between the tiles
    // then updated the board
    if (dy == -1 && dx == 0){
        has_updated = update_on_y(game, 0, SIZE-1);
    } else if (dy == 1 && dx == 0){
        has_updated = update_on_y(game, SIZE-1, 0);
    } else if (dy == 0 && dx == -1){
        has_updated = update_on_x(game, 0, SIZE-1);
    } else {
        has_updated = update_on_x(game, SIZE-1, 0);
    }
    return has_updated;
}

bool shift_tiles_on_y(struct game *game, int start_y, int end_y, int col){
    int i, row;
    char tile;
    bool is_shifted;
	
    for (row = start_y, i = start_y, is_shifted = false;
        row != end_y; (start_y == 0)?row++:row--){
        tile = game->board[row][col];
        
        // if the tile is not a SPACE,
        // then put current tile to the i position
        // and increment/decrement i based on the direction for the next insert
        if (tile != ' '){
            if (row != i) is_shifted = true;
            game->board[row][col] = ' '; // convert the current tile to SPACE
            game->board[start_y == 0 ? i++:i--][col] = tile; // increment/decrement base on the direction
        }
    }
    return is_shifted;
}

bool shift_tiles_on_x(struct game *game, int start_x, int end_x, int row){
    int i, col;
    char tile;
    bool is_shifted;
	
    for (col = start_x, i = start_x, is_shifted = false;
        col != end_x; (start_x == 0)?col++:col--){
        tile = game->board[row][col];
			
		  // if the tile is not a SPACE,
        // then put current tile to the i position
        // and increment/decrement i based on the direction for the next insert       
        if (tile != ' '){
            if (col != i) is_shifted = true;
            game->board[row][col] = ' ';  // convert the current tile to SPACE
            game->board[row][start_x == 0 ? i++:i--] = tile; // increment/decrement base on the direction
        }
    }
    return is_shifted;
}

bool has_empty_tile(const struct game game){
    int row, col;
	
    for (row = 0; row < SIZE; row++){
        for(col = 0; col < SIZE; col++){
            if (game.board[row][col] == ' '){
                return true;
            }
        }
    }
    return false;
}

bool save_game(const struct game game, FILE *file){
    int row, col, i;
    char *str;
	
    str = (char *) malloc(24);
	
    if (file == NULL){
        printf("Saving error!");
        return false;
    }
    
    // saved the current board as string
    for (row = 0, i = 0; row < SIZE; row++){
        for(col = 0; col < SIZE; col++){
            str[i++] = (game.board[row][col] == ' ') ? 'X':game.board[row][col];
        }
    }
	
    str[i] = '\0'; /* to terminate string properly */
    
    // save the string of the game state and score
    fprintf(file,"%s %d", str, game.score);
    free(str);
    fclose(file);
    return true;
}

bool read_saved_game(struct game *game, FILE *file){
    int row, col, i;
    char ch;
    char *str;
    bool add_tile = true;  /* use to return if needed to add_tile */

    // check the file is exist or not
    if (file == NULL){
        printf("Reading error. File not found.\n");
        fclose(file);
        return add_tile;
    }

    // read the file, firstly, read the saved game
    // then read the score
    str = (char *) malloc(24);
    fscanf(file,"%s %d", str, &game->score);
	
    for (i = 0, row = 0, col = 0; i <strlen(str); i++){
        ch = str[i];
        if (ch == 'X'){   // this means the tile is space
            game->board[row][col++] = ' ';		
        } else if (ch != '\n'){
            game->board[row][col++] = ch;
            add_tile = false;  // this means don’t need to add a tile before the player slide
        }
		
        if (col >= SIZE){
            col = 0;
            row++;
        }
    }
	
    free(str);
    fclose(file);
    return add_tile;
}
