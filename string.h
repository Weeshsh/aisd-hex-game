#ifndef STRING_H
#define STRING_H

#pragma once

struct string {
    char* str;
    int size;
    int length;

    string();
    void pushBack(char c);
    void clear();
    ~string();
};

#endif