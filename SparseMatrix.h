//
// Created by Gabriel Spranger Rojas on 11/6/19.
//

#ifndef CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H
#define CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H

#include <iostream>
#include <fstream>

using namespace std;

#include "Nodes.h"

template <typename T>
class SparseMatrix {
public:
    HeaderNode<T, true>* xAxis = nullptr;
    HeaderNode<T, false>* yAxis = nullptr;
    NumericType columns = 0;
    NumericType rows = 0;

public:
    SparseMatrix() = default;

    /// Insert

    void insert(const NumericType& row, const NumericType& col, T data) {
        // TODO: insert
        if (xAxis == nullptr){
            xAxis = new HeaderNode<T, true> (col);
            xAxis->right = xAxis;
        } else {
            // TODO: revisar si ya existe el indice
            auto new_x = new HeaderNode<T, true> (col);
            auto temp = xAxis;
            if (xAxis->right == nullptr) {
                cout << "Entra" << endl;
                while (temp->right->x < new_x->x) {
                    temp = temp->right;
                }
                cout << "sale" << endl;
                if (temp->right != nullptr) {
                    auto temp_right = temp->right;
                    temp->right = new_x;
                    new_x->right = temp_right;
                } else {
                    temp->right = new_x;
                    new_x->right = xAxis;
                }
            } else {
                if (new_x->x < temp->x){
                    auto new_right = temp;
                    xAxis = new_x;
                    xAxis->right = new_right;
                    new_right->right = xAxis;
                } else {
                    xAxis->right = new_x;
                    new_x->right = xAxis;
                }
            }
        }


        if (yAxis == nullptr){
            yAxis = new HeaderNode<T, false> (row);
            yAxis->down = yAxis;
        } else {
            // TODO: revisar si ya existe el indice
            auto new_y = new HeaderNode<T, false> (row);
            auto temp = yAxis;
            if (yAxis->down == nullptr) {
                while (temp->down->y < new_y->y) {
                    temp = temp->down;
                }
                if (temp->down != nullptr) {
                    auto temp_down = temp->down;
                    temp->down = new_y;
                    new_y->down = temp_down;
                } else {
                    temp->down = new_y;
                    new_y->down = yAxis;
                }
            } else {
                if (new_y->y < temp->y){
                    auto new_down = temp;
                    yAxis = new_y;
                    yAxis->down = new_down;
                    new_down->down = yAxis;
                } else {
                    yAxis->down = new_y;
                    new_y->down = yAxis;
                }
            }
        }

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
