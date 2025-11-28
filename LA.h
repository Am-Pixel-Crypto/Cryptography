
// Linear Algebra
//
//
//
// Authors:  Mahmoud Mostafa
//           Haytham Ashraf

#ifndef _LA_H_
#define _LA_H_

#include <fstream>

using namespace std;

class Matrix {
public:

    // ctors
    Matrix();
    Matrix(int size);
    Matrix(int rows, int cols);
    Matrix(Matrix& mat);
    ~Matrix();

    // retrive the determine
    double Determinant();

    // determine if matrix is invertible
    bool isInvertible();

    // check if this matrix can be multiplied with another matrix
    bool CanMulWith(const Matrix& mat);

    // produce an inversed matrix from this matrix
    Matrix Inverse();

    // retrive row by index
    double* operator[](int index);

    // multiply two matrices
    Matrix& operator*(const Matrix& A);

    // print a matrix to a file stream or to the console
    friend ostream& operator<<(ostream& os, const Matrix& A);
private:

    int rows, cols;
    double** m;

    // this function will actually allocate 'm'
    void Create(int _rows, int _cols);
};


/*
    void saveEncodingMatrix(int A[3][3], int size);
    int savedMatrix();
    bool loadMatrix(int choice, int A[3][3], int &size);

    Moved to io.h
*/

#endif // _LA_H_