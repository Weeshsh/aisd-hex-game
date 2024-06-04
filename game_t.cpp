#include "game_t.h"
#include <iostream>
#include <cstring>

#define NO_PAWN 0
#define RED 1
#define BLUE 2

#define WON 3

#define GROWTH 2

game_t::game_t() : input(), board(), flag(false) {}

int game_t::emptySpaces() {
    int counter = 0;

    for (int column = 0; column < board.size; column++) 
        for (int row = 0; row < board.size; row++) 
            if (board.table[row][column] == NO_PAWN) 
                counter++;

    return counter;
}

void game_t::getLine() {
    input.clear();
    char inp = ' ';

    while (inp != '\n') {
        inp = getchar();

        if (inp != '\n') 
            input.pushBack(inp);
        
    }
}

bool game_t::isValidMove(int type, int row, int column) {
    return (row >= 0 &&
        column >= 0 &&
        row < this->board.size &&
        column < this->board.size &&
        board.table[row][column] == type &&
        !board.visited[row][column]);
}

bool game_t::DFS(int type, int row, int column) {
    int moves[6][2] = { {-1, 0}, {0, 1},{-1, -1},  {1, 1}, {1, 0},  {0, -1} };

    if (type == BLUE) {
        if (row == board.size - 1)
            return true;

        moves[0][0] = 0; moves[0][1] = -1;
        moves[1][0] = 1; moves[1][1] = 0;
        moves[2][0] = 1; moves[2][1] = 1;
        moves[3][0] = 0; moves[3][1] = 1;
        moves[4][0] = -1; moves[4][1] = 0;
        moves[5][0] = -1; moves[5][1] = -1;
    }
    else
        if (column == board.size - 1) 
            return true;
        

    board.visited[row][column] = true;


    for (int i = 0; i < 6; i++) 
        if (isValidMove(type, row + moves[i][0], column + moves[i][1]))
            if (DFS(type, row + moves[i][0], column + moves[i][1]))
                return true;
    

    return false;
}

int game_t::checkGameOver() {
    int size = board.size;
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++) 
            board.visited[i][j] = false;
    

    for (int i = 0; i < size; i++)
        if (board.table[i][0] == RED)
            if (DFS(RED, i, 0)) 
                return RED;
            

    for (int i = 0; i < size; i++)
        if (board.table[0][i] == BLUE)
            if (DFS(BLUE, 0, i)) 
                return BLUE;
            
    return 0;
}

int game_t::checkGameOver(int type) {
    int size = board.size;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board.visited[i][j] = false;
        }
    }

    if (type == RED) {
        for (int i = 0; i < size; i++)
            if (board.table[i][0] == RED)
                if (DFS(RED, i, 0)) {
                    return WON;
                }
    }
    else if (type == BLUE) {
        for (int i = 0; i < size; i++)
            if (board.table[0][i] == BLUE)
                if (DFS(BLUE, 0, i)) {
                    return WON;
                }
    }
    return 0;
}

bool game_t::isPossible() {
    int temp = checkGameOver();

    if (temp == RED && board.redCounter <= board.blueCounter)
        return 0;

    if (temp == BLUE && board.redCounter > board.blueCounter)
        return 0;

    if (temp == 0)
        return 1;


    for (int column = 0; column < board.size; column++)
        for (int row = 0; row < board.size; row++)
            if (board.table[row][column] == temp) {
                board.table[row][column] = NO_PAWN;

                int res = checkGameOver();
                board.table[row][column] = temp;

                if (res != temp)
                    return 1;
            }
    return 0;
}

int game_t::checkNaive(int type, int moves) {
    int missingOpponentPawns = 0;
    
    if (type == RED && board.turn == RED) {
        missingOpponentPawns = moves - 1;
    }
    else if (type == BLUE && board.turn == BLUE) {
        missingOpponentPawns = moves - 1;
    }
    else {
        missingOpponentPawns = moves;
    }

    if (!moves) {
        if (checkGameOver(type) == WON) 
            if (emptySpaces() >= missingOpponentPawns)
                return WON;
        return 0;
    }
    else if (checkGameOver(type) == WON)
        return 0;


    int temp = 0;
    for (int column = 0; column < board.size; column++) 
        for (int row = 0; row < board.size; row++) 
            if (board.table[row][column] == NO_PAWN) {
                board.table[row][column] = type;

                temp = checkNaive(type, moves - 1, missingOpponentPawns);
                board.table[row][column] = NO_PAWN;
                
                if (temp == WON)
                    return WON;
            }

    return 0;

}

int game_t::checkNaive(int type, int moves, int missingOpponentPawns) {
    if (!moves) {
        if (checkGameOver(type) == WON) 
            if (emptySpaces() >= missingOpponentPawns)
                return WON;
            return 0;
        }
        else if (checkGameOver(type) == WON)
            return 0;



    int temp = 0;
    for (int column = 0; column < board.size; column++) 
        for (int row = 0; row < board.size; row++) 
            if (board.table[row][column] == NO_PAWN) {
                board.table[row][column] = type;

                temp = checkNaive(type, moves - 1, missingOpponentPawns);
                board.table[row][column] = NO_PAWN;

                if (temp == WON)
                    return WON;
            }

    return 0;
}

