#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


int main() {
    int x;
    string msg;

    while (true) {
        cout << "==== Matrix Encoder/Decoder ====\n";
        cout << "1. Encode a message\n";
        cout << "2. Decode a message\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> x;
        cin.ignore();

        if (x == 1) {
            encodeMessage();
        }   

        else if (x == 2) {
            decodeMessage();
        }

        else if (x == 3) {  
            break;
        }

        else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
