

#include "LA.h"


void Matrix::init(int rows, int cols) {

    if(m) {
        for(int i = 0; i < cols; i++) 
            delete[] this->m[i];
        delete[] this->m;
    }

    this->rows = rows;
    this->cols = cols;

    this->m = new double*[rows];
    for(int i = 0; i < cols; i++) 
        this->m[i] = new double[cols];
}

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->m = NULL;
}

Matrix::Matrix(Matrix& m) {
    m.rows = this->rows;
    m.cols = this->cols;

    m.m = new double*[this->rows];
    for(int i = 0; i < rows; i++) {

        m.m[i] = new double[this->cols];
        for(int k = 0; k < cols; k++)
            m[i][k] = this->m[i][k];
    }
}

Matrix::Matrix(int rows, int cols) {
    init(rows, cols);
}

Matrix::Matrix(int size) {
    init(size, size);
}

Matrix::~Matrix() {
    if(m) {
        for(int i = 0; i < cols; i++) 
            delete[] this->m[i];
        delete[] this->m;
    }
    this->rows = 0;
    this->rows = 0;
    this->m = NULL;
}

double* Matrix::operator*(int index) {
    return this->m[index];
}

double Matrix::determinant() {

    double det = 0;

    // we dont calculate determinant if it is not square.
    if( rows != cols ) 
        return 0;

    switch(rows) {
        // 1x1 matrix
        case 1: 
        {
            det = this->m[0][0];
        } break;

        // 2x2 matrix
        case 2:
        {
            det  = (this->m[0][0] * this->m[1][1]);
            det -= (this->m[0][1] * this->m[1][0]);
        } break;

        // 3x3 matrix
        case 3: 
        {
            det  = this->m[0][0] * (this->m[1][1] * this->m[2][2] - this->m[1][2] * this->m[2][1]);
            det -= this->m[0][1] * (this->m[1][0] * this->m[2][2] - this->m[1][2] * this->m[2][0]);
            det += this->m[0][2] * (this->m[1][0] * this->m[1][2] - this->m[1][1] * this->m[2][0]);
        } break;

        // 4x4 matrix
        /*case 4: {
            double _11, _12, _13, _14;
            _11 = _12 = _13 = _14 = 0;

            _11  = m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]);
            _11 -= m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]);
            _11 += m[1][3] * (m[2][1] * m[2][3] - m[2][2] * m[3][1]);
            _11 *= m[0][0];

            _12  = m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]);
            _12 -= m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]);
            _12 += m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
            _12 *= m[0][1];

            _13  = m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]);
            _13 -= m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]);
            _13 += m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
            _13 *= m[0][2];

            _14  = m[1][0] * (m[2][2] * m[3][2] - m[2][2] * m[3][1]);
            _14 -= m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]);
            _14 += m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]);
            _14 *= m[0][3];

            det = _11 - _12 + _13 - _14;
        } break;*/
        
        default: 
            det = 0;
    }

    return det;
}

bool Matrix::isInvertible() {
    return this->determinant() != 0;
}

Matrix Matrix::inverse() {

    Matrix result;

    if(this->determinant() == 0 || (rows != cols)) {
        // cant find inverst for this
        return result;
    }

    switch(rows) {
        case 2:
        {
            double det = this->determinant();

            result.init(2, 2);
            result[0][0] =  this->m[1][1] / det;
            result[0][1] = -this->m[0][1] / det;
            result[1][0] = -this->m[1][0] / det;
            result[1][1] =  this->m[0][0] / det;
        } break;
        
        case 3:
        {
            double det = this->determinant();
            
            //A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1]) -
            //A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0]) +
            //A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);

            Matrix Cof(3);
            Cof[0][0] =  (this->m[1][1]*this->m[2][2] - this->m[1][2]*this->m[2][1]);
            Cof[0][1] = -(this->m[1][0]*this->m[2][2] - this->m[1][2]*this->m[2][0]);
            Cof[0][2] =  (this->m[1][0]*this->m[2][1] - this->m[1][1]*this->m[2][0]);
            Cof[1][0] = -(this->m[0][1]*this->m[2][2] - this->m[0][2]*this->m[2][1]);
            Cof[1][1] =  (this->m[0][0]*this->m[2][2] - this->m[0][2]*this->m[2][0]);
            Cof[1][2] = -(this->m[0][0]*this->m[2][1] - this->m[0][1]*this->m[2][0]);
            Cof[2][0] =  (this->m[0][1]*this->m[1][2] - this->m[0][2]*this->m[1][1]);
            Cof[2][1] = -(this->m[0][0]*this->m[1][2] - this->m[0][2]*this->m[1][0]);
            Cof[2][2] =  (this->m[0][0]*this->m[1][1] - this->m[0][1]*this->m[1][0]);
            
            result.init(3, 3);
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    result[i][j] = Cof[j][i] / det;
        } break;
    }

    return result;    
}

Matrix Matrix::operator*(const Matrix& m) {

    Matrix result;

    if(rows != m.cols) {
        // operation is not permitted
        return result;
    }

    result.init(rows, m.cols);

    int row, col;
    for(row = 0; row < rows; row++) {

        double val = 0;
        for(col = 0; col < cols; col++)
            val += this->m[col][row] * m[row][col];
        result[row][col] = val;
    }

    return result;
}

void Matrix::operator*(double scaler) {
    for(int i = 0; i < m.rows; i++) 
        for(int k = 0; k < m.cols; k++)
            m[i][k] *= scaler;
}