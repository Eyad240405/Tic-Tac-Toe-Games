#ifndef _FIVE_BY_FIVE_TIC_TAC_TOE_H_
#define _FIVE_BY_FIVE_TIC_TAC_TOE_H_

#include "BoardGame_Classes.h"

Player<char>* globalplayers[2];

template <typename T>
class five_by_five_Board : public Board<T> {
public:

    five_by_five_Board ();
    int counter;
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class five_by_five_Player : public Player<T> {
    public:
    five_by_five_Player (string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class five_by_five_Random_Player : public RandomPlayer<T>{
public:
    five_by_five_Random_Player(T symbol);
    void getmove(int &x, int &y);
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
five_by_five_Board<T>::five_by_five_Board() {
    counter = 0;
    this->rows = this->columns = 5;
    this->board = new char*[this -> rows];
    for (int i = 0; i < this -> rows; i++) {
        this->board[i] = new char[this -> columns];
        for (int j = 0; j < this -> columns; j++) {
            this->board[i][j] = 0;
            //delete [0][4] square
            if (i == 0 && j == 4) {
                this->board[i][j] = '.';
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool five_by_five_Board<T>::update_board(int x, int y, T mark) {

    //Only update if move is valid
if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            counter --;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            counter ++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template<typename T>
void five_by_five_Board<T>::display_board() {
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
template<typename T>

bool five_by_five_Board<T>::is_win() {
    if (this->n_moves == 24) {
        int countX = 0;
        int countO = 0;
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] == 'X' && this->board[i][j + 1] == 'X' && this->board[i][j + 2] == 'X') {
                    countX++;
                }
                if (this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O') {
                    countO++;
                }
            }
        }

        // Check columns
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == 'X' && this->board[i + 1][j] == 'X' && this->board[i + 2][j] == 'X') {
                    countX++;
                }
                if (this->board[i][j] == 'O' && this->board[i + 1][j] == 'O' && this->board[i + 2][j] == 'O') {
                    countO++;
                }
            }
        }

        // Check diagonals (left-to-right)
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] == 'X' && this->board[i + 1][j + 1] == 'X' && this->board[i + 2][j + 2] == 'X') {
                    countX++;
                }
                if (this->board[i][j] == 'O' && this->board[i + 1][j + 1] == 'O' && this->board[i + 2][j + 2] == 'O') {
                    countO++;
                }
            }
        }

        // Check diagonals (right-to-left)
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 2; j < this->columns; j++) {
                if (this->board[i][j] == 'X' && this->board[i + 1][j - 1] == 'X' && this->board[i + 2][j - 2] == 'X') {
                    countX++;
                }
                if (this->board[i][j] == 'O' && this->board[i + 1][j - 1] == 'O' && this->board[i + 2][j - 2] == 'O') {
                    countO++;
                }
            }
        }
        // Determine and print the winner
        if (countX > countO) {
            *globalplayers[1] = *globalplayers[0];
            return true;
        }

        if (countO > countX ) {
                return true;
        }

        if (countX == countO) {
            return true;
        }
    }
    return false;  // Always return false to continue the game
}

// Modify is_draw to print the winner
template<typename T>
bool five_by_five_Board<T>::is_draw() {
    if (this->n_moves == 24 && !is_win()) {
            cout << "It's a draw!";
            return true;


    }
    return false;
}

template<typename T>
bool five_by_five_Board<T>::game_is_over() {
    if (is_win()) {
        return true;
    }
    return is_draw();
}

//--------------------------------------

// Constructor for five_by_five_Player
template<typename T>
five_by_five_Player<T>::five_by_five_Player(string name, T symbol) : Player<T>(name, symbol) {}

template<typename T>
void five_by_five_Player<T>::getmove(int &x, int &y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    do {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;

        if (x == 0 && y == 4) {
            cout << "Invalid move! Square (0, 4) is not allowed. Please choose a different square.\n";
        } else {
            break;
        }
    } while (true);
}


// Constructor for five_by_five_Random_Player
template<typename T>
five_by_five_Random_Player<T>::five_by_five_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void five_by_five_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}

#endif


