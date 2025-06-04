#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"

#include <iostream>
#include <iomanip>
#include <cctype>

template <typename T>
class SUS_board :public Board<T> {

private:
    int score1 = 0, score2 = 0;
    T sympol1, sympol2;


    bool check_sus(int x, int y, T symbol) {
        if (symbol == 'S') {
            if (x == 1 && y == 1) return false;
            else {
                if (x == 0 && y == 0) {
                    if (this->board[x][y + 1] == 'U' && this->board[x][y + 2] == 'S') return true;
                    else if (this->board[x + 1][y + 1] == 'U' && this->board[x + 2][y + 2] == 'S') return true;
                    else if (this->board[x + 1][y] == 'U' && this->board[x + 2][y] == 'S') return true;
                }
                else if (x == 0 && y == 2) {
                    if (this->board[x][y - 1] == 'U' && this->board[x][y - 2] == 'S') return true;
                    else if (this->board[x + 1][y - 1] == 'U' && this->board[x + 2][y - 2] == 'S') return true;
                    else if (this->board[x + 1][y] == 'U' && this->board[x + 2][y] == 'S') return true;
                }
                else if (x == 2 && y == 0) {
                    if (this->board[x][y + 1] == 'U' && this->board[x][y + 2] == 'S') return true;
                    else if (this->board[x - 1][y + 1] == 'U' && this->board[x - 2][y + 2] == 'S') return true;
                    else if (this->board[x - 1][y] == 'U' && this->board[x - 2][y] == 'S') return true;
                }
                else if (x == 2 && y == 2) {
                    if (this->board[x][y - 1] == 'U' && this->board[x][y - 2] == 'S') return true;
                    else if (this->board[x - 1][y - 1] == 'U' && this->board[x - 2][y - 2] == 'S') return true;
                    else if (this->board[x - 1][y] == 'U' && this->board[x - 2][y] == 'S') return true;
                }
                else if (x == 1 && y == 0 && this->board[x][y + 1] == 'U' && this->board[x][y + 2] == 'S') return true;
                else if (x == 0 && y == 1 && this->board[x + 1][y] == 'U' && this->board[x + 2][y] == 'S') return true;
                else if (x == 2 && y == 1 && this->board[x - 1][y] == 'U' && this->board[x - 2][y] == 'S') return true;
                else if (x == 1 && y == 2 && this->board[x][y - 1] == 'U' && this->board[x][y - 2] == 'S') return true;
            }
        }
        else {
            if ((x == 0 && (y == 0 || y == 2)) || (x == 2 && (y == 0 || y == 2))) {
                return false;
            }
            else {
                if (x == 1 && y == 0 && this->board[x - 1][y] == 'S' && this->board[x + 1][y] == 'S') return true;
                else if (x == 0 && y == 1 && this->board[x][y - 1] == 'S' && this->board[x][y + 1] == 'S') return true;
                else if (x == 2 && y == 1 && this->board[x][y - 1] == 'S' && this->board[x][y + 1] == 'S') return true;
                else if (x == 1 && y == 2 && this->board[x - 1][y] == 'S' && this->board[x + 1][y] == 'S') return true;
                else if (x == 1 && y == 1) {
                    if (this->board[x - 1][y - 1] == 'S' && this->board[x + 1][y + 1] == 'S') return true;
                    else if (this->board[x + 1][y - 1] == 'S' && this->board[x - 1][y + 1] == 'S') return true;
                    else if (this->board[x - 1][y] == 'S' && this->board[x + 1][y] == 'S') return true;
                    else if (this->board[x][y - 1] == 'S' && this->board[x][y + 1] == 'S') return true;
                }
            }
        }
        return false;
    }

    bool no_more() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == ' ') {
                    if (check_sus(i, j, 'S')) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

public:
    SUS_board(T sympol1, T sympol2) {
        this->sympol1 = sympol1;
        this->sympol2 = sympol2;

        this->rows = this->columns = 3;
        this->board = new char* [this->rows];
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
                if (check_sus(x, y, sympol)) {
                    if (sympol == this->sympol1) {
                        score1++;
                    }
                    else {
                        score2++;
                    }
                }
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
        cout << "\n player 1 is : " << score1 <<
            "\n player 2 is : " << score2 << endl;
    }
     
    bool is_win() {
        if (score1 > score2 && this->n_moves == 9) return true;
        if (score1 + 1 < score2 && this->n_moves == 8) return true;
        if (score1 + 1 == score2 && this->n_moves == 8 && no_more()) return true;
        return false;
    }

    bool is_draw() {
        return this->score1 == this->score2 && this->score1 != 0 && this->n_moves == 9;
    }

    bool game_is_over() {
        return this->n_moves == 9;
    }


};

template <typename T>
class SUS_player : public Player<T> {
    
public:
    int seq = 0;
    SUS_player(string name, T sympol) : Player<T>(name, sympol) {}

  void getmove(int& x, int& y)  override {
        cout << "\nPlease enter your move x and y separated by spaces: ";
        cin >> x >> y;
    }

};


template <typename T>
class SUS_randomplayer : public RandomPlayer<T> {

public:
    explicit SUS_randomplayer(T sympol) : RandomPlayer<T>(sympol) {
        this->name = "Random Computer Player";
        this->dimension = 3;
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y)  override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

};

#endif // SUS_H

