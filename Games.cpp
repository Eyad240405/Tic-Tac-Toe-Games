#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramid_Tic_Tac_Toe.h"
#include "Four_in_a_row.h"
#include "five_by_five_tic_tac_toe.h"
#include "Word_TicTacToe.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "misere_tic_tac_toe.h"
#include "Tic_Tac_Toe4x4.h"
#include "Ultimate_TicTacToe.h"

using namespace std;

int main() {
    cout << "Welcome to FCAI. :)\n";
    int choice1, choice2;
    Player<char>* players[2];
    string playerXName, player2Name;

    int Game;
    cout << "Choose your game...\n"
            "1) Pyramid Tic Tac Toe\n"
            "2) Four in a row Tic Tac Toe\n"
            "3) 5X5 Tic Tac Toc\n"
            "4) Word Tic Tac Toe\n"
            "5) Numerical Tic Tac Toe\n"
            "6) Misere Tic Tac Toe\n"
            "7) 4X4 Tic Tac Toe\n"
            "8) Ultimate Tic Tac Toe\n"
            "choose:";
    cin >> Game;

    // Set up player 1
    cout << "Enter Player 1 name:";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n"
            "3. AI player\n";
    cin >> choice1;

    // Set up player 2
    cout << "Enter Player 2 name:";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n"
            "3. AI player\n";
    cin >> choice2;

    // Game 1
    if(Game == 1){
        Board<char>* B = new Pyramid_TicTacToe_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Pyramid_TicTacToe_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Pyramid_TicTacToe_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Pyramid_TicTacToe_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Pyramid_TicTacToe_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Pyramid_TicTacToe_game(B, players);
        Pyramid_TicTacToe_game.run();
        delete B;
    }
    // Game 2
    else if(Game == 2){
        Board<char>* B = new Four_in_a_row_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Four_in_a_row_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Four_in_a_row_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Four_in_a_row_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Four_in_a_row_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Four_in_a_row_game(B, players);
        Four_in_a_row_game.run();
        delete B;
    }
    // Game 3
    else if(Game == 3){
        Board<char>* B = new five_by_five_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new five_by_five_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new five_by_five_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new five_by_five_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new five_by_five_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> five_by_five_game(B, players);
        five_by_five_game.run();
        delete B;
    }
    // Game 4
    else if(Game == 4){
        Board<char>* B = new Word_TicTacToe_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Word_TicTacToe_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Word_TicTacToe_Random_Player<char>('X');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Word_TicTacToe_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Word_TicTacToe_Random_Player<char>('O');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> five_by_five_game(B, players);
        five_by_five_game.run();
        delete B;
    }
    // Game 5
    else if(Game == 5){
        Board<char>* B = new Numerical_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Numerical_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Numerical_Random_Player<char>('R');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Numerical_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Numerical_Random_Player<char>('R');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Numerical_game(B, players);
        Numerical_game.run();
        delete B;
    }
    // Game 6
    else if(Game == 6){
        Board<char>* B = new Misere_tic_tac_toe_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Misere_tic_tac_toe_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Misere_tic_tac_toe_Random_Player<char>('R');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Misere_tic_tac_toe_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Misere_tic_tac_toe_Random_Player<char>('R');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Misere_tic_tac_toe_game(B, players);
        globalplayers1[0] = players[0];
        globalplayers1[1] = players[1];
        Misere_tic_tac_toe_game.run();
        delete B;
    }
    // Game 7
    else if(Game == 7){
        Board<char>* B = new Tic_Tac_Toe4x4_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Tic_Tac_Toe4x4_Player<char>(playerXName,'X');
                break;
            case 2:
                players[0] = new Tic_Tac_Toe4x4_Random_Player<char>('x');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Tic_Tac_Toe4x4_Player<char>(player2Name,'O');
                break;
            case 2:
                players[1] = new Tic_Tac_Toe4x4_Random_Player<char>('o');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Tic_Tac_Toe4x4_game(B, players);
        Tic_Tac_Toe4x4_game.run();
        delete B;
    }
    // Game 8
    else if(Game == 8){

        Board<char>* B = new Ultimate_Board<char>();

        switch(choice1) {
            case 1:
                players[0] = new Ultimate_Player<char>(playerXName,'x');
                break;
            case 2:
                players[0] = new Ultimate_Random_Player<char>('x');
                break;
            default:
                cout << "Invalid choice for Player 1. Exiting the game.\n";
                return 1;
        }
        switch(choice2) {
            case 1:
                players[1] = new Ultimate_Player<char>(player2Name,'o');
                break;
            case 2:
                players[1] = new Ultimate_Random_Player<char>('o');
                break;
            default:
                cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
        }

        // Create the game manager and run the game
        GameManager<char> Ultimate_game(B, players);
        Ultimate_game.run();
        delete B;
    }
    else{
        cout << "Invalid!";
    }

    // Clean up
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}

