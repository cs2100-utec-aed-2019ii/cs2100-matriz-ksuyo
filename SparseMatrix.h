//
// Created by Benjamin Diaz Garcia on 11/6/19.
//

#ifndef CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H
#define CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Nodes.h"

template <typename T>
class SparseMatrix {
public:
    HeaderNode<T, true>* xAxis = nullptr;
    HeaderNode<T, false>* yAxis = nullptr;
    NumericType columns = 0;
    NumericType rows = 0;
    int columnsMatrix = 0;
    int rowsMatrix = 0;

public:
    SparseMatrix() = default;

    /// Insert

    void insert(const NumericType& column, const NumericType& row, T data) {

        if (columns != 0 && rows != 0) {
            auto busquedaX = xAxis;
            int contador = 0;

            while (busquedaX->x != row) {
                busquedaX = busquedaX->right;
                if (contador == columns) {
                    goto start;
                }
                contador++;
            }

            auto aux = busquedaX->down;
            if (aux->y > column) {
                goto start;
            }


            while (aux->y < column && aux->down != nullptr) {
                aux = aux->down;
            }
            if (aux->y == column){
                goto fail;
            } else {
                goto start;
            }

        } else {
            goto start;
        }

        fail:
        std::cout << "La posición ya está ocupada" << std::endl;
        return;

        start:

        if (xAxis == nullptr){
            xAxis = new HeaderNode<T, true> (row);
            xAxis->right = xAxis;
        } else {
            auto check_x = xAxis;

            if (check_x->x == row){
                goto y;
            }
            check_x = check_x->right;
            while (check_x != xAxis){
                if (check_x->x == row){
                    goto y;
                }
                check_x = check_x->right;
            }

            auto new_x = new HeaderNode<T, true> (row);
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
            yAxis = new HeaderNode<T, false> (column);
            yAxis->down = yAxis;
        } else {
            auto check_y = yAxis;

            if (check_y->y == column){
                goto end;
            }
            check_y = check_y->down;
            while (check_y != yAxis){
                if (check_y->y == column){
                    goto end;
                }
                check_y = check_y->down;
            }

            auto new_y = new HeaderNode<T, false> (column);
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

        auto new_node = new ElementNode<T> (row, column, data);
        auto tempx = xAxis;
        auto tempy = yAxis;

        while (tempx->x != row){
            tempx = tempx->right;
        }

        while (tempy->y != column){
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

            while(temp->down != nullptr && temp->down->y < new_node->y && contador < rows-1) {
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

            while(temp->right != nullptr && temp->right->x < new_node->y && contador < columns-1) {
                temp = temp->right;
                contador++;
            }

            auto aux = temp->right;
            temp->right = new_node;
            new_node->right = aux;
        }


    }

    /// Erase

    void erase(const NumericType& column, const NumericType& row) {
        /// Encontrar el eje Y y X
        auto xPrev = xAxis;
        auto yPrev = yAxis;
        auto xAxisTemp = xAxis;
        auto yAxisTemp = yAxis;

        int contX = 0;
        int contY = 0;

        while (xAxisTemp->x != row) {
            if (contX == columns) return;
            contX++;
            xPrev = xAxisTemp;
            xAxisTemp = xAxisTemp->right;
        }

        while (yAxisTemp->y != column) {
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

        while (tempx->y != column && tempx->down != nullptr) {
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

        while (tempy->x != row && tempx->right != nullptr) {
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

    /// Clear

    void clear() {
        if (columns == 0 && rows == 0) {
            return;
        }

        /// Elimina todos los indices de X y los hijos de cada uno
        if (columns == 1) {
            auto node = xAxis->down;
            while (node->down != nullptr) {
                auto next = node->down;
                delete node;
                node = next;
            }
            delete node;
            delete xAxis;
        } else {
            auto tempX = xAxis;
            int contador = 0;
            while (contador < columns) {
                contador++;
                auto hijosX = tempX->down;
                while (hijosX->down != nullptr) {
                    auto nextHijo = hijosX->down;
                    delete hijosX;
                    hijosX = nextHijo;
                }
                delete hijosX;
                tempX = tempX->right;
            }

            contador = 0;
            tempX = xAxis;
            while (contador < columns) {
                auto nextX = tempX->right;
                delete tempX;
                tempX = nextX;
                contador++;
            }

        }

        xAxis = nullptr;

        /// Elimina todos los indices de Y
        if (rows == 1) {
            delete yAxis;
        } else {
            auto node = yAxis->down;

            while (node->down != yAxis) {
                auto next = node->down;
                delete node;
                node = next;
            }
            delete node;
        }

        yAxis = nullptr;

        columns = 0;
        rows = 0;

    }

    /// Matrix

    int** matrix() {
        int** a2d = nullptr;
        auto tempX = xAxis;
        auto tempY = yAxis;

        while (tempX->right != xAxis){
            tempX = tempX->right;
        }

        while (tempY->down != yAxis){
            tempY = tempY->down;
        }

        int maxX = tempX->x;
        int maxY = tempY->y;

        a2d = new int* [maxX+1];
        for (int i = 0; i < maxX+1; ++i) {
            a2d[i] = new int [maxY+1];
        }
        columnsMatrix = maxX+1;
        rowsMatrix = maxY+1;

        for (int i = 0; i < columnsMatrix; ++i) {
            for (int j = 0; j < rowsMatrix; ++j) {
                a2d[i][j] = 0;
            }
        }

        auto tempnew = xAxis;
        int contador = 0;

        while (contador < columns) {
            auto hijos = tempnew->down;
            while (hijos != nullptr){
                a2d[hijos->x][hijos->y] = hijos->data;
                hijos = hijos->down;
            }
            tempnew = tempnew->right;
            contador++;
        }

        return a2d;
    }

    /// Operator Overloading

    inline friend std::ostream& operator<< (std::ostream& os, SparseMatrix<T>& sm) {
       auto a = sm.matrix();

        for (int i = 0; i < sm.columnsMatrix; ++i) {
            for (int j = 0; j < sm.rowsMatrix; ++j) {
                os << std::setw(4) << a[i][j] << " ";
            }
            os << std::endl;
        }

       return os;

    }

    /// Static Methods

    SparseMatrix<T>* identity(const NumericType& row, const NumericType& col) {
        // TODO: return matriz with 1s in the diagonal, 0s elsewhere
        int x;
        int y;
        auto SM = new SparseMatrix();

        for (x = 0; x < row; ++x) {
            for (y = 0; y < col; ++y) {
                if (x == y) {
                    SM->insert(x, y, 1);
                }
            }
        }

        return SM;
    }


    static SparseMatrix<T>* load_from_image(const std::string& filename) {
        cv::Mat image = imread("/Users/benjamindiaz/CLionProjects/Ciclo 4/cs2100-matriz-ksuyo/"+filename, cv::IMREAD_COLOR);

        auto h = image.rows;
        auto w = image.cols;

        auto Matriz = new SparseMatrix<T>;

        /// Iterating through image's pixels
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                auto pixelData = image.at<cv::Vec3b>(r, c); // [0] blue channel, [1] green channel, [2] red channel
                auto red = pixelData[2];
                auto green = pixelData[1];
                auto blue = pixelData[0];
                auto colorAvg = (red + green + blue) / 3;
                if (colorAvg < 200) {
                    Pixel pixel = Pixel(pixelData[2], pixelData[1], pixelData[0]);
                    Matriz->insert(r, c, pixel.avg());
                }
            }
        }
        return Matriz;
    }

    ~SparseMatrix() {
        clear();
    }
};


template<>
class SparseMatrix<Pixel> {
public:
    HeaderNode<Pixel, true>* xAxis = nullptr;
    HeaderNode<Pixel, false>* yAxis = nullptr;
    NumericType columns = 0;
    NumericType rows = 0;
    int columnsMatrix = 0;
    int rowsMatrix = 0;

public:
    SparseMatrix() = default;

    /// Insert

    void insert(const NumericType& column, const NumericType& row, Pixel data) {

        if (columns != 0 && rows != 0) {
            auto busquedaX = xAxis;
            int contador = 0;

            while (busquedaX->x != row) {
                busquedaX = busquedaX->right;
                if (contador == columns) {
                    goto start;
                }
                contador++;
            }

            auto aux = busquedaX->down;
            if (aux->y > column) {
                goto start;
            }


            while (aux->y < column && aux->down != nullptr) {
                aux = aux->down;
            }
            if (aux->y == column){
                goto fail;
            } else {
                goto start;
            }

        } else {
            goto start;
        }

        fail:
        std::cout << "La posición ya está ocupada" << std::endl;
        return;

        start:

        if (xAxis == nullptr){
            xAxis = new HeaderNode<Pixel, true> (row);
            xAxis->right = xAxis;
        } else {
            auto check_x = xAxis;

            if (check_x->x == row){
                goto y;
            }
            check_x = check_x->right;
            while (check_x != xAxis){
                if (check_x->x == row){
                    goto y;
                }
                check_x = check_x->right;
            }

            auto new_x = new HeaderNode<Pixel, true> (row);
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
            yAxis = new HeaderNode<Pixel, false> (column);
            yAxis->down = yAxis;
        } else {
            auto check_y = yAxis;

            if (check_y->y == column){
                goto end;
            }
            check_y = check_y->down;
            while (check_y != yAxis){
                if (check_y->y == column){
                    goto end;
                }
                check_y = check_y->down;
            }

            auto new_y = new HeaderNode<Pixel, false> (column);
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

        auto new_node = new ElementNode<Pixel> (row, column, data);
        auto tempx = xAxis;
        auto tempy = yAxis;

        while (tempx->x != row){
            tempx = tempx->right;
        }

        while (tempy->y != column){
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

            while(temp->down != nullptr && temp->down->y < new_node->y && contador < rows-1) {
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

            while(temp->right != nullptr && temp->right->x < new_node->y && contador < columns-1) {
                temp = temp->right;
                contador++;
            }

            auto aux = temp->right;
            temp->right = new_node;
            new_node->right = aux;
        }


    }

    /// Erase

    void erase(const NumericType& column, const NumericType& row) {
        /// Encontrar el eje Y y X
        auto xPrev = xAxis;
        auto yPrev = yAxis;
        auto xAxisTemp = xAxis;
        auto yAxisTemp = yAxis;

        int contX = 0;
        int contY = 0;

        while (xAxisTemp->x != row) {
            if (contX == columns) return;
            contX++;
            xPrev = xAxisTemp;
            xAxisTemp = xAxisTemp->right;
        }

        while (yAxisTemp->y != column) {
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

        while (tempx->y != column && tempx->down != nullptr) {
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

        while (tempy->x != row && tempx->right != nullptr) {
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

    /// Clear

    void clear() {
        if (columns == 0 && rows == 0) {
            return;
        }

        /// Elimina todos los indices de X y los hijos de cada uno
        if (columns == 1) {
            auto node = xAxis->down;
            while (node->down != nullptr) {
                auto next = node->down;
                delete node;
                node = next;
            }
            delete node;
            delete xAxis;
        } else {
            auto tempX = xAxis;
            int contador = 0;
            while (contador < columns) {
                contador++;
                auto hijosX = tempX->down;
                while (hijosX->down != nullptr) {
                    auto nextHijo = hijosX->down;
                    delete hijosX;
                    hijosX = nextHijo;
                }
                delete hijosX;
                tempX = tempX->right;
            }

            contador = 0;
            tempX = xAxis;
            while (contador < columns) {
                auto nextX = tempX->right;
                delete tempX;
                tempX = nextX;
                contador++;
            }

        }

        xAxis = nullptr;

        /// Elimina todos los indices de Y
        if (rows == 1) {
            delete yAxis;
        } else {
            auto node = yAxis->down;

            while (node->down != yAxis) {
                auto next = node->down;
                delete node;
                node = next;
            }
            delete node;
        }

        yAxis = nullptr;

        columns = 0;
        rows = 0;

    }


    static SparseMatrix<Pixel>* load_from_image(const std::string& filename) {
        cv::Mat image = imread("/Users/benjamindiaz/CLionProjects/Ciclo 4/cs2100-matriz-ksuyo/"+filename, cv::IMREAD_COLOR);

        auto h = image.rows;
        auto w = image.cols;

        auto Matriz = new SparseMatrix<Pixel>;

        /// Iterating through image's pixels
        for (int r = 0; r < h; ++r) {
            for (int c = 0; c < w; ++c) {
                auto pixelData = image.at<cv::Vec3b>(r, c); // [0] blue channel, [1] green channel, [2] red channel
                auto red = pixelData[2];
                auto green = pixelData[1];
                auto blue = pixelData[0];
                auto colorAvg = (red + green + blue) / 3;
                if (colorAvg < 200) {
                    Pixel pixel = Pixel(pixelData[2], pixelData[1], pixelData[0]);
                    Matriz->insert(r, c, pixel);
                }
            }
        }
        return Matriz;
    }

    ~SparseMatrix() {
        clear();
    }

};

#endif //CS2100_MATRIZ_KSUYO_SPARSEMATRIX_H
