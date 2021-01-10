//
// Created by heechan on 21. 1. 9..
//

#ifndef ROTTO_STATE_H
#define ROTTO_STATE_H

#include <vector>

using std::vector;

class state {
private:
    vector<int> numbers;
    int bonus{};
public:
    state();

    ~state();

    void init();

    [[nodiscard]] int getBonus() const { return bonus; }
    [[nodiscard]] vector<int> getNumbers() const { return numbers; }
};

#endif //ROTTO_STATE_H
