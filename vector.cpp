#include "vector.h"

const int GROWTH = 2;

vector::vector() : values(new int[1] {0}), size(1), length(0) {}

void vector::pushBack(int value) {
    if (length + 1 >= size) {
        size *= GROWTH;
        int* temp = new int[size];
        for (int i = 0; i < length; i++) {
            temp[i] = values[i];
        }
        delete[] values;
        values = temp;
    }
    values[length++] = value;
}

void vector::clear() {
    delete[] values;
    values = new int[1] {0};
    size = 1;
    length = 0;
}

vector::~vector() {
    delete[] values;
}
