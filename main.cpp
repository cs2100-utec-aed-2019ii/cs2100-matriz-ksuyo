#include "SparseMatrix.h"

using namespace std;

template <typename T>
SparseMatrix<T>* mult(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2);

template <typename T>
SparseMatrix<T>* add(SparseMatrix<T>& sm1, SparseMatrix<T>& sm2);

template <typename T>
SparseMatrix<T>* transpose(const SparseMatrix<T>& sm1);

template <typename T>
SparseMatrix<T>* inv(const SparseMatrix<T>& sm1);

int main(int argc, char** argv) {

    srand(time(nullptr));

    SparseMatrix<double> m1;
    m1.insert(0, 0, 5);
    m1.insert(1, 1, 10);
    m1.insert(2, 2, 20);
    m1.insert(3, 5, 100);
    m1.insert(5, 5, 30);
    m1.insert(1, 3, 20);
    m1.insert(2, 5, 30);
    m1.insert(5, 5, 40);

 //   cout << "filas ocupadas: " << m1.rows << ", columnas ocupadas: " << m1.columns << endl;
    cout << m1 << endl;
    auto m2 = add(m1, m1);
    cout << *m2 << endl;
    return 0;
}
















template <typename T>
SparseMatrix<T>* mult(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2) {

}

template <typename T>
SparseMatrix<T>* add(SparseMatrix<T>& sm1, SparseMatrix<T>& sm2) {
    auto m1 = sm1.matrix();
    auto m2 = sm2.matrix();
    if(sm1.columnsMatrix == sm2.columnsMatrix && sm2.rowsMatrix == sm1.rowsMatrix){

        int** m3 = nullptr;

        m3 = new int* [sm1.columnsMatrix];
        for (int i = 0; i < sm1.columnsMatrix; ++i) {
            m3[i] = new int [sm1.columnsMatrix];
        }

        for (int i = 0; i < sm1.columnsMatrix; ++i) {
            for (int j = 0; j < sm1.rowsMatrix; ++j) {
                m3[i][j] = 0;
            }
        }

        for(unsigned i = 0; i < sm1.columnsMatrix; ++i ) {
            for (unsigned j = 0; j < sm1.rowsMatrix; ++j) {
                m3[i][j] = m1[i][j] + m2[i][j];
            }
        }

        auto* m3a = new SparseMatrix<T>();
        for(unsigned i = 0; i < sm1.columnsMatrix; ++i ) {
            for (unsigned j = 0; j < sm1.rowsMatrix; ++j) {
                if (m3[i][j] != 0)
                    m3a->insert(j,i,m3[i][j]);
            }
        }
        return m3a;
    }
}

template <typename T>
SparseMatrix<T>* transpose(const SparseMatrix<T>& sm1) {
    // TODO
}

template <typename T>
SparseMatrix<T>* inv(const SparseMatrix<T>& sm1) {
    // TODO
}
