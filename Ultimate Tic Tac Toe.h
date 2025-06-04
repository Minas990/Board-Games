#ifndef _MINa
#define _MINa

#include "BoardGame_Classes.h"
#include <iomanip>

template <typename T>
class Ultimate : public Board<T>
{
private:
    vector<vector<T>> winners;
    pair<bool, char> _is_win(int i, int j);
public:
    Ultimate();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
Ultimate<T>::Ultimate() : winners(3, vector<T>(3, '\0'))
{
    this->rows = this->columns = 9;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Ultimate<T>::update_board(int x, int y, T mark)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0) && winners[x / 3][y / 3] == 0)
    {
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template <typename T>
void Ultimate<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == 0)
                cout << "   |";
            else
                cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n----------------------------------------";
    }
    cout << endl;
    cout << "minimized version\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < 3; j++)
        {
            if (this->winners[i][j] == 0)
                cout << "   |";
            else
                cout << setw(2) << this->winners[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << "\n\n";
}

template <typename T>
bool Ultimate<T>::is_win()
{
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            auto it = _is_win(i, j);
            if (it.first  )
            {
                winners[i / 3][j / 3] = it.second;
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if ((winners[i][0] == winners[i][1] && winners[i][1] == winners[i][2] && winners[i][0] != 0) ||
            (winners[0][i] == winners[1][i] && winners[1][i] == winners[2][i] && winners[0][i] != 0))
        {

            this->display_board();
            return true;
        }
    }
    if ((winners[0][0] == winners[1][1] && winners[1][1] == winners[2][2] && winners[0][0] != 0) ||
        (winners[0][2] == winners[1][1] && winners[1][1] == winners[2][0] && winners[0][2] != 0))
    {
        this->display_board();
        return true;
    }
    return false;
}

template <typename T>
pair<bool, char> Ultimate<T>::_is_win(int sr, int sc)
{
    for (int i = 0; i < 3; i++)
    {
        if (this->board[sr + i][sc] == this->board[sr + i][sc + 1] && this->board[sr + i][sc + 1] == this->board[sr + i][sc + 2] && this->board[sr + i][sc] != 0)
        {
            return {true, this->board[sr + i][sc]};
        }
        if (this->board[sr][sc + i] == this->board[sr + 1][sc + i] && this->board[sr + 1][sc + i] == this->board[sr + 2][sc + i] && this->board[sr][sc + i] != 0)
        {
            return {true, this->board[sr][sc + i]};
        }
    }
    if (this->board[sr][sc] == this->board[sr + 1][sc + 1] && this->board[sr + 1][sc + 1] == this->board[sr + 2][sc + 2] && this->board[sr][sc] != 0)
    {
        return {true, this->board[sr][sc]};
    }
    if (this->board[sr][sc + 2] == this->board[sr + 1][sc + 1] && this->board[sr + 1][sc + 1] == this->board[sr + 2][sc] && this->board[sr][sc + 2] != 0)
    {
        return {true, this->board[sr][sc + 2]};
    }
    return {false, '\0'};
}

template <typename T>
bool Ultimate<T>::is_draw()
{
    for(int i = 0;i<9;i+=3)
    {
        for(int j = 0;j<9;j+=3)
        {
            if(winners[i/3][j/3])
            {
                continue;
            }
            if(this->board[i][j]==0)
                return false;
        }
    }

    bool ok =!is_win();
    if(ok)
    {
        this->display_board();
    }
    return ok;
}

template <typename T>
bool Ultimate<T>::game_is_over()
{
    return is_win() || is_draw();
}


//player
template <typename T>
class Ultimate_Player : public Player<T> 
{
public:
    Ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;
};
template <typename T>
Ultimate_Player<T>::Ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Ultimate_Player<T>::getmove(int& x, int& y) 
{
    cout << "\nPlease enter your move x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
}

// random player


template <typename T>
class Ultimate_Random_Player : public RandomPlayer<T>
{
public:
    Ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
Ultimate_Random_Player<T>::Ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

template <typename T>
void Ultimate_Random_Player<T>::getmove(int& x, int& y) 
{
    x = rand() % this->dimension;  
    y = rand() % this->dimension;
}



#endif