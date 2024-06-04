#ifndef VECTOR_H
#define VECTOR_H

#pragma once

struct vector {
    int* values;
    int size;
    int length;

    vector();
    void pushBack(int value);
    void clear();
    ~vector();
};

#endif