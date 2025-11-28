

//
//
// Author:  Mahmoud Mostafa


#include <iostream>
#include "crypto.h"
using namespace std;

int main() {

    bool shouldExit = false;
    int option;

    while (!shouldExit) {
        cout << "==== Matrix Encoder/Decoder ====\n"
             << "1. Encode message\n"
             << "2. Decode message\n"
             << "3. Show History\n"
             << "4. Exit\n"
             << "Choose: ";
        cin >> option;
        cin.ignore();

        switch(option) {
            case 1:
            {
                // TBD ...
            } break;

            case 2:
            {
                // TBD ...
            } break;

            case 3:
            {
                // TBD ...
            } break;

            case 4:
            {
                // exit the mainloop
                shouldExit = true;
            } break;

            default:
            {
                cout << "Invalid choice!\n";
            }
        }
    }

    return 0;
}