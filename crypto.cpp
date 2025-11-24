#include "crypto.h"
#include "LA.h"
#include "io.h"
#include <iostream>

using namespace std;

CryptoSystem::CryptoSystem() {
    size = 0;
}
void CryptoSystem::createOrLoadMatrix() {
    int option;
    cout << "\n1.Create a matrix\n2.Use old matrix\nEnter an option: ";
    cin >> option;

    if (option == 1) {
        while (true) {
            cout << "\n1. 2x2\n2. 3x3\nEnter size: ";
            cin >> size;
            if (size == 1 || size == 2) { size++; break; }
            cout << "Invalid choice.\n";
        }

        while (true) {
            cout << "\nEnter matrix row by row:\n";
            for (int r = 0; r < size; r++)
                for (int c = 0; c < size; c++)
                    cin >> A[r][c];

            if (!isInvertible(A, size))
                cout << "ERROR: Matrix is NOT invertible!\n";
            else
                break;
        }
        saveEncodingMatrix(A, size);
    }
    else if (option == 2) {
        savedMatrix();
        int choice;
        cout << "Choose matrix number: ";
        cin >> choice;
        loadMatrix(choice, A, size);
    }
    cin.ignore();
}

void CryptoSystem::encode() {
    createOrLoadMatrix();

    string msg;
    cout << "\nEnter the message you want to encode: ";
    getline(cin, msg);

    int L = msg.length();
    int num[L];

    for (int i = 0; i < L; i++) {
        if      (msg[i] == ' ') num[i] = 0;
        else if (msg[i] >= 'A' && msg[i] <= 'Z') num[i] = msg[i] - 'A' + 1;
        else if (msg[i] >= 'a' && msg[i] <= 'z') num[i] = msg[i] - 'a' + 27;
    }

    int cols = (L + size - 1) / size;
    int M[3][50] = {0}, idx = 0;

    for (int r = 0; r < size; r++)
        for (int c = 0; c < cols; c++)
            if (idx < L) M[r][c] = num[idx++];

    double B[3][50] = {0};
    for (int r = 0; r < size; r++)
        for (int c = 0; c < cols; c++)
            for (int k = 0; k < size; k++)
                B[r][c] += A[r][k] * M[k][c];

    printMatrix(B, size, cols, "Encoded Matrix (B)");
}

void CryptoSystem::decode() {
    createOrLoadMatrix();
    int cols;
    cout << "Enter number of columns: ";
    cin >> cols;

    double inv[3][3];
    (size == 2) ? inverse2x2(A, inv) : inverse3x3(A, inv);

    double B[3][50];
    cout << "\nEnter encoded matrix row by row:\n";
    for (int r = 0; r < size; r++)
        for (int c = 0; c < cols; c++)
            cin >> B[r][c];

    double M[3][50] = {0};
    for (int r = 0; r < size; r++)
        for (int c = 0; c < cols; c++)
            for (int k = 0; k < size; k++)
                M[r][c] += inv[r][k] * B[k][c];

    printMatrix(M, size, cols, "Decoded Matrix (M)");
    msgOut(M, size, cols);
}