#include "board_t.h"
#include <iostream>
#include "vector.h"

#define NO_PAWN 0
#define RED 1
#define BLUE 2

board_t::board_t() : table(nullptr), size(0), redCounter(0), blueCounter(0), isCorrect(false), visited(nullptr), turn(0) {}

void board_t::clear() {
    redCounter = 0;
    blueCounter = 0;
    isCorrect = false;

    if (table) {
        for (int i = 0; i < size; ++i) {
            delete[] table[i];
        }
        delete[] table;
        table = nullptr;
    }

    if (visited) {
        for (int i = 0; i < size; ++i) {
            delete[] visited[i];
        }
        delete[] visited;
        visited = nullptr;
    }

    size = 0;
}

void board_t::readBoard(vector* res) {
    char inp = ' ';
    int counter = 0, stop = 0;

    while (stop != 2) {
        while (inp != '\n') {
            inp = getchar();

            if (inp == '<') {
                getchar();
                inp = getchar();

                switch (inp) {
                case ' ':
                    res->pushBack(NO_PAWN);
                    break;
                case 'r':
                    res->pushBack(RED);
                    redCounter++;
                    break;
                case 'b':
                    res->pushBack(BLUE);
                    blueCounter++;
                    break;
                }
            }

            else if (inp == '-') {
                counter++;
                if (counter == 3) {
                    stop++;
                }
            }
            else {
                counter = 0;
            }
        }
        inp = ' ';
        counter = 0;
    }
}

void board_t::parseBoard(vector* input) {
    size = sqrt(input->length);
    table = new int* [size];

    for (int i = 0; i < size; i++)
        table[i] = new int[size];
    

    int row = 0;
    int i = 0;
    while (i < input->length) {
        int tempRow = row;
        int column = 0;

        if (row >= size) {
            tempRow = size - 1;
            column = row - size + 1;
        }

        while (tempRow >= 0 && column != size) 
            table[tempRow--][column++] = input->values[i++];
        
        row++;
    }
}

void board_t::getBoard() {
    vector inputArray;

    readBoard(&inputArray);

    parseBoard(&inputArray);

    isCorrect = (blueCounter == redCounter || blueCounter + 1 == redCounter);

    visited = new bool* [size];
    for (int i = 0; i < size; i++) {
        visited[i] = new bool[size];
        for (int j = 0; j < size; j++) {
            visited[i][j] = false;
        }
    }

    turn = RED;

    if ((redCounter + blueCounter) % 2 == 1) 
        turn = BLUE;
    
}

board_t::~board_t() {
    clear();
}
