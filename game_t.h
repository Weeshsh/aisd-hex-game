#pragma once

#include "board_t.h"
#include "string.h"

struct game_t {
    string input;
    board_t board;
    bool flag;

    game_t();

    int emptySpaces();
    void getLine();

    bool isValidMove(int type, int row, int column);
    bool DFS(int type, int row, int column);
    
    int checkGameOver();
    int checkGameOver(int type);

    bool isPossible();
    
    int checkNaive(int type, int moves);
    int checkNaive(int type, int moves, int missingOpponentPawns);
    void naive();


    int checkPerfectOneMove(int type);
    int checkPerfectTwoMoves(int type);

    void perfect();

    void handleQueries();

    void clear();
};