//
// Created by yangheechan on 2020-12-20.
//
#include "TicTacToe.h"
#include <random>

TicTacToe::~TicTacToe()
{
}
TicTacToe::TicTacToe()
        :data(3, vector<string>(3, "")),
         turn("X")
{
}
void TicTacToe::toggleTurn()
{
    turn = (turn=="X") ? "O" : "X";
}
void TicTacToe::init()
{
    turn = "X";
    for (auto& elem: data) {
        for (auto& atom:elem) {
            atom = "";
        }
    }
}
void TicTacToe::setData(int row, int col)
{
    if (data[row][col].empty()) {
        data[row][col] = turn;

    }
    else {
        return;
    }

}
bool TicTacToe::CheckResult()
{
    winPoint.clear();

    for (int i = 0; i<3; i++) {
        // 가로라인
        if (data[i][0]==data[i][1] && data[i][1]==data[i][2]
                && !data[i][0].empty() && !data[i][1].empty() && !data[i][2].empty()) {
            winPoint.emplace_back(i, 0);
            winPoint.emplace_back(i, 1);
            winPoint.emplace_back(i, 2);
            return true;
        }
        // 세로라인
        if (data[0][i]==data[1][i] && data[1][i]==data[2][i]
                && !data[0][i].empty() && !data[1][i].empty() && !data[2][i].empty()) {
            winPoint.emplace_back(0, i);
            winPoint.emplace_back(1, i);
            winPoint.emplace_back(2, i);
            return true;
        }
    }
    // 대각선
    if (data[0][0]==data[1][1] && data[1][1]==data[2][2] &&
            !data[0][0].empty() && !data[1][1].empty() && !data[2][2].empty()) {
        winPoint.emplace_back(0, 0);
        winPoint.emplace_back(1, 1);
        winPoint.emplace_back(2, 2);
        return true;
    }
    if (data[0][2]==data[1][1] && data[1][1]==data[2][0]
            && !data[0][2].empty() && !data[1][1].empty() && !data[2][0].empty()) {
        winPoint.emplace_back(0, 2);
        winPoint.emplace_back(1, 1);
        winPoint.emplace_back(2, 0);
        return true;
    }
    return false;
}
bool TicTacToe::CheckFull()
{
    for (int i = 0; i<3; i++) {
        for (int j = 0; j<3; j++) {
            if (data[i][j].empty()) {
                return false;
            }
        }
    }

    return true;
}
std::pair<int, int> TicTacToe::coordinates()
{

    vector<std::pair<int, int>> empty;
    for (int row = 0; row<3; row++) {
        for (int column = 0; column<3; column++) {
            if (data[row][column].empty()) {
                empty.emplace_back(row, column);
            }
        }
    }

    std::random_device rd;
    std::shuffle(empty.begin(), empty.end(), std::mt19937{rd()});

    return empty[0];
}
vector<std::pair<int, int>> TicTacToe::getWinPoint() const
{
    return winPoint;
}
