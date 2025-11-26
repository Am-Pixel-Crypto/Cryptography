#ifndef LA_H
#define LA_H

bool isInvertible(int A[3][3], int m);
void inverse2x2(int A[3][3], double result[3][3]);
void inverse3x3(int A[3][3], double result[3][3]);
void saveEncodingMatrix(int A[3][3], int size);
int savedMatrix();
bool loadMatrix(int choice, int A[3][3], int &size);

#endif