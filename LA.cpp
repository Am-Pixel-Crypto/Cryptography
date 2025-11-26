#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LA.h"
using namespace std;

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

void saveEncodingMatrix(int A[3][3], int size){
    fstream file("encoding_matrix.txt", ios::app);
    file << "Matrix (" << size << "x" << size << ")\n";
    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++)
            file << A[r][c] << " ";
        file << endl;
    }
    file << "-----------------------------\n";
    file.close();
}
int savedMatrix() {
    ifstream file("encoding_matrix.txt");
    string line;
    int matrixCount = 0;
    int size = 0;

    cout << "\n===== Saved Matrices =====\n";
    while (getline(file, line)) {
        if (line.find("Matrix (") == 0) {
            matrixCount++;
            cout << "\nMatrix #" << matrixCount << "  " << line << "\n";
            if (line.find("2x2") != string::npos) size = 2;
            if (line.find("3x3") != string::npos) size = 3;

            for (int r = 0; r < size; r++) {
                if (getline(file, line))
                    cout << "{ " << line << "}\n";
            }
            cout << "-----------------------------\n";
        }
    }
    return matrixCount;
}
bool loadMatrix(int choice, int A[3][3], int &size) {
    ifstream file("encoding_matrix.txt");
    string line;
    int current = 0;
    while (getline(file, line)) {
        if (line.find("Matrix (") == 0) {
            current++;
            if (current == choice) {
                if (line.find("2x2") != string::npos)
                    size = 2;
                else if (line.find("3x3") != string::npos)
                    size = 3;
                for (int r = 0; r < size; r++) {
                    getline(file, line);
                    stringstream ss(line);
                    for (int c = 0; c < size; c++) {
                        ss >> A[r][c];
                    }
                }
                return true;
            }
        }
    }
    return false;
}