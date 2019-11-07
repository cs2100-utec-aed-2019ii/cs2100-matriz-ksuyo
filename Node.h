//
// Created by Gabriel Spranger Rojas on 11/6/19.
//

#ifndef CS2100_MATRIZ_KSUYO_NODE_H
#define CS2100_MATRIZ_KSUYO_NODE_H

#include "Macros.h"

template <typename T>
class Node {
public:
    T data;
    NumericType posX;
    NumericType posY;
    Node<T>* next;
    Node<T>* down;
};

#endif //CS2100_MATRIZ_KSUYO_NODE_H
