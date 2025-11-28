
//
//
// Author: Mahmoud Mostafa


#ifndef IO_H
#define IO_H
#include <string>

using namespace std;

void printMatrix(int M[3][50], int rows, int cols, string title);
void msgOut(int M[3][50], int rows, int cols);

void saveEncodingMatrix(int A[3][3], int size);
int  savedMatrix();
bool loadMatrix(int choice, int A[3][3], int &size);

#endif