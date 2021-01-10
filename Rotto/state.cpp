//
// Created by heechan on 21. 1. 9..
//

#include "state.h"
#include <random>

void state::init()
{
    std::random_device rd;
    vector<int> shuffle(45);

    std::iota(shuffle.begin(), shuffle.end(), 1);
    std::shuffle(shuffle.begin(), shuffle.end(), std::mt19937{rd()});

    bonus = shuffle[0];
    numbers = std::vector<int>(shuffle.begin()+1, shuffle.begin()+6);
}

state::state()
{
    init();
}

state::~state()
= default;
