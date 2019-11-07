//
// Created by Gabriel Spranger Rojas on 11/6/19.
//

#ifndef CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H
#define CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H

#include <iostream>
#include <fstream>

#include "Node.h"

template <typename T>
class SparseMatrix {
public:
    Node<T>* x;
    Node<T>* y;
    NumericType columns;
    NumericType rows;

public:
    SparseMatrix() = default;

    /// Insert

    void insert(const NumericType& row, const NumericType& col, T data) {
        // TODO: insert
    }

    /// Erase

    void erase(const NumericType& row, const NumericType& col) {
        // TODO: erase
    }

    /// Operator Overloading

    inline friend std::ostream& operator<< (std::ostream& os, SparseMatrix<T>& sm) {
        // TODO: print matrix with 0s and the data. Example:
        // 0 0 0 1
        // 1 0 0 5
        // 6 0 0 3
    }

    /// Static Methods

    static SparseMatrix<T>& identity(const NumericType& row, const NumericType& col) {
        // TODO: return matriz with 1s in the diagonal, 0s elsewhere
    }

    static SparseMatrix<T>& load_from_image(const std::string& filename) {
        // TODO: return sparse matrix from file using CImg.h
    }

    ~SparseMatrix() {
        // TODO: free memory
    }
};













































#endif //CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H
