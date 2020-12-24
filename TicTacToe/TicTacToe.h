//
// Created by yangheechan on 2020-12-20.
//
#ifndef TICTACTOE_TICTACTOE_H
#define TICTACTOE_TICTACTOE_H
#include <vector>
#include <string>

using std::vector;
using std::string;

class TicTacToe {
public:
    TicTacToe();
    ~TicTacToe();
    void init();

    [[nodiscard]] string getTurn() const { return turn; }
    [[nodiscard]] string confirmData(int row, int col) const { return data[row][col]; }
    void setData(int row, int col);
    void toggleTurn();
    bool CheckResult();
    bool CheckFull();
    [[nodiscard]] vector<std::pair<int,int>> getWinPoint() const;
    std::pair<int, int> coordinates();
private:
    vector<vector<string>> data;
    vector<std::pair<int, int>> winPoint;
    string turn;
};

#endif //TICTACTOE_TICTACTOE_H
