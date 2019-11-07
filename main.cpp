#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    srand(time(nullptr));

    Matrix<double> m1;

    for(int i= 0; i < 100; i++)
        m1.insert(rand()%100,rand()%100,rand%250);//(f,c,val)

    cout << m1 << endl; // print in console

    m1.erase(100,2); // delete(f,c)

    Matrix<double> m2 = Matrix<double>::identity(m1.f,m1.f); //f,c

    ofstream _out("res.txt");
    _out << m2 << endl; // print in file
    _out.close();

    cout << mult(m1,m2) << endl; //  mutiplication
    cout << add(m1,m2) << endl; // addition
    cout << transpose(m1) << endl; // transpose
    cout << inv(m1) << endl; // Inversa - Extra!

    // Cargar desde imagen -  Extra (Usar CImg.h)
    Matrix<double> m_image = load_from_image("lenna.jpg");//512x512

    ofstream _out_i("res.txt");
    _out_i << m_image;
    _out_i.close();

    return 1;
}
