#ifndef PYRAMIC_TIC_TAC_TOE_H
#define PYRAMIC_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <cctype>
#include <iomanip>
using namespace std;

template <typename T> 
class pyramic_tic_tac_toe_board : public Board<T> {

public:
    pyramic_tic_tac_toe_board() {
        this->rows = 3;
        this->columns = 5;

        this->board = new char* [this->rows];

        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                if ((i == 0 && (j == 0 || j == 1 || j == 3 || j == 4)) || (i == 1 && (j == 0 || j == 4))) {
                    this->board[i][j] = 0;
                }
                else {
                    this->board[i][j] = ' ';
                }
            }
        }
    }

    bool update_board(int x, int y, T sympol)  override {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == ' ' || sympol == 0)) {
            if (sympol == 0) {
                this->n_moves--;
                this->board[x][y] = ' ';
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(sympol);
            }

            return true;
        }
        return false;
    }

    void display_board()  override {
        for (int i = 0; i < this->rows; i++) {
            if (i == 0) cout << "\n\t \t";
            else if (i == 1) cout << "\t";
            cout << "|";
            for (int j = 2 - i; j < 5 - 2 + i; j++) {
                cout << "(" << i << "," << j << ")";
                cout << setw(2) << this->board[i][j] << "|";
            }
            cout << "\n------------------------------------------\n";
        }
    }

    bool is_win()  override {
        // verically
        if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != ' ') {
            return true;
        }

        // horizontally
        if ((this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != ' ') ||
            (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != ' ') ||
            (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != ' ') ||
            (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != ' ')) {
            return true;
        }

        // diagonally
        if ((this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != ' ') ||
            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
            return true;
        }

        return false;
    }

    bool is_draw()  override {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over()  override {
        return is_win() || is_draw();
    }

};


template <typename T> 
class pyramic_tic_tac_toe_player : public Player<T> {

public:
    pyramic_tic_tac_toe_player(string name, T sympol) : Player<T>(name, sympol) {}

    void getmove(int& x, int& y)  override {
        cout << "\nPlease enter your move x and y separated by spaces: ";
        cin >> x >> y;
    }

};


template <typename T> 
class pyramic_tic_tac_toe_randomplayer : public RandomPlayer<T> {

public:
    explicit pyramic_tic_tac_toe_randomplayer(T sympol) : RandomPlayer<T>(sympol) {
        this->name = "Random Computer Player";
        this->dimension = 0;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y)  override {
        x = rand() % 3;
        y = rand() % 5;

        if ((x == 0 && (y == 0 || y == 1 || y == 3 || y == 4)) || (x == 1 && (y == 0 || y == 4))) {
            getmove(x, y);
        }
    }

};


#endif