#ifndef _Ultimate_TicTacToe_H
#define _Ultimate_TicTacToe_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib> // for srand() and rand()
#include <ctime>   // for time()

using namespace std;

template <typename T>
class Ultimate_Board: public Board<T> {
public:
    Ultimate_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool smallWin(int& r, int& c, char& m);
};

template <typename T>
class Ultimate_Player : public Player<T> {
public:
    Ultimate_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T> {
public:
    Ultimate_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

//--------------------------------------- IMPLEMENTATION

// Constructor for Ultimate_Board
template <typename T>
Ultimate_Board<T>::Ultimate_Board() {
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}
template <typename T>
bool Ultimate_Board<T>::update_board(int x, int y, T mark) {
    // Ensure the move is within bounds and the cell is empty
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
        return false;
    }

    // Place the mark
    this->n_moves++;
    this->board[x][y] = mark;

    // Check if this move causes a smaller board to be won
    int r = (x / 3) * 3;  // Top-left row of the smaller board
    int c = (y / 3) * 3;  // Top-left column of the smaller board
    char winner = ' ';

    if (smallWin(r, c, winner)) {
        // If the smaller board is won, mark the smaller board as completed
        for (int i = r; i < r + 3; i++) {
            for (int j = c; j < c + 3; j++) {
                this->board[i][j] = '.';  // Mark as "completed"
            }
        }
        // Set the center of the smaller board to the winning mark
        this->board[r + 1][c + 1] = toupper(winner);
    }

    return true;
}

// Display the board and the pieces on it
template <typename T>
void Ultimate_Board<T>::display_board() {
    int r = 0;
    for (int i = 0; i < this->rows; i++) {
        if (i % 3 == 0 && i != 0) { cout << "\n -----------------------------------------"; }
        cout << "\n" << r << " |";
        r++;
        for (int j = 0; j < this->columns; j++) {
            if (j % 3 == 0 && j != 0) { cout << ":|"; }
            cout << setw(2) << this->board[i][j] << " |";
        }
    }
    cout << endl;
    cout << setw(5);
    for (int c = 0; c < this->rows; c++) {
        if (c == 3 || c == 6) {
            cout << setw(6);
        }
        cout << c << setw(4);
    }
    cout << endl;
}
template <typename T>
bool Ultimate_Board<T>::smallWin(int& k, int& j, char& m) {
    for (k = 0; k < this->rows; k += 3) {  // Check the top, middle, and bottom 3x3 blocks
        for (j = 0; j < this->columns; j += 3) {  // Check the left, center, and right 3x3 blocks
            // Check rows and columns in the 3x3 blocks
            for (int l = 0; l < 3; l++) {
                if ((this->board[k + l][j] == this->board[k + l][j + 1] && this->board[k + l][j + 1] == this->board[k + l][j + 2] &&
                this->board[k + l][j] != ' ' && this->board[k + l][j] != '.')) {
                    m = this->board[k + l][j];  // Set the marker of the winning player
                    return true;
                }
                if((this->board[k][j + l] == this->board[k + 1][j + l] && this->board[k + 1][j + l] == this->board[k + 2][j + l] &&
                this->board[k][j + l] != ' ' && this->board[k][j + l] != '.')){
                    m = this->board[k][j + l];
                    return true;
                }
            }
            // Check diagonals in the 3x3 blocks
            if ((this->board[k][j] == this->board[k + 1][j + 1] && this->board[k + 1][j + 1] == this->board[k + 2][j + 2] &&
            this->board[k][j] != ' ' && this->board[k][j] != '.')) {
                m = this->board[k][j];  // Set the marker of the winning player
                return true;
            }
            if((this->board[k][j + 2] == this->board[k + 1][j + 1] && this->board[k + 1][j + 1] == this->board[k + 2][j] &&
            this->board[k][j + 2] != ' ' && this->board[k][j + 2] != '.')){
                m = this->board[k][j + 2];
                return true;
            }
        }
    }
    return false;
}

// Returns true if there is any winner
template <typename T>
bool Ultimate_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 1; i < this->rows; i += 3) {
        if ((this->board[i][1] == this->board[i][4] && this->board[i][7] == this->board[i][1] && this->board[i][1] != ' ') ||
            (this->board[1][i] == this->board[4][i] && this->board[7][i] == this->board[1][i] && this->board[1][i] != ' ')) {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[4][4] == this->board[1][1] && this->board[7][7] == this->board[1][1] && this->board[1][1] != ' ') ||
        (this->board[4][4] == this->board[1][7] && this->board[7][1] == this->board[1][7] && this->board[1][7] != ' ')) {
        return true;
    }
    return false;
}

// Return true if 81 moves are done and no winner
template <typename T>
bool Ultimate_Board<T>::is_draw() {
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool Ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Ultimate_Player
template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces:";
    cin >> x >> y;
}

// Constructor for Ultimate_Random_Player
template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 8
    y = rand() % this->dimension;
}

#endif //_Ultimate_TicTacToe_H
