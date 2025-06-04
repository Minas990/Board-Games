#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>
#include <iomanip>
#include <fstream>
using namespace std;

template <typename T>
class Word_tic_tac_toe_board : public Board<T> {
 
    bool is_valid_word(char one, char two, char three) {
        string word = string(1, one) + string(1, two) + string(1, three);
        ifstream file("dic.txt");
        if (!file) {
            cerr << "error opening file\n";
            return false;
        }

        string line;
        while (getline(file, line)) {
            if (line == word) {
                return true;
            }
        }
        file.close();
        return false;
    }

public:
    Word_tic_tac_toe_board() {
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = ' ';
            }
        }
        this->n_moves = 0;
    }

    bool update_board(int x, int y, T sympol) {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || sympol == 0)) {
            if (sympol == 0) {
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(sympol);
            }

            return true;
        }
        return false;
    }

    void display_board() {
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << " |";
            }
            cout << "\n-----------------------------";
        }
        cout << endl;
    }

    bool is_win() {
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] != ' ' && this->board[i][1] != ' ' && this->board[i][2] != ' ') {

                char one = static_cast<char>(this->board[i][0]);
                char two = static_cast<char>(this->board[i][1]);
                char three = static_cast<char>(this->board[i][2]);


                if (is_valid_word(one, two, three)) return true;
            }
            if (this->board[0][i] != ' ' && this->board[1][i] != ' ' && this->board[2][i] != ' ') {

                char one = static_cast<char>(this->board[0][i]);
                char two = static_cast<char>(this->board[1][i]);
                char three = static_cast<char>(this->board[2][i]);


                if (is_valid_word(one, two, three)) return true;
            }
        }

        // Check diagonals
        if (this->board[0][0] != ' ' && this->board[1][1] != ' ' && this->board[2][2] != ' ') {

            char one = static_cast<char>(this->board[0][0]);
            char two = static_cast<char>(this->board[1][1]);
            char three = static_cast<char>(this->board[2][2]);


            if (is_valid_word(one, two, three)) return true;
        }

        if (this->board[0][2] != ' ' && this->board[1][1] != ' ' && this->board[2][0] != ' ') {

            char one = static_cast<char>(this->board[0][2]);
            char two = static_cast<char>(this->board[1][1]);
            char three = static_cast<char>(this->board[2][0]);

            if (is_valid_word(one, two, three)) return true;
        }

        return false;
    }

    bool is_draw() {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() {
        return is_win() || is_draw();
    }
};

template <typename T>
class Word_tic_tac_toe_player : public Player<T> {

public:
    Word_tic_tac_toe_player(string name, T sympol) : Player<T>(name, sympol) {}

    void getmove(int& x, int& y)  override {
        cout << "\nPlease enter your move x, y, character separated by spaces: ";
        cin >> x >> y;

        cin >> this->symbol;
    }

};


template <typename T>
class Word_tic_tac_toe_randomplayer : public RandomPlayer<T> {

public:
    explicit Word_tic_tac_toe_randomplayer(T sympol) : RandomPlayer<T>(sympol) {
        this->name = "Random Computer Player";
        this->dimension = 3;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y)  override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int randInd = rand() % alpha.size();
        this->symbol = alpha[randInd];
    }

};


#endif
