#ifndef _FOUR_IN
#define _FOUR_IN

#include "BoardGame_Classes.h"

template <typename T>
class Four_In_Board : public Board<T>
{
public:
    Four_In_Board ();
    bool update_board (int x ,int y ,T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
private:
    vector<int>heights;
    bool four_contig(string str)
    {
        if (str.length() < 4) {
            return false;
        }
        for (size_t i = 0; i <= str.length() - 4; ++i) 
        {
            if(str[i]=='0')
                continue;
            if (str[i] == str[i + 1] && str[i + 1] == str[i + 2] && str[i + 2] == str[i + 3]) 
            {
                return true;  
            }
        }
        return false; 
    }
};

template <typename T>
class Four_In_Player : public Player<T> 
{
public:
    Four_In_Player (string name, T symbol);
    void getmove(int& x,int& y) ;

};


template <typename T>
class Four_In_Random_Player : public RandomPlayer<T>
{
public:
    Four_In_Random_Player (T symbol);
    void getmove(int &x,int& y) ;
};



//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Four_In_Board<T>::Four_In_Board() 
{
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) 
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) 
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    heights.resize(this->columns);
}


template <typename T>
bool Four_In_Board<T>::update_board(int x,int y ,T mark) 
{
    // Only update if move is valid
    y = heights[x];
    if (!(x < 0 || x >= this->columns) && (heights[x]<=5|| mark == 0)) {
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else 
        {
            this->n_moves++;
            this->board[5-y][x] = toupper(mark);
        }
        heights[x]++;
        return true;
    }
    return false;
}

template <typename T>
void Four_In_Board<T>::display_board() 
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
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
bool Four_In_Board<T>::is_win() 
{
    //for rows
    for(int i = 0;i<this->rows;i++)
    {
        string thesRws;
        for(int j = 0;j<this->columns;j++)
        {
            if(this->board[i][j]==0)
                thesRws+='0';
            else 
                thesRws+=this->board[i][j];
        }
        if(four_contig(thesRws))
            return true;
    }
    //for columns
    for(int i = 0;i<this->columns;i++)
    {
        string theColus;
        for(int j = 0;j<this->rows;j++)
        {
            if(this->board[j][i]==0)
                theColus+='0';
            else 
                theColus+=this->board[j][i];
        }
        if(four_contig(theColus))
            return true;
    }
    //for diag
    vector<pair<int,int>> xandy = {{3,0},{4,0},{5,0},{5,1},{5,2},{5,3}};
    for(auto& it : xandy)
    {
        string diag;
        int i = it.first;
        int j = it.second;
        while(i>=0 && i<this->rows && j>=0 && j<this->columns)
        {
            if(this->board[i][j]==0)
                diag+='0';
            else 
                diag+=this->board[i][j];
            i--;
            j++;
        }
        if(four_contig(diag))  
            return true;
    }
    vector<pair<int,int>> xandy_inverse = {{0,3},{0,2},{0,1},{0,0},{1,0},{2,0}};
    for(auto& it : xandy_inverse)
    {
        string diag;
        int i = it.first;
        int j = it.second;
        while(i>=0 && i<this->rows && j>=0 && j<this->columns)
        {
            if(this->board[i][j]==0)
                diag+='0';
            else 
                diag+=this->board[i][j];
            i++;
            j++;
        }
        if(four_contig(diag))  
            return true;
    }
    return false;
}

template <typename T>
bool Four_In_Board<T>::is_draw() 
{
    return (this->n_moves == 6*7 && !is_win());
}

template <typename T>
bool Four_In_Board<T>::game_is_over() 
{
    return is_win() || is_draw();
}

// player
template <typename T>
Four_In_Player<T>::Four_In_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_In_Player<T>::getmove(int& x,int& y) 
{
    cout << "\nPlease enter your move x  (0 to 6) separated by spaces: ";
    cin >> x;
}
//random player
template <typename T>
Four_In_Random_Player<T>::Four_In_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void Four_In_Random_Player<T>::getmove(int& x,int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 6
}



#endif