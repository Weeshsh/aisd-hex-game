#include <iostream>
#include "string.h"
#include "vector.h"
#include "board_t.h"
#include "game_t.h"

int main() {
    game_t game;

    while (!game.flag) {
        game.clear();
        game.board.getBoard();
        game.handleQueries();
    }

    return 0;
}