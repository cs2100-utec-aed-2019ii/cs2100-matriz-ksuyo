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

/*
    srand(time(nullptr));

    SparseMatrix<double> m1;

    for(int i= 0; i < 100; i++)
        m1.insert(rand()%100,rand()%100,rand()%255); // (f,c,val)

    cout << m1 << endl; // print in console

    m1.erase(100,2); // delete(f,c)

    SparseMatrix<double> m2 = SparseMatrix<double>::identity(m1.rows, m1.columns); //f,c

    ofstream _out("res.txt");
    _out << m2 << endl; // print in file
    _out.close();

    cout << mult(m1, m2) << endl; //  mutiplication
    cout << add(m1, m2) << endl; // addition
    cout << transpose(m1) << endl; // transpose
    cout << inv(m1) << endl; // Inversa - Extra!

    // Cargar desde imagen -  Extra (Usar CImg.h)
    SparseMatrix<double> m_image = SparseMatrix<double>::load_from_image("lenna.jpg");//512x512

    ofstream _out_i("res.txt");
    _out_i << m_image;
    _out_i.close();
*/

    SparseMatrix<int> m1;

    m1.insert(0, 0, 5);
    m1.insert(1, 1, 10);
    m1.insert(2, 2, 20);
    cout << m1.xAxis->x << " " << m1.yAxis->y << endl;

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
