#include "SparseMatrix.h"

using namespace std;

template <typename T>
SparseMatrix<T>& mult(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2);

template <typename T>
SparseMatrix<T>& add(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2);

template <typename T>
SparseMatrix<T>& transpose(const SparseMatrix<T>& sm1);

template <typename T>
SparseMatrix<T>& inv(const SparseMatrix<T>& sm1);

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
 //   cout << m1 << endl;

    auto m2 = SparseMatrix<double>::load_from_image("lenna.png");
    cout << *m2 << endl;
    cout << "filas ocupadas: " << m2->rows << ", columnas ocupadas: " << m2->columns << endl;
    return 0;
}
















template <typename T>
SparseMatrix<T>& mult(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2) {
    // TODO
}

template <typename T>
SparseMatrix<T>& add(const SparseMatrix<T>& sm1, const SparseMatrix<T>& sm2) {
    // TODO
}

template <typename T>
SparseMatrix<T>& transpose(const SparseMatrix<T>& sm1) {
    // TODO
}

template <typename T>
SparseMatrix<T>& inv(const SparseMatrix<T>& sm1) {
    // TODO
}
