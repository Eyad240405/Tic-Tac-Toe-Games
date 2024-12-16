#ifndef _PYRAMID_TIC_TAC_TOE_H
#define _PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

template <typename T>
class Pyramid_TicTacToe_Board : public Board<T> {
public:
    Pyramid_TicTacToe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Pyramid_TicTacToe_Player : public Player<T> {
public:
    Pyramid_TicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Pyramid_TicTacToe_Random_Player : public RandomPlayer<T> {
public:
    Pyramid_TicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for Pyramid_TicTacToe_Board
template <typename T>
Pyramid_TicTacToe_Board<T>::Pyramid_TicTacToe_Board() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];

    // Initialize the pyramid-shaped board
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if((i == 0 && j == 0) || (i ==0 && j == 1) || (i == 0 && j == 3) || (i == 0 && j == 4) || (i == 1 && j == 0) || (i == 1 && j == 4)){
                this->board[i][j] = '.';
            }
            else{
                this->board[i][j] = 0;
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramid_TicTacToe_Board<T>::update_board(int x, int y, T mark) {
    // Check if the coordinates are valid within the pyramid shape
    if ((x == 0 && y == 2) || (x == 1 && (y > 0 && y < 4)) || (x == 2)) {
        // Only update if move is valid and cell is empty
        if (this->board[x][y] == 0) {
            this->board[x][y] = toupper(mark);
            this->n_moves++;
            return true;
        }
    }
    return false;
}

// Display the pyramid-shaped board
template <typename T>
void Pyramid_TicTacToe_Board<T>::display_board() {
    int r = 0;
    for (int i = 0; i < this->rows; i++) {
        cout << "\n" << r << " |";
        r++;
        for (int j = 0; j < this->columns; j++) {  // Adjust the column limit per row
            cout << setw(2) << this->board[i][j] << " |";
        }
    }
    cout << endl;
    cout << setw(5);
    for(int c = 0; c < this->columns; c++) {
        cout << c << setw(4);
    }
    cout << endl;
    cout << string(15, '-') << endl;
}

// Check for a win condition (3 in a row)
template <typename T>
bool Pyramid_TicTacToe_Board<T>::is_win() {
    // Horizontal
    for (int r = 0; r < this->rows; r++) {
        for(int c = 0; c < this->columns - 3; c++){
            if(this->board[r][c + 1] == this->board[r][c] && this->board[r][c + 2] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Vertical
    for (int r = 0; r < this->rows - 2; r++) {
        for(int c = 0; c < this->columns; c++){
            if(this->board[r + 1][c] == this->board[r][c] && this->board[r + 2][c] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Positive diagonal
    for (int r = 0; r < this->rows - 2; r++) {
        for(int c = 0; c < this->columns - 2; c++){
            if(this->board[r + 1][c + 1] == this->board[r][c] && this->board[r + 2][c + 2] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Negative diagonal
    for (int r = 2; r < this->rows; ++r) {
        for (int c = 0; c < this->columns - 2; ++c) {
            if (this->board[r - 1][c + 1] == this->board[r][c] && this->board[r - 2][c + 2] == this->board[r][c] && this->board[r][c] != 0) {
                return true;
            }
        }
    }
    return false;
    }
// Check if the game is a draw (no more moves and no winner)
template <typename T>
bool Pyramid_TicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over (win or draw)
template <typename T>
bool Pyramid_TicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Pyramid_TicTacToe_Player
template <typename T>
Pyramid_TicTacToe_Player<T>::Pyramid_TicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_TicTacToe_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    cout << "\nPlease enter your move (row and column for the pyramid, starting from row 0, column 2):";
    cin >> x >> y;
}

// Constructor for Pyramid_TicTacToe_Random_Player
template <typename T>
Pyramid_TicTacToe_Random_Player<T>::Pyramid_TicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Pyramid_TicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;  // Random row selection (0, 1, or 2)
    y = rand() % (5 - x);  // Column selection based on row
}

#endif //_PYRAMID_TIC_TAC_TOE_H