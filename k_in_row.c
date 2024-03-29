#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_COLS 7

void print_board(char board[][MAX_COLS], int rows, int cols);

void print_get_row();

int scan_row();

void print_get_column();

int scan_column();

void print_error_number_of_rows();

void print_error_number_of_cols();

void print_get_k();

void print_error_k(int correct_k);

void print_player_enter_col(char player_symbol);

void print_invalid_input(char player);

void print_column_full();

void print_draw_msg();

void print_win_msg(char player_symbol, int turn_num);

int get_min(int col, int row);

int scan_k(int col, int row);

char game_start(char board[][MAX_COLS], int rows, int cols,
                int *a_counter, int k);

void scan_player_input(char board[][MAX_COLS], int col, int rows, char player);

bool is_column_full(char board[][MAX_COLS], int input, int rows, char player);

void set_cell(char board[][MAX_COLS], int input, int rows, char player);

bool someone_won(char board[][MAX_COLS], int k, int rows, int cols, char p);

bool draw(char board[][MAX_COLS], int cols);

bool check_vertical(char board[][MAX_COLS], int k, int row, int cols, char p);

bool check_horizontal(char board[][MAX_COLS], int k, int row, int cols, char p);

bool check_diagonal_1(char board[][MAX_COLS], int k, int row, int cols, char p);

bool check_diagonal_2(char board[][MAX_COLS], int k, int row, int cols, char p);

bool check_diagonal_3(char board[][MAX_COLS], int k, int row, int cols, char p);

bool check_diagonal_4(char board[][MAX_COLS], int k, int row, int cols, char p);

void set_matrix(char board[][MAX_COLS], int row, int column);

int main() {
    int row, column, k, counter = 0;
    // int *a_counter = &counter;
    char winner;
    row = scan_row(); // Scan the value of the row.
    column = scan_column(); // Scan the value of the column.
    k = scan_k(column, row); // Scan the value of k.

    // Dynamic allocation of the length of the array.
    char board[MAX_COLS][MAX_COLS] = { {0} } ;
    set_matrix(board, row, column);

    // Let the game begin.
    winner = game_start(board,row , column, &counter, k);

    print_win_msg(winner, counter);

    return 0;
}

// Set the value of each cell in the matrix to space.
void set_matrix(char board[][MAX_COLS], int row, int column){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
            board[i][j] = ' ';
        }
    }
}

// Scan the value of the rows in the matrix.
int scan_row(){
    print_get_row();
    int row;
    scanf(" %d", &row);
    if (row > 7){ // Check if row is greater than 7.
        print_error_number_of_rows();
    }
    return row;
}

// Scan the value of the columns in the matrix.
int scan_column(){
    print_get_column();
    int column;
    scanf(" %d", &column);
    if (column > 7){ // Check if column is greater than 7.
        print_error_number_of_cols();
    }
    return column;
}

// Get the minimum value between the column and the row.
int get_min(int col, int row){
    if (col > row){
        return row;
    }
    return col;
}

// Scan the value of k.
int scan_k(int col, int row){
    print_get_k();
    int k;
    int temp = get_min(col, row);
    scanf(" %d", &k);
    if (k <= 0){ // if k is 0 or lower set the value of k as the col or row.
        print_error_k(temp);
        return temp;
    }
    return k;
}

char game_start(char board[][MAX_COLS], int rows, int cols,
                int *a_counter, int k){
    print_board(board ,rows , cols); // Printing blank board.
    char player = 'Y';
    while(1){
        print_player_enter_col(player);
        scan_player_input(board, cols, rows, player);
        (*a_counter)++; // Counting the numbers of moves.
        print_board(board, rows, cols); // printing the board after each move.
        if(someone_won(board, k, rows, cols, player)){
            return player;
        }else if(draw(board, cols)){
            return 'D';
        }
        player = (player == 'X') ? 'Y' : 'X'; // Swap between the players.
    }
    return 0; // Shouldn't get here
}

// Check if there is a draw
bool draw(char board[][MAX_COLS], int cols){
    for (int i = 0; i < cols; i++){
        if (board[0][i] == ' '){
            return false;
        }
    }
    print_draw_msg();
    return true;
}

bool someone_won(char board[][MAX_COLS], int k, int rows, int cols, char p){
    if (check_vertical(board, k, rows, cols, p) ||
        check_horizontal(board, k, rows, cols, p) ||
        check_diagonal_1(board, k, rows, cols, p) ||
        check_diagonal_2(board, k, rows, cols, p) ||
        check_diagonal_3(board, k, rows, cols, p) ||
        check_diagonal_4(board, k, rows, cols, p)){
        return true;
    }
    return false;
}


