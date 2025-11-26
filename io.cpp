#include <iostream>
#include <iomanip>
#include "io.h"

using namespace std;

void printMatrix(int M[3][50], int rows, int cols, string title) {
    cout << "\n" << title << ":\n";
    for (int r = 0; r < rows; r++) {
        cout << "{ ";
        for (int c = 0; c < cols; c++) {
            cout << setw(6) << fixed << setprecision(2) << M[r][c] << " ";
        }
        cout << "}\n";
    }
}
void msgOut(int M[3][50], int rows, int cols){
    cout << "\nDecoded message: ";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int val = int(M[r][c] + 0.5);
            if (val == 0)
                cout << " ";
            else if (val >= 1 && val <= 26)
                cout << char(val + 64);
            else if (val >= 27 && val <= 52)
                cout << char(val - 26 + 96);
        }
    }
}