void game_t::naive() {
    printf(checkNaive(RED, 1) ? "YES\n" : "NO\n");
    printf(checkNaive(BLUE, 1) ? "YES\n" : "NO\n");
    printf(checkNaive(RED, 2) ? "YES\n" : "NO\n");
    printf(checkNaive(BLUE, 2) ? "YES\n" : "NO\n");
}

void game_t::clear() {
    board.clear();
    input.clear();
    flag = false;
}

void game_t::handleQueries() {
    while (true) {
        getLine();
        if (strcmp(input.str, "BOARD_SIZE") == 0)
            printf("%d\n", board.size);

        else if (strcmp(input.str, "PAWNS_NUMBER") == 0)
            printf("%d\n", board.blueCounter + board.redCounter);

        if (strcmp(input.str, "IS_BOARD_CORRECT") == 0) {
            if (board.isCorrect)
                printf("YES\n");
            else
                printf("NO\n");
        }
        else if (strcmp(input.str, "IS_GAME_OVER") == 0) {
            if (board.isCorrect) {

                switch (checkGameOver()) {
                case BLUE:
                    printf("YES BLUE\n");
                    break;
                case RED:
                    printf("YES RED\n");
                    break;
                default:
                    printf("NO\n");
                    break;
                }
            }
            else
                printf("NO\n");

        }
        else if (strcmp(input.str, "IS_BOARD_POSSIBLE") == 0) {
            if (board.isCorrect) {
                if (isPossible())
                    printf("YES\n");

                else
                    printf("NO\n");

            }
            else
                printf("NO\n");

        }
        else if (strcmp(input.str, "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") == 0) {
            getLine();
            getLine();
            getLine();
            if (board.isCorrect)
                naive();

            else
                printf("NO\nNO\nNO\nNO\n");

        }

        else if (strcmp(input.str, "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") == 0) {
            getLine();
            getLine();
            getLine();
            if (board.isCorrect)
                perfect();

            else
                printf("NO\nNO\nNO\nNO\n");

        }

        printf("\n");

        char temp = getchar();
        char c = getchar();
        
        ungetc(c, stdin);
        ungetc(temp, stdin);

        if (c == ' ' || temp == ' ')
            return;

        if (c == EOF) {
            flag = true;
            return;
        }
    }
}

int game_t::checkPerfectOneMove(int type) {
    if (checkGameOver())
        return 0;
    
    int temp = emptySpaces();

        if (type == board.turn) {
            if (temp < 1)
                return 0;

            return checkNaive(type, 1);
        } else {
            if (temp < 2)
                return 0;
            
            if (checkNaive(board.turn, 1)) 
                return 0;
        }

        temp = 0;
        int counter = 0;

        for (int column = 0; column < board.size; column++)
            for (int row = 0; row < board.size; row++)
                if (board.table[row][column] == NO_PAWN) {
                    board.table[row][column] = type;

                    temp = checkGameOver(type);

                    board.table[row][column] = NO_PAWN;

                    if (temp == WON) {
                        counter++;

                        if (counter > 1)
                            return 1;
                    }

                }
    return 0;
}

int game_t::checkPerfectTwoMoves(int type) {
    if (checkGameOver())
        return 0;

    int temp = emptySpaces();

    if (type == board.turn) {
        if (temp < 3)
            return 0;

        int res = 0;

        for (int column = 0; column < board.size; column++)
            for (int row = 0; row < board.size; row++)
                if (board.table[row][column] == NO_PAWN) {
                    board.table[row][column] = type;

                    board.turn = (type == RED ? BLUE : RED);

                    res = checkPerfectOneMove(type);

                    board.turn = type;

                    board.table[row][column] = NO_PAWN;
                    
                    if (res)
                        return 1;
                }

        return 0;
    }
    else {
        int counter = 0;

        if (temp < 4)
            return 0;

        for (int column = 0; column < board.size; column++)
            for (int row = 0; row < board.size; row++)
                if (board.table[row][column] == NO_PAWN) {
                    board.table[row][column] = board.turn;

                    for (int i = 0; i < board.size; i++)
                        for (int j = 0; j < board.size; j++)
                            if (board.table[i][j] == NO_PAWN) {
                                board.table[i][j] = type;

                                counter += checkPerfectOneMove(type);

                                board.table[i][j] = NO_PAWN;
                            }

                    board.table[row][column] = NO_PAWN;

                    if (counter == 0) 
                        return 0;
                    
                    counter = 0;
                }
    }
    return 1;
}

void game_t::perfect() {
    printf(checkPerfectOneMove(RED) ? "YES\n" : "NO\n");
    printf(checkPerfectOneMove(BLUE) ? "YES\n" : "NO\n");
    printf(checkPerfectTwoMoves(RED) ? "YES\n" : "NO\n");
    printf(checkPerfectTwoMoves(BLUE) ? "YES\n" : "NO\n");
}