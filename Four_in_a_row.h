#ifndef Game2_H
#define Game2_H

#include "BoardGame_Classes.h"

template <typename T>
class Four_in_a_row_Board:public Board<T> {
public:
    Four_in_a_row_Board ();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Four_in_a_row_Player : public Player<T> {
public:
    Four_in_a_row_Player (string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Four_in_a_row_Random_Player : public RandomPlayer<T>{
public:
    Four_in_a_row_Random_Player (T symbol);
    void getmove(int &x, int& y) ;
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <limits>
#include <algorithm>

using namespace std;

// Constructor for Four_in_a_row_Board
template <typename T>
Four_in_a_row_Board<T>::Four_in_a_row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Four_in_a_row_Board<T>::update_board(int x, int y, T mark) {
    for(int r = this->rows - 1; r >= 0; r--){
        if(this->board[r][y] == 0){
            x = r;
            break;
        }
    }
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Four_in_a_row_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool Four_in_a_row_Board<T>::is_win() {
    // Horizontal
    for (int r = 0; r < this->rows; r++) {
        for(int c = 0; c < this->columns - 3; c++){
            if(this->board[r][c + 1] == this->board[r][c] && this->board[r][c + 2] == this->board[r][c] && this->board[r][c + 3] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Vertical
    for (int r = 0; r < this->rows - 3; r++) {
        for(int c = 0; c < this->columns; c++){
            if(this->board[r + 1][c] == this->board[r][c] && this->board[r + 2][c] == this->board[r][c] && this->board[r + 3][c] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Positive diagonal
    for (int r = 0; r < this->rows - 3; r++) {
        for(int c = 0; c < this->columns - 3; c++){
            if(this->board[r + 1][c + 1] == this->board[r][c] && this->board[r + 2][c + 2] == this->board[r][c] && this->board[r + 3][c + 3] == this->board[r][c] && this->board[r][c] != 0){
                return true;
            }
        }
    }
    // Negative diagonal
    for (int r = 3; r < this->rows; ++r) {
        for (int c = 0; c < this->columns - 3; ++c) {
            if (this->board[r - 1][c + 1] == this->board[r][c] && this->board[r - 2][c + 2] == this->board[r][c] && this->board[r - 3][c + 3] == this->board[r][c] && this->board[r][c] != 0) {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Four_in_a_row_Board<T>::is_draw() {
    for(int r = 0; r < this->rows; r++){
        for(int c = 0; c < this->columns; c++){
            if(this->board[r][c] == 0){
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Four_in_a_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for Four_in_a_row_Player
template <typename T>
Four_in_a_row_Player<T>::Four_in_a_row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_in_a_row_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    cout << "\nPlease enter your move (0 to 6):";
    cin >> y;

}


// Constructor for Four_in_a_row_Random_Player
template <typename T>
Four_in_a_row_Random_Player<T>::Four_in_a_row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Four_in_a_row_Random_Player<T>::getmove(int& x, int& y) {
    y = rand() % this->dimension;  // Random number between 0 and 6
}


#endif