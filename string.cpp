#define _CRT_SECURE_NO_WARNINGS

#include "string.h"
#include <cstring>

#define GROWTH  2

string::string() : str{ new char[GROWTH] {'\0'} }, size{ GROWTH }, length{ 0 } {}

void string::pushBack(char c) {
    if (length + 1 >= size) {
        size *= GROWTH;
        char* temp = new char[size];
        strcpy(temp, str);
        delete[] str;
        str = temp;
    }
    str[length++] = c;
    str[length] = '\0';
}

void string::clear() {
    delete[] str;
    str = new char[GROWTH] {'\0'};
    size = GROWTH;
    length = 0;
}

string::~string() {
    delete[] str;
}