// Check from left to right first column
bool check_diagonal_1(char board[][MAX_COLS], int k, int rows, int cols,
                      char player) {
    for (int i = 0; i < rows ; i++){
        int x = i, y = 0, counter = 0;
        while (x < rows && y < cols){
            if (board[x][y] != player){
                counter = 0;
            }else{
                counter++;
            }
            if (counter >=k){
                return true;
            }
            x++;
            y++;
        }
    }
    return false;
}

// Check from left to right first row.
bool check_diagonal_2(char board[][MAX_COLS], int k, int rows, int cols,
                      char player) {
    for (int i = 0; i < cols ; i++){
        int x = 0, y = i, counter = 0;
        while (x < rows && y < cols){
            if (board[x][y] != player){
                counter = 0;
            }else{
                counter++;
            }
            if (counter >= k){
                return true;
            }
            x++;
            y++;
        }
    }
    return false;
}

// check last column right to left
bool check_diagonal_3(char board[][MAX_COLS], int k, int rows, int cols,
                      char player) {
    for (int i = 0; i < rows ; i++){
        int x = i, y = cols - 1, counter = 0;
        while (x < rows && y >= 0){
            if (board[x][y] != player){
                counter = 0;
            }else{
                counter++;
            }
            if (counter >= k){
                return true;
            }
            x++;
            y--;
        }
    }
    return false;
}

// Check from first row right to left
bool check_diagonal_4(char board[][MAX_COLS], int k, int rows, int cols,
                      char player) {
    for (int i = 0; i < cols ; i++){
        int x = 0, y = i, counter = 0;
        while (x < rows && y >= 0){
            if (board[x][y] != player){
                counter = 0;
            }else{
                counter++;
            }
            if (counter >=k){
                return true;
            }
            x++;
            y--;
        }
    }
    return false;
}

bool check_horizontal(char board[][MAX_COLS], int k, int rows, int cols
                      ,char player){
    for (int i = 0; i < rows; i++){
        int counter = 0;
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == player){
                counter++;
            }else{
                counter = 0;
            }
            if (counter >= k){
                return true;
            }
        }
    }
    return false;
}

bool check_vertical(char board[][MAX_COLS], int k, int rows, int cols,
                    char player){
    for (int j = 0; j < cols; j++) {
        int counter = 0;
        for (int i = 0; i < rows; i++) {
            if (board[i][j] == player){
                counter++;
            }else{
                counter = 0;
            }
            if (counter >= k){
                return true;
            }
        }
    }
    return false;
}

void scan_player_input(char board[][MAX_COLS], int col, int rows, char player){
    int input;
    while (1) {
        scanf("%d", &input);
        if (col <= input || input < 0){
            print_invalid_input(player);
            continue;
        }else if(is_column_full(board, input, rows, player)) {
            print_column_full();
            print_player_enter_col(player);
            continue;
        }else {
            break;
        }
    }
}

bool is_column_full(char board[][MAX_COLS] ,int input, int rows, char player){
    if (board[0][input] == ' '){
        set_cell(board, input, rows, player);
        return false;
    }
    return true;
}

void set_cell(char board[][MAX_COLS], int input, int rows, char player){
    for (int i = rows - 1; i >= 0; i--){
        if (board[i][input] != ' '){
            continue;
        }
        board[i][input] = player;
        break;
    }
}

void print_get_row(){
    printf("Number of rows:\n");
}

void print_get_column(){
    printf("Number of columns:\n");
}

void print_error_number_of_rows(){
    printf("Error: Number of rows must be smaller than 8\n");
    exit(1);
}

void print_error_number_of_cols(){
    printf("Error: Number of columns must be smaller than 8\n");
    exit(1);
}

void print_get_k(){
    printf("Please enter k:\n");
}

void print_error_k(int correct_k){
    printf("Error: k must be greater than zero, setting k to %d\n", correct_k);
}

void print_player_enter_col(char player_symbol){
    printf("Player %c, enter col:\n", player_symbol);
}

void print_invalid_input(char player){
    printf("Invalid input, try again\n");
    print_player_enter_col(player);
}

void print_column_full(){
    printf("Column is full, try again\n");
}

void print_board(char board[][MAX_COLS], int rows, int cols) {
    //print the board in the following format:
    printf("\n");
    for (int i = 0; i < rows; i++) {
        printf("|");
        for (int j = 0; j < cols; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
}

void print_draw_msg() {
    printf("DRAW!\n");
    exit(0);
}

void print_win_msg(char player_symbol, int turn_num) {
    printf("Player %c won in %d moves!\n", player_symbol, turn_num);
}
