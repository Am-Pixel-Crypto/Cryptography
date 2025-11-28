

//
//
// Authors:  Mahmoud Mostafa
//           Haytham Ashraf


#include <iostream>
#include "LA.h"

Matrix::Matrix(){
    rows = 0;
    cols = 0;
    m = NULL;
}

Matrix::Matrix(int size){
    Create(size, size);
}

Matrix::Matrix(Matrix& mat) {
    rows = mat.rows;
    cols = mat.cols;

    m = new double*[rows];
    for(int i = 0; i < rows; i++) {

        m[i] = new double[cols];
        for(int k = 0; k < cols; k++)
            m[i][k] = mat[i][k];
    }

    #ifdef _DEBUG
        cout << "Deep copy Matrix Constructor\n";
    #endif
}

Matrix::Matrix(int rows, int cols){
    Create(rows, cols);
}

Matrix::~Matrix(){
    if(m) {
        for(int i = 0; i < rows; i++)
            delete[] m[i];
        delete[] m;
    }
    m = NULL;
}

void Matrix::Create(int _rows, int _cols) {

    // check if previously created
    if(m != NULL) {
        for(int i = 0; i < rows; i++)
            delete[] m[i];
        delete[] m;
    }

    rows = _rows;
    cols = _cols;

    m = new double*[rows];
    for(int i = 0; i < rows; i++)
        m[i] = new double[cols];
}

bool Matrix::isInvertible() {
    return (Determinant() != 0);
}

double Matrix::Determinant() {
    double det = 0;

    // Only check if this matrix is a square matrix
    if(rows != cols) return false;

    switch(rows) {
        case 1: det = m[0][0];
                break;

        case 2: det = (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
                break;

        case 3: det = 
            (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])) -
            (m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])) +
            (m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
            break;

        default: cout << "Unsupported matrix 4x4\n";
    }

    return det;
}

bool Matrix::CanMulWith(const Matrix& mat) {
    return cols == mat.rows;
}

Matrix Matrix::Inverse() {

    // deep copy
    Matrix inv;
    
    // Once again, we would only find the inverse for squared matrices.
    
    if(rows != cols) {
        // We really don't expect the program to get here at this point.
        exit(1);
    }

    inv.Create(rows, cols);

    const double DET = inv.Determinant();

    switch(rows) {
        case 1: 
        {
            inv[0][0] = m[0][0];
        } break;

        case 2:
        {
            inv[0][0] =  m[1][1] / DET;
            inv[0][1] = -m[0][1] / DET;
            inv[1][0] = -m[1][0] / DET;
            inv[1][1] =  m[0][0] / DET;
        } break;

        case 3:
        {
            Matrix Cof(3);

            Cof[0][0] =  (m[1][1]*m[2][2] - m[1][2]*m[2][1]);
            Cof[0][1] = -(m[1][0]*m[2][2] - m[1][2]*m[2][0]);
            Cof[0][2] =  (m[1][0]*m[2][1] - m[1][1]*m[2][0]);
            Cof[1][0] = -(m[0][1]*m[2][2] - m[0][2]*m[2][1]);
            Cof[1][1] =  (m[0][0]*m[2][2] - m[0][2]*m[2][0]);
            Cof[1][2] = -(m[0][0]*m[2][1] - m[0][1]*m[2][0]);
            Cof[2][0] =  (m[0][1]*m[1][2] - m[0][2]*m[1][1]);
            Cof[2][1] = -(m[0][0]*m[1][2] - m[0][2]*m[1][0]);
            Cof[2][2] =  (m[0][0]*m[1][1] - m[0][1]*m[1][0]);

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    inv[i][j] = Cof[j][i] / DET;
        } break;

        default: 
            cout << "Unsupported matrix 4x4\n";
    }

    return inv;
}

double* Matrix::operator[](int index) {
    return m[index];
}

Matrix& Matrix::operator*(const Matrix& A) {
    // TBD ...
}

ostream& operator<<(ostream& os, const Matrix& A) {
    // TBD ...
}

/*

bool isInvertible(int A[3][3], int m) {
    double det = 0;

    if (m == 2) {
        det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
    }
    else if (m == 3) {
        det = 
            A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) -
            A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) +
            A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
    }
    // cout << "Determinant = " << det << endl;
    return (det != 0);
}



void inverse2x2(int A[3][3], double result[3][3]) {
    double det = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
    result[0][0] =  A[1][1] / det;
    result[0][1] = -A[0][1] / det;
    result[1][0] = -A[1][0] / det;
    result[1][1] =  A[0][0] / det;
}

void inverse3x3(int A[3][3], double result[3][3]) {
    double det =
        A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1]) -
        A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0]) +
        A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

    double Cof[3][3];
    Cof[0][0] =  (A[1][1]*A[2][2] - A[1][2]*A[2][1]);
    Cof[0][1] = -(A[1][0]*A[2][2] - A[1][2]*A[2][0]);
    Cof[0][2] =  (A[1][0]*A[2][1] - A[1][1]*A[2][0]);
    Cof[1][0] = -(A[0][1]*A[2][2] - A[0][2]*A[2][1]);
    Cof[1][1] =  (A[0][0]*A[2][2] - A[0][2]*A[2][0]);
    Cof[1][2] = -(A[0][0]*A[2][1] - A[0][1]*A[2][0]);
    Cof[2][0] =  (A[0][1]*A[1][2] - A[0][2]*A[1][1]);
    Cof[2][1] = -(A[0][0]*A[1][2] - A[0][2]*A[1][0]);
    Cof[2][2] =  (A[0][0]*A[1][1] - A[0][1]*A[1][0]);

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result[i][j] = Cof[j][i] / det;
}

*/