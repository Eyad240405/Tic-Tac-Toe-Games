#ifndef Game7_H
#define Game7_H

#include "BoardGame_Classes.h"

template <typename T>
class Tic_Tac_Toe4x4_Board:public Board<T> {
public:
    Tic_Tac_Toe4x4_Board ();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool ValidLocations(int Raw, int Col, int location , int& newRaw, int& newCol);
    bool ValidSymbol(int x , int y , T symbol);
};

template <typename T>
class Tic_Tac_Toe4x4_Player : public Player<T> {
public:
    Tic_Tac_Toe4x4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class Tic_Tac_Toe4x4_Random_Player : public RandomPlayer<T>{
public:
    Tic_Tac_Toe4x4_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Tic_Tac_Toe4x4_Board
template <typename T>
Tic_Tac_Toe4x4_Board<T>::Tic_Tac_Toe4x4_Board() {
    this->rows = 4;
    this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    for (int i = 0; i < this->columns; i++){
        if(i % 2 == 0){
            this->board[0][i] = 'O';
            this->board[3][i] = 'X';
        }else{
            this->board[0][i] = 'X';
            this->board[3][i] = 'O';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::update_board(int x, int y, T mark) {
    while(!this->ValidSymbol(x,y, toupper(mark))){
        return false;
    }
    int choice , newRaw , newCol;
    if(mark == 'o') {
        choice = rand() % 5;
    }
    else {
        cout << "Enter valid direction...\n"
                  "1) Up\n"
                  "2) Down\n"
                  "3) Left\n"
                  "4) Right\n"
                  "choose:";
        cin >> choice;
    }
    while(!this->ValidLocations(x,y,choice,newRaw,newCol)) {
        if(mark == 'o'){
            choice = rand() % 5;
        }
        else{
            cout << "Enter valid direction...\n"
                    "1) Up\n"
                    "2) Down\n"
                    "3) Left\n"
                    "4) Right\n"
                    "choose:";
            cin >> choice;
        }
    }

    this->board[x][y] = 0;
    this->board[newRaw][newCol] = toupper(mark);
    cout << this->board[x][y] << endl;
    return true;
}

// Display the board and the pieces on it
template <typename T>
void Tic_Tac_Toe4x4_Board<T>::display_board() {
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

template<typename T>
bool Tic_Tac_Toe4x4_Board<T>::ValidLocations(int Raw, int Col, int location ,int& newRaw, int& newCol) {
    if(location == 1){
        if(Raw > 0 && this->board[Raw - 1][Col] == 0){
            newRaw = Raw - 1;
            newCol = Col;
            return true;
        }
    }
    if(location == 2){
        if(Raw < this->rows - 1 && this->board[Raw + 1][Col] == 0) {
            newRaw = Raw + 1;
            newCol = Col;
            return true;
        }
    }
    if(location == 3){
        if(Col > 0 && this->board[Raw][Col - 1] == 0) {
            newRaw = Raw;
            newCol = Col - 1;
            return true;
        }
    }
    if(location == 4){
        if(Col < this->columns - 1 && this->board[Raw][Col + 1] == 0){
            newRaw = Raw;
            newCol = Col + 1;
            return true;
        }
    }
    newRaw = Raw;
    newCol = Col;
    return false;
}

template<typename T>
bool Tic_Tac_Toe4x4_Board<T>::ValidSymbol(int x, int y, T symbol) {
    if(this->board[x][y] == symbol){
        return true;
    }
    return false;
}


// Returns true if there is any winner
template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::is_win() {
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

template <typename T>
bool Tic_Tac_Toe4x4_Board<T>::is_draw() {
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
bool Tic_Tac_Toe4x4_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for Tic_Tac_Toe4x4_Player
template <typename T>
Tic_Tac_Toe4x4_Player<T>::Tic_Tac_Toe4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Tic_Tac_Toe4x4_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn (" << this->symbol << ").";
    cout << "\nenter the location of your character (x , y) from 0 to 3 to move:";
    cin >> x >>y;


}


// Constructor for Tic_Tac_Toe4x4_Random_Player
template <typename T>
Tic_Tac_Toe4x4_Random_Player<T>::Tic_Tac_Toe4x4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Tic_Tac_Toe4x4_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 3
    y = rand() % this->dimension;

}


#endif