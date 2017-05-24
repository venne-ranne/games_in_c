#include <stdbool.h>
#define SIZE 4

struct game {
    // game board
    char board[SIZE][SIZE];
    // current score
    int score;
};

/**
 * Adds random A or B tile to the game. This is very dumb function. 
 * The board must have at least one empty tile.
 * If there is no empty tile, function will end in infinite loop.
 * @param game reference to the game object
 */
void add_random_tile(struct game *game);


/**
 * Renders the game
 * @param game the game object with board and score to render
 */
void render(const struct game game);

/**
 * Shifts the tiles either left or right direction so that there is no spaces 
 * between the tiles. Returns true if at least one tile is moved from its 
 * original position, otherwise false.
 * @param game the game object with board to check
 * @param start_x where to start in x-axe
 * @param end_x where to end in x-axe
 * @return true, if the board was shifted, or false otherwise.
 */
bool shift_tiles_on_x(struct game *game, int start_x, int end_x, int row);

/**
 * Shifts the tiles either up or down direction so that there is no spaces 
 * between the tiles. Returns true if at least one tile is moved from its 
 * original position, otherwise false.
 * @param game the game object with board to check
 * @param start_y where to start in y-axe
 * @param end_y where to end in y-axe
 * @return true, if the board was shifted, or false otherwise.
 */
bool shift_tiles_on_y(struct game *game, int start_y, int end_y, int col);

/**
 * Makes move in given direction
 * If it is possible, function makes move in given direction,
 * updates the current game state (board and score) and returns
 * true. If it is not
 * possible to move, returns false.
 * @param game reference to the game object
 * @param dy movement in y-axe
 * @param dx movement in x-axe
 * @return true, if game state was updated, false otherwise
 */
bool update(struct game *game, int dy, int dx);

/**
 * Checks whether it is possible to make move
 * Function checks game board if it is possible to make another
 * move. The move is possible, if there are two tiles with the 
 * same letter nearby or there is at least one empty tile.
 * @param game the game object with board to check
 * @return true, if another movement is possible, or false otherwise.
 */
bool is_move_possible(const struct game game);


/**
 * Checks whether game is already won.
 * Returns true, if tile with letter 'K' is located on the board. Returns
 * false, if it is not.
 * @param game the game object with board to check
 * @return true, if game is won, or false otherwise.
 */
bool is_game_won(const struct game game);

/* Extra functions */

/**
 * Checks if the board has an empty space or not. 
 * Returns true if at least one tile is empty, otherwise false.
 * @param game the game object with board to check
 * @return true, if the board has an empty space, or false otherwise.
 */
bool has_empty_tile(const struct game game);

/**
 * Draws the border line on the board based on the number of columns.
 * @param size the width of the board.
 */
void drawBorder(const int size);

/**
 * Updates the current board based on the slide direction either left or right.
 * If it is possible, function makes move in given direction, updates 
 * the current game state (board and score) and returns true.
 * If it is not possible to move, returns false.
 * @param game reference to the game object
 * @param start_x the first position in x-axe
 * @param start_x the last position in x-axe
 * @return true, if game state was updated, false otherwise
 */
bool update_on_x(struct game *game, int start_x, int end_x);

/**
 * Updates the current board based on the slide direction either up or down.
 * If it is possible, function makes move in given direction, updates 
 * the current game state (board and score) and returns true.
 * If it is not possible to move, returns false.
 * @param game reference to the game object
 * @param start_y the first position in y-axe
 * @param start_y the last position in y-axe
 * @return true, if game state was updated, false otherwise
 */
bool update_on_y(struct game *game, int start_y, int end_y);

/**
 * Write the current game state into a file. Returns true if 
 * the game is successfully saved, or otherwise false.
 * @param game reference to the game object
 * @param file the file to use for saving
 * @return true, if the game was written to the file, false otherwise
 */
bool save_game(const struct game game, FILE *file);

/**
 * Read a game from a file. Returns true if the game is not updated 
 * or all tiles are empty. Returns false if the game is successfully 
 * updated and at least one tile is alphabet.
 * @param game reference to the game object
 * @param file the file to read
 * @return true, if game was not updated or all tiles are SPACEs, false otherwise.
 */
bool read_saved_game(struct game *game, FILE *file);

int start_k_game();
bool start_new_game(struct game *game);
int direction_to_slide();
void save_game_before_quit(const struct game game);
