#include <iostream> 
#include <vector> 

using namespace std;

class TicTacToe {
public:
    TicTacToe();
    void playGame(char);
private:
    vector<vector<char>> cells;
    char c_player;
    void BoardPrint();
    bool checkFull();
    bool checker(char);
    pair<int, int> CompMove();
    int minimax(int, bool);
    void playerMove();
};

