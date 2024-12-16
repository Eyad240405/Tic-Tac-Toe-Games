#ifndef Game5_H
#define Game5_H

#include "BoardGame_Classes.h"

template <typename T>
class Numerical_Board:public Board<T> {
public:
    Numerical_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool ValidLocations(int Raw, int Col);
    bool ValidNumber(char num);
};

template <typename T>
class Numerical_Player : public Player<T> {
public:
    Numerical_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
    void getnum(int& num);
};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
public:
    Numerical_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    void getnum(int& num);
};

template <typename T>
class Numerical_GameManager : public GameManager<T>{
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    Numerical_GameManager(Board<T>* b, Player<T>* playerPtr[2]);

    void run();
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;
int turn = 0;
// Constructor for Numerical_Board
template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
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
bool Numerical_Board<T>::update_board(int x, int y, T mark) {
    int num;
    if(mark == 'R') {
        num = rand() % 10;
    }
    else {
        cout << "Enter your number from 1 to 9 that isn't on the board\n(ood for player 1, even for player2):";
        cin >> num;
    }
    for(int r = 0; r < this->rows; r++) {
        for(int c = 0; c < this->columns; c++){
            if(num == this->board[r][c] - 48){
                if(mark == 'R') {
                    num = rand() % 10;
                }
                else {
                    cout << "Enter your number from 1 to 9 that isn't on the board\n(ood for player 1, even for player2):";
                    cin >> num;
                }
            }
        }
    }
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns || num < 1 || num > 9) && (this->board[x][y] == 0)) {
        if (num % 2 == turn % 2){
            this->n_moves--;
            this->board[x][y] = 0;
            return false;
        }
        else {
            this->n_moves++;
            this->board[x][y] = num + 48;
            turn++;
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Numerical_Board<T>::display_board() {
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
bool Numerical_Board<T>::is_win() {
    // Horizontal
    for (int r = 0; r < this->rows; r++) {
        if((this->board[r][0] - 48) + (this->board[r][1] - 48) + (this->board[r][2] - 48) == 15) {
            return true;
        }
    }
    // Vertical
    for (int c = 0; c < this->columns; c++) {
        if((this->board[0][c] - 48) + (this->board[1][c] - 48) + (this->board[2][c] - 48) == 15){
            return true;
        }
    }
    // Positive diagonal
    if((this->board[0][0] - 48) + (this->board[1][1] - 48) + (this->board[2][2] - 48) == 15){
        return true;
    }
    // Negative diagonal
    if((this->board[0][2] - 48) + (this->board[1][1] - 48) + (this->board[2][0] - 48) == 15){
        return true;
    }
    return false;
}

template <typename T>
bool Numerical_Board<T>::is_draw() {
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
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


//--------------------------------------

// Constructor for Numerical_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    cout << this->name << ", it's your turn.";
    cout << "\nPlease enter your valid move x and y (0 to 2) separated by spaces:";
    cin >> x >> y;
}


// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player\n";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



#endif