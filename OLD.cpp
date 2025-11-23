

Matrix2 inverse2x2(int A[3][3]) {
    Matrix2 result;
    double det = (A[0][0] * A[1][1]) - (A[0][1] * A[1][0]);
    result.m[0][0] =  A[1][1] / det;
    result.m[0][1] = -A[0][1] / det;
    result.m[1][0] = -A[1][0] / det;
    result.m[1][1] =  A[0][0] / det;
    return result;
}

Matrix3 inverse3x3(int A[3][3]) {
    Matrix3 result;
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
            result.m[i][j] = Cof[j][i] / det;

    return result;
}

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
