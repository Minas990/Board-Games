#include <iostream>
#include <string>
#include "Pyramic_tic_tac_toe.h"
#include "Word_tic_tac_toe.h"
#include "SUS.h"
#include "Four-in-a-row.h"
#include "Numerical Tic-Tac-Toe.h"
#include "Ultimate Tic Tac Toe.h"

using namespace std;

void GamesMenu(int& choice) {
    cout << "1. Pyramic tic-tac-toe\n";
    cout << "2. Four-in-a-row\n";
    cout << "3. Word tic-tac-toe\n";
    cout << "4. Numerical tic-tac-toe\n";
    cout << "5. Ultimate tic-tac-toe\n";
    cout << "6. SUS tic-tac-toe\n";
    cout << "7. Exit\n";
    cout << "Choose a game: ";
    cin >> choice;
}

void SetUpPlayer(int& choice) {
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Choose Player type: ";
    cin >> choice;
}

template <typename T>
void CreatePlayers(Player<T>* players[], int gameNum, T symbol1, T symbol2) {
    int playerType1, playerType2;
    cout << "====================================\n";
    cout << "Player one setup:\n";
    SetUpPlayer(playerType1);
    cout << "====================================\n";
    cout << "Player two setup:\n";
    SetUpPlayer(playerType2);
    cout << "====================================\n";

    // Create Player 1
    if (playerType1 == 1) {
        string name;
        cout << "Enter player one name: ";
        cin.ignore();
        getline(cin, name);
        switch (gameNum) {
        case 1: players[0] = new pyramic_tic_tac_toe_player<T>(name, symbol1); break;
        case 2: players[0] = new Four_In_Player<T>(name, symbol1); break;
        case 3: players[0] = new Word_tic_tac_toe_player<T>(name, symbol1); break;
        case 4: players[0] = new Numeracle_Tic_Tac_TwoPlayer<T>(name, symbol1); break;
        case 5: players[0] = new Ultimate_Player<T>(name, symbol1); break;
        case 6: players[0] = new SUS_player<T>(name, symbol1); break;
        }
    }
    else {
        switch (gameNum) {
        case 1: players[0] = new pyramic_tic_tac_toe_randomplayer<T>(symbol1); break;
        case 2: players[0] = new Four_In_Random_Player<T>(symbol1); break;
        case 3: players[0] = new Word_tic_tac_toe_randomplayer<T>(symbol1); break;
        case 4: players[0] = new Numeracle_Tic_Tac_TwoRandom_Player<T>(symbol1); break;
        case 5: players[0] = new Ultimate_Random_Player<T>(symbol1); break;
        case 6: players[0] = new SUS_randomplayer<T>(symbol1); break;
        }
    }

    // Create Player 2
    if (playerType2 == 1) {
        string name;
        cout << "Enter player two name: ";
        cin.ignore();
        getline(cin, name);
        switch (gameNum) {
        case 1: players[1] = new pyramic_tic_tac_toe_player<T>(name, symbol2); break;
        case 2: players[1] = new Four_In_Player<T>(name, symbol2); break;
        case 3: players[1] = new Word_tic_tac_toe_player<T>(name, symbol2); break;
        case 4: players[1] = new Numeracle_Tic_Tac_TwoPlayer<T>(name, symbol2); break;
        case 5: players[1] = new Ultimate_Player<T>(name, symbol2); break;
        case 6: players[1] = new SUS_player<T>(name, symbol2); break;
        }
    }
    else {
        switch (gameNum) {
        case 1: players[1] = new pyramic_tic_tac_toe_randomplayer<T>(symbol2); break;
        case 2: players[1] = new Four_In_Random_Player<T>(symbol2); break;
        case 3: players[1] = new Word_tic_tac_toe_randomplayer<T>(symbol2); break;
        case 4: players[1] = new Numeracle_Tic_Tac_TwoRandom_Player<T>(symbol2); break;
        case 5: players[1] = new Ultimate_Random_Player<T>(symbol2); break;
        case 6: players[1] = new SUS_randomplayer<T>(symbol2); break;
        }
    }
}

int main() {
    int gameNum;

    GamesMenu(gameNum);

    while (gameNum >= 1 && gameNum <= 6) {
        cout << "====================================\n";

        // Handle Numerical Tic-Tac-Toe (int board) separately
        if (gameNum == 4) {
            Board<int>* board = new Numeracle_Tic_Tac_Two_Board<int>();
            Player<int>* players[2]{ nullptr, nullptr };
            CreatePlayers(players, gameNum, 0, 1); // Numerical symbols: 0 and 1
            GameManager<int> manager(board, players);
            manager.run();
            delete board;
            delete players[0];
            delete players[1];
        }
        else {
            Board<char>* board = nullptr;
            Player<char>* players[2]{ nullptr, nullptr };

            switch (gameNum) {
            case 1: board = new pyramic_tic_tac_toe_board<char>(); break;
            case 2: board = new Four_In_Board<char>(); break;
            case 3: board = new Word_tic_tac_toe_board<char>(); break;
            case 5: board = new Ultimate<char>(); break;
            case 6: board = new SUS_board<char>('S', 'U'); break;
            }
            if (gameNum == 6) CreatePlayers(players, gameNum, 'S', 'U'); // Symbols: 'S' and 'U'
            else CreatePlayers(players, gameNum, 'X', 'O'); // Symbols: 'X' and 'O'
            GameManager<char> manager(board, players);
            manager.run();
            delete board;
            delete players[0];
            delete players[1];
        }

        GamesMenu(gameNum);
    }

    return 0;
}
