

//
//
// Author: Mahmoud Mostafa


// the file name of witch all encoded matrices are saved
#define OUTPUT_FILE_NAME ((const char*)"encoding_matrix.txt")


#include <iostream>
#include <iomanip>
#include <fstream>
#include "io.h"


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

void saveEncodingMatrix(int A[3][3], int size){
    fstream file(OUTPUT_FILE_NAME, ios::app);

    if(file.is_open()) {
        file << "Matrix (" << size << "x" << size << ")\n";
        for (int r = 0; r < size; r++){
            for (int c = 0; c < size; c++)
                file << A[r][c] << " ";
            file << endl;
        }
        file << "-----------------------------\n";
        file.close();
    } else {
        cout << "Error: failed to open \"" << OUTPUT_FILE_NAME << "\"" << endl;
    }
}

int savedMatrix() {
    ifstream file(OUTPUT_FILE_NAME);
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