int tictaetoe_game();
void draw(const int size, char field[][size]);
void reset_board(const int size, char field[][size]);
void drawBorder_line(const int size);
int get_position(const char player, char input[]);
int is_solved(const int size, char field[][size]);
int is_game_over(const int size, char field[][size]);
int add_cross(const int size, char field[][size], const int x, const int y, const char player);
int is_row_contains(const int size, char field[][size]);
int is_col_contains(const int size, char field[][size]);
int is_diagonal_contains(const int size, char field[][size], int pos_x, int pos_y);
int is_anti_diagonal_contains(const int size, char field[][size], int pos_x, int pos_y);
void ask_save_game(const int size, char field[][size]);
bool save_tictactoe_game(const int size, char field[][size], FILE *file);
