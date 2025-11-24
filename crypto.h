#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <string>
#include <fstream>
#include "LA.h"
#include "io.h"

using namespace std;

class CryptoSystem {
private:
    int A[3][3];
    int size;

public:
    CryptoSystem();
    void createOrLoadMatrix();
    void encode();
    void decode();
};

#endif