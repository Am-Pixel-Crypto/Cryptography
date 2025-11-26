#include <iostream>
#include "crypto.h"
using namespace std;

int main() {
    CryptoSystem crypt;
    int option;

    while (true) {
        cout << "==== Matrix Encoder/Decoder ====\n"
             << "1. Encode message\n"
             << "2. Decode message\n"
             << "3. Show History\n"
             << "4. Exit\n"
             << "Choose: ";
        cin >> option;
        cin.ignore();

        if (option == 1) crypt.encode();
        else if (option == 2) crypt.decode();
        else if (option == 3) break;
        else cout << "Invalid choice!\n";
    }
}