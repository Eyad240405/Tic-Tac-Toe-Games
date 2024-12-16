#ifndef _Word_TicTacToe_BOARD_H
#define _Word_TicTacToe_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

template <typename T>
class Word_TicTacToe_Board : public Board<T> {
public:
    Word_TicTacToe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    vector<string> dictionary;
    void load_dictionary(const string& filename);
    bool check_word(const string& word);
    string get_row(int row);
    string get_column(int col);
    string get_diagonal(int type);
};

template <typename T>
class Word_TicTacToe_Player : public Player<T> {
public:
    Word_TicTacToe_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class Word_TicTacToe_Random_Player : public RandomPlayer<T> {
public:
    Word_TicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
Word_TicTacToe_Board<T>::Word_TicTacToe_Board() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
    load_dictionary("dic.txt");
}

template <typename T>
bool Word_TicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void Word_TicTacToe_Board<T>::display_board() {
    cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            int position = i * this->columns + j + 1;
            if (this->board[i][j] == ' ') {
                cout << "| " << position << " ";
            } else {
                cout << "| " << this->board[i][j] << " ";
            }
        }
        cout << "|\n";
        if (i < this->rows - 1) {
            cout << "-----------------\n";
        }
    }
    cout << endl;
}

template <typename T>
bool Word_TicTacToe_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if (check_word(get_row(i))) return true;
    }
    for (int j = 0; j < this->columns; j++) {
        if (check_word(get_column(j))) return true;
    }
    if (check_word(get_diagonal(0)) || check_word(get_diagonal(1))) return true;
    return false;
}

template <typename T>
bool Word_TicTacToe_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

template <typename T>
bool Word_TicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
void Word_TicTacToe_Board<T>::load_dictionary(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Couldn't open " << filename << ". select right folder." << endl;
        exit(1);
    }
    string word;
    while (file >> word) {
        if (word.length() == 3) {
            dictionary.push_back(word);
        }
    }
    file.close();
}

template <typename T>
bool Word_TicTacToe_Board<T>::check_word(const string& word) {
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

template <typename T>
string Word_TicTacToe_Board<T>::get_row(int row) {
    string result;
    for (int j = 0; j < this->columns; j++) {
        result += this->board[row][j];
    }
    return result;
}

template <typename T>
string Word_TicTacToe_Board<T>::get_column(int col) {
    string result;
    for (int i = 0; i < this->rows; i++) {
        result += this->board[i][col];
    }
    return result;
}

template <typename T>
string Word_TicTacToe_Board<T>::get_diagonal(int type) {
    string result;
    if (type == 0) {
        for (int i = 0; i < this->rows; i++) {
            result += this->board[i][i];
        }
    } else if (type == 1) {
        for (int i = 0; i < this->rows; i++) {
            result += this->board[i][this->columns - 1 - i];
        }
    }
    return result;
}

template <typename T>
Word_TicTacToe_Player<T>::Word_TicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Word_TicTacToe_Player<T>::getmove(int& x, int& y) {
    int position;
    cout << this->getname() << " enter from 1 to 9:";
    cin >> position;

    x = (position - 1) / 3;
    y = (position - 1) % 3;

    cout << "Enter the letter you want to place:";
    cin >> this->symbol;
}

template <typename T>
Word_TicTacToe_Random_Player<T>::Word_TicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    srand(time(0));
}

template <typename T>
void Word_TicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;

    this->symbol = (rand() % 26) + 65;
}

#endif //_X_O_BOARD_H