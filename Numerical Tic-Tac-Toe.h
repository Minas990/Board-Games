#ifndef __Numberical
#define __Numberical

#include "BoardGame_Classes.h"
#include <set>
template <typename T>
class Numeracle_Tic_Tac_Two_Board : public Board<T>
{
public:
    Numeracle_Tic_Tac_Two_Board ();
    bool update_board (int x ,int y ,T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
private:
    bool player_turn = true;
    set<int>player1;
    set<int>player2;
};

template <typename T>
class Numeracle_Tic_Tac_TwoPlayer : public Player<T> 
{
public:
    Numeracle_Tic_Tac_TwoPlayer (string name, T symbol);
    void getmove(int& x,int& y) ;
    set<int> st;
};

template <typename T>
class Numeracle_Tic_Tac_TwoRandom_Player : public RandomPlayer<T>
{
public:
    Numeracle_Tic_Tac_TwoRandom_Player (T symbol);
    void getmove(int &x,int& y) ;
    set<int> st;

};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Numeracle_Tic_Tac_Two_Board<T>::Numeracle_Tic_Tac_Two_Board() 
{
    this->rows = 3;
    this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) 
    {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) 
        {
            this->board[i][j] = 0;
        }
    }
    for(int i =1 ;i<=9;i+=2)
    {
        player1.insert(i);
        player2.insert(i+1);
    }
    player2.erase(10);
    this->n_moves = 0;
}


template <typename T>
bool Numeracle_Tic_Tac_Two_Board<T>::update_board(int x,int y ,T mark) 
{
    bool ok =false;
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) 
    {
        if(player_turn)
        {
            if(player1.count(mark))
            {
                player_turn = !player_turn;
                this->board[x][y] = mark;
                player1.erase(mark);
                ok = true;
            this->n_moves++;
            }
        }
        else 
        {
            if(player2.count(mark))
            {
                player_turn = !player_turn;
                this->board[x][y] = mark;
                player2.erase(mark);
                ok = true;
                this->n_moves++;
            }
        }
    }
    return ok;
}

template <typename T>
void Numeracle_Tic_Tac_Two_Board<T>::display_board() 
{
    for (int i = 0; i < this->rows; i++) 
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) 
        {
            // cout << "(" << i << "," << j << ")";
            if(this->board[i][j]==0)
                cout <<"   |";
            else 
                cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n---------------";
    }
    cout << endl;
}

template <typename T>
bool Numeracle_Tic_Tac_Two_Board<T>::is_win() 
{
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) 
    {
        if ((this->board[i][0]  + this->board[i][1] + this->board[i][2]==15 && this->board[i][0] && this->board[i][1] && this->board[i][2] ) ||
            (this->board[0][i]  + this->board[1][i] + this->board[2][i] == 15)&& this->board[0][i] && this->board[1][i] && this->board[2][i]  ) 
        {
            return true;
        }
    }
    // Check diagonals
    if ((this->board[0][0] +  this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] && this->board[1][1] && this->board[2][2] ) ||
        (this->board[0][2] +  this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] && this->board[1][1] && this->board[2][0] )) 
    {
        return true;
    }
    return false;
}

template <typename T>
bool Numeracle_Tic_Tac_Two_Board<T>::is_draw() 
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numeracle_Tic_Tac_Two_Board<T>::game_is_over() 
{
    return is_win() || is_draw();
}

// player 
template <typename T>
Numeracle_Tic_Tac_TwoPlayer<T>::Numeracle_Tic_Tac_TwoPlayer(string name, T symbol) :
Player<T>(name, symbol) 
{
    if(this->symbol%2==0)
    {
        this->st.insert(1);
        this->st.insert(3);
        this->st.insert(5);
        this->st.insert(7);
        this->st.insert(9);
    }
    else 
    {
        this->st.insert(2);
        this->st.insert(4);
        this->st.insert(6);
        this->st.insert(8);
    }
}

template <typename T>
void Numeracle_Tic_Tac_TwoPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    for(auto& it:this->st)  cout << it <<' ';
    cout << "\nchoose from this number : ";
    cin >> this->symbol ;
}

template <typename T>
Numeracle_Tic_Tac_TwoRandom_Player<T>::Numeracle_Tic_Tac_TwoRandom_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    if(this->symbol%2==0)
    {
        this->st.insert(1);
        this->st.insert(3);
        this->st.insert(5);
        this->st.insert(7);
        this->st.insert(9);
    }
    else 
    {
        this->st.insert(2);
        this->st.insert(4);
        this->st.insert(6);
        this->st.insert(8);
    }
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Numeracle_Tic_Tac_TwoRandom_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    vector<int> v(st.begin(),st.end());
    this->symbol = v[rand()%v.size()];
}

#endif