#include <iostream>
#include <vector>
#include "Header1.h"

using namespace std;

TicTacToe::TicTacToe() : cells(3, vector<char>(3, ' ')), c_player('X') {}

void TicTacToe::BoardPrint() {
    cout << "Current board:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << cells[i][j];
            if (j < 2) cout << " || ";
        }
        cout << endl;
        if (i < 2) cout << "------------" << endl;
    }
}

bool TicTacToe::checkFull() {
    for (const auto& row : cells) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

bool TicTacToe::checker(char player) {
    for (int i = 0; i < 3; ++i) {
        if (cells[i][0] == player && cells[i][1] == player && cells[i][2] == player) return true;
        if (cells[0][i] == player && cells[1][i] == player && cells[2][i] == player) return true;
    }
    if (cells[0][0] == player && cells[1][1] == player && cells[2][2] == player) return true;
    if (cells[0][2] == player && cells[1][1] == player && cells[2][0] == player) return true;
    return false;
}

pair<int, int> TicTacToe::CompMove() {
    int best = -100000000;
    pair<int, int> bestMove;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (cells[i][j] == ' ') {
                cells[i][j] = 'O';
                int score = minimax(0, false);
                cells[i][j] = ' ';
                if (score > best) {
                    best = score;
                    bestMove = { i, j };
                }
            }
        }
    }
    return bestMove;
}

int TicTacToe::minimax(int depth, bool isMax) {
    if (checker('O')) return 10 - depth;
    if (checker('X')) return depth - 10;
    if (checkFull()) return 0;

    if (isMax) {
        int best = -10000000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (cells[i][j] == ' ') {
                    cells[i][j] = 'O';
                    int score = minimax(depth + 1, false);
                    cells[i][j] = ' ';
                    best = max(score, best);
                }
            }
        }
        return best;
    }
    else {
        int best = 100000000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (cells[i][j] == ' ') {
                    cells[i][j] = 'X';
                    int score = minimax(depth + 1, true);
                    cells[i][j] = ' ';
                    best = min(score, best);
                }
            }
        }
        return best;
    }
}

void TicTacToe::playerMove() {
    int row, column;
    while (true) {
        cout << "Enter move " << c_player << "(row and column separated by a space): ";
        cin >> row >> column;
        if (row >= 1 && row <= 3 && column >= 1 && column <= 3 && cells[row - 1][column - 1] == ' ') {
            cells[row - 1][column - 1] = c_player;
            break;
        }
        else {
            cout << "Try another move" << endl;
        }
    }
}


void TicTacToe::playGame(char numb) {
    BoardPrint();
    if (numb == '1') {
        while (true) {
            if (c_player == 'X') {
                playerMove();
                c_player = 'O';
            }
            else {
                pair<int, int> C_Move = CompMove();
                cells[C_Move.first][C_Move.second] = 'O';
                c_player = 'X';
            }
            cout << "Computer Move:" << endl;
            BoardPrint();
            if (checker('X')) {
                cout << "X win" << endl;
                break;
            }
            if (checker('O')) {
                cout << "O win" << endl;
                break;
            }
            if (checkFull()) {
                cout << "Draw" << endl;
                break;
            }
        }
    }
    else if (numb == '2') {
        while (true) {
            if (c_player == 'X') {
                playerMove();
                c_player = 'O';
            }
            else {
                playerMove();
                c_player = 'X';
            }
            BoardPrint();
            if (checker('X')) {
                cout << "X win" << endl;
                break;
            }
            if (checker('O')) {
                cout << "O win" << endl;
                break;
            }
            if (checkFull()) {
                cout << "Draw" << endl;
                break;
            }

        }
    }
}

int main() {
    TicTacToe game;
    char numb = 0;
    cout << "Choose 1 or 2 players" << endl;
    cin >> numb;
    while (true) {
        if (numb != '1' && numb != '2') {
            cout << "Incorrect choice. Choose 1 or 2" << endl;
        }
        else {
            break;
        }
        cout << "Choose 1 or 2 players";
        cin >> numb;
    }
    game.playGame(numb);
    return 0;
}
