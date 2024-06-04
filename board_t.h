#pragma once

#include <cmath>
#include "vector.h"

struct pair_t {
    int x, y;
};

struct board_t {
    int** table;
    int size;
    int redCounter;
    int blueCounter;
    bool isCorrect;
    bool** visited;
    int turn;

    board_t();

    void clear();
    void readBoard(vector* res);
    void parseBoard(vector* input);
    void getBoard();
    ~board_t();
};