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

        if (columns != 0 && rows != 0) {
            auto busquedaX = xAxis;
            int contador = 0;

            while (busquedaX->x != col) {
                busquedaX = busquedaX->right;
                if (contador == columns) {
                    goto start;
                }
                contador++;
            }
            auto aux = busquedaX->down;
            if (aux->y > row) {
                goto start;
            }

            while (aux->y < row) {
                aux = aux->down;
            }
            if (aux->y == row){
                goto fail;
            } else {
                goto start;
            }

        } else {
            goto start;
        }

        fail:
        cout << "La posición ya está ocupada" << endl;
        return;

        start:

        if (xAxis == nullptr){
            xAxis = new HeaderNode<T, true> (col);
            xAxis->right = xAxis;
        } else {
            auto check_x = xAxis;

            if (check_x->x == col){
                goto y;
            }
            check_x = check_x->right;
            while (check_x != xAxis){
                if (check_x->x == col){
                    goto y;
                }
                check_x = check_x->right;
            }

            auto new_x = new HeaderNode<T, true> (col);
            auto temp = xAxis;
            if (xAxis->right != xAxis) {
                while (temp->right->x < new_x->x && temp->right != xAxis) {
                    temp = temp->right;
                }
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
        columns++;
        y:

        if (yAxis == nullptr){
            yAxis = new HeaderNode<T, false> (row);
            yAxis->down = yAxis;
        } else {
            auto check_y = yAxis;

            if (check_y->y == row){
                goto end;
            }
            check_y = check_y->down;
            while (check_y != yAxis){
                if (check_y->y == row){
                    goto end;
                }
                check_y = check_y->down;
            }

            auto new_y = new HeaderNode<T, false> (row);
            auto temp = yAxis;
            if (yAxis->down != yAxis) {
                while (temp->down->y < new_y->y && temp->down != yAxis) {
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
        rows++;
        end:

        auto new_node = new ElementNode<T> (col, row, data);
        auto tempx = xAxis;
        auto tempy = yAxis;

        while (tempx->x != col){
            tempx = tempx->right;
        }

        while (tempy->y != row){
            tempy = tempy->down;
        }

        if (tempx->down == nullptr){
            tempx->down = new_node;
            new_node->downToHeader = tempx;
            new_node->down = nullptr;
        } else if (tempx->down->downToHeader == tempx) {
            if (tempx->down->y > new_node->y){
                auto temp_new_down = tempx->down;
                tempx->down = new_node;
                new_node->down = temp_new_down;
                temp_new_down->downToHeader = tempx;
            } else {
                tempx->down->down = new_node;
                new_node->downToHeader = tempx;
                new_node->down = nullptr;
            }
        } else {
            auto temp = tempx->down;
            int contador = 0;

            while(temp->down->y < new_node->y && contador < rows-1) {
                temp = temp->down;
                contador++;
            }

            auto aux = temp->down;
            temp->down = new_node;
            new_node->down = aux;
        }

//TODO

        if (tempy->right == nullptr){
            tempy->right = new_node;
            new_node->rightToHeader = yAxis;
            new_node->right = nullptr;
        } else if (tempy->right->rightToHeader == tempy) {
            if (tempy->right->x > new_node->x){
                auto temp_new_right = tempy->right;
                tempy->right = new_node;
                new_node->right = temp_new_right;
                temp_new_right->rightToHeader = tempy;
            } else {
                tempy->right->right = new_node;
                new_node->rightToHeader = tempy;
                new_node->right = nullptr;
            }
        } else {
            auto temp = tempy->right;
            int contador = 0;

            while(temp->right->x < new_node->y && contador < columns-1) {
                temp = temp->right;
                contador++;
            }

            auto aux = temp->right;
            temp->right = new_node;
            new_node->right = aux;
        }


    }

    /// Erase

    void erase(const NumericType& row, const NumericType& col) {
        /// Encontrar el eje Y y X
        auto xPrev = xAxis;
        auto yPrev = yAxis;
        auto xAxisTemp = xAxis;
        auto yAxisTemp = yAxis;

        int contX = 0;
        int contY = 0;

        while (xAxisTemp->x != col) {
            if (contX == columns) return;
            contX++;
            xPrev = xAxisTemp;
            xAxisTemp = xAxisTemp->right;
        }

        while (yAxisTemp->y != row) {
            if (contY == rows) return;
            contY++;
            yPrev = yAxisTemp;
            yAxisTemp = yAxisTemp->down;
        }

        /// Encontrar el nodo

        auto tempx = xAxisTemp->down;
        auto tempy = yAxisTemp->right;

        auto auxX = tempx;
        auto auxY = tempy;

        while (tempx->y != row && tempx->down != nullptr) {
            auxX = tempx;
            tempx = tempx->down;
        }

        auto nodeToDeleteX = tempx;


        /// Si es el primero
        if (auxX->data == tempx->data) {
            /// Si es el unico
            if (auxX->down == nullptr) {
                /// Si es el primer header
                if (xPrev->x == xAxisTemp->x) {
                    /// Si soy el unico header
                    if (xPrev->right == xPrev){
                        delete xAxis;
                        xAxis = nullptr;
                    } else {
                        /// Ir al ultimo
                        auto lastX = xPrev;
                        auto rightXPrev = xPrev->right;
                        while (lastX->right != xPrev){
                            lastX = lastX->right;
                        }
                        xAxis = rightXPrev;
                        lastX->right = rightXPrev;
                        delete xPrev;
                    }
                    columns--;
                    goto headerY;
                }
                xPrev->right = xAxisTemp->right;
                delete xAxisTemp;
                columns--;
            } else {
                xAxisTemp->down = tempx->down;
            }
        }

        headerY:

        while (tempy->x != col && tempx->right != nullptr) {
            auxY = tempy;
            tempy = tempy->right;
        }


        /// Si es el primero
        if (auxY->data == tempy->data) {
            if (yPrev->y == yAxisTemp->y) {
                ///Si soy el unico header
                if (yPrev->down == yPrev){
                    delete yAxis;
                    yAxis = nullptr;
                } else {
                    ///Ir al ultimo
                    auto lastY = yPrev;
                    auto downYPrev = yPrev->down;
                    while (lastY->down != yPrev){
                        lastY = lastY->down;
                    }
                    yAxis = downYPrev;
                    lastY->down = downYPrev;
                    delete yPrev;
                }
                rows--;
                goto endHeaders;
            }

            yPrev->down = yAxisTemp->down;
            delete yAxisTemp;
            rows--;
            } else {
                yAxisTemp->right = tempy->right;
            }

        endHeaders:

        delete nodeToDeleteX;
    }

    /// Operator Overloading

    inline friend std::ostream& operator<< (std::ostream& os, SparseMatrix<T>& sm) {
        auto smx = sm.xAxis;
        auto smy = sm.yAxis;

        os << "x: " << endl;
        os << smx->x << " ";
        smx = smx->right;
        while (smx != sm.xAxis) {
            os << smx->x << " ";
            smx = smx->right;
        }

        os << "\ny: " << endl;
        os << smy->y << " ";
        smy = smy->down;
        while (smy != sm.yAxis) {
            os << smy->y << " ";
            smy = smy->down;
        }

        return os;

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
