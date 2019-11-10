#ifndef CS2100_MATRIZ_KSUYO_NODES_H
#define CS2100_MATRIZ_KSUYO_NODES_H

#include "Macros.h"
#include "Pixel.h"


template <class T, bool isX>
struct HeaderNode {};

template <class T>
struct ElementNode {
    NumericType x = 0;
    NumericType y = 0;
    T data;
    enode* down = nullptr;
    enode* right = nullptr;
    HeaderNode<T, true>* downToHeader = nullptr;
    HeaderNode<T, false>* rightToHeader = nullptr;
    ElementNode(NumericType x, NumericType y, T data): x{x}, y{y}, data{data} {}

};

template <class T>
struct HeaderNode <T, true> {
    enode* down = nullptr;
    hnodex* right = nullptr;
    NumericType x;
    NumericType y = -1;
    explicit HeaderNode(NumericType x): x{x} {}
};

template <class T>
struct HeaderNode <T, false> {
    hnodey* down = nullptr;
    enode* right = nullptr;
    NumericType y;
    NumericType x = -1;
    explicit HeaderNode(NumericType y): y{y} {}
};

#endif