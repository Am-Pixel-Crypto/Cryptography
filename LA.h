



// Linear Algebra equations and math.

#ifndef _LA_H_
#define _LA_H_


class Matrix {
private:
    // size of the matrix
    int rows, cols;
    double **m;

    void init(int rows, int cols);
    double* operator*(int index);
public:
    Matrix();
    Matrix(Matrix& m);
    Matrix(int rows, int cols);
    Matrix(int size);

    // Math operations
    double determinant();
    bool isInvertible();
    Matrix inverse();
    Matrix operator*(const Matrix& m);
    Matrix& operator*(double scaler);
};

#endif // _LA_H_