

#ifndef _CRYPYTO_H_
#define _CRYPYTO_H_


void encodeMessage() {

    string msg;
    int size, m;
    int A[3][3];

    while (true) {
        cout << "==== Encoding Matrix Size ====\n"
            << "1. 2x2\n"
            << "2. 3x3\n"
            << "Enter size: ";
        cin >> size;
        
        if (size == 1) {
            m = 2;
            break;
        }
        else if (size == 2) {
            m = 3;
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    while (true){
        cout << "\nEnter the encoding matrix A (row by row):\n";
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < m; c++) {
                cin >> A[r][c];
            }
        }
        if (!isInvertible(A, m)) {
            cout << "ERROR: This matrix is NOT invertible!"
            << "\nUse a different encoding matrix.\n";
        }
        else
            break;
    }

    cin.ignore();
    cout << "\nEnter the message you want to encode: ";
    getline(cin, msg);
    int L = msg.length();
    int num[L];
    for (size_t i = 0; i < msg.length(); i++) {
        if (msg[i] == ' ') {
            num[i] = 0;
        }
        else if (msg[i] >= 'A' && msg[i] <= 'Z') {
            num[i] = msg[i] - 'A' + 1;
        }
        else if (msg[i] >= 'a' && msg[i] <= 'z') {
            num[i] = msg[i] - 'a' + 27;
        }
    }

    /*
    for (int k = 0; k < input.length(); k++) {
        cout << num[k] << " ";
    }*/

    int cols = L / m;
    if (L % m != 0) cols++; 

    int M[3][50] = {0}; 
    int index = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < cols; c++) {
            if (index < L) 
                M[r][c] = num[index++];
        }
    }

    int B[3][50] = {0};
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < cols; c++) {
            for (int k = 0; k < m; k++) {
                B[r][c] += A[r][k] * M[k][c];
            }
        }
    }

    /*
    cout << "\nMessage matrix (M):\n";
    for (int r = 0; r < rows; r++) {
        cout << "{ ";                   
            for (int c = 0; c < cols; c++) {
                cout << setw(3) << M[r][c] << " ";
            }
            cout << "}\n";  
    }*/

    cout << "\nEncoded matrix (B):\n";
    for (int r = 0; r < m; r++) {
        cout << "{ ";
        for (int c = 0; c < cols; c++) {
            cout << setw(4) << B[r][c] << " ";
        }
        cout << "}\n";
    }
}

void decodeMessage() {

    int size, m;
    int A[3][3];

    while (true) {
        cout << "==== Encoding Matrix Size ====\n"
             << "1. 2x2\n"
             << "2. 3x3\n"
             << "Enter size: ";
        cin >> size;
        
        if (size == 1) {
            m = 2;
            break;
        }
        else if (size == 2) {
            m = 3;
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    while (true){
        cout << "\nEnter the encoding matrix A (row by row):\n";
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < m; c++) {
                cin >> A[r][c];
            }
        }
        if (!isInvertible(A, m)) {
            cout << "ERROR: This matrix is NOT invertible!"
            << "\nUse a different encoding matrix.\n";
        }
        else
            break;
    }

    int cols;

    cout << "Enter number of columns: ";
    cin >> cols;

    Matrix2 inv2;
    Matrix3 inv3;

    if (m == 2)
        inv2 = inverse2x2(A);
    else
        inv3 = inverse3x3(A);

    double B[3][50];
    cout << "\nEnter the encoded matrix row by row:\n";
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < cols; c++) {
            cin >> B[r][c];
        }
    }

    double M[3][50] = {0};
    if (m == 2) {
        for (int r = 0; r < 2; r++) {
            for (int c = 0; c < cols; c++) {
                for (int k = 0; k < 2; k++) {
                    M[r][c] += inv2.m[r][k] * B[k][c];
                }
            }
        }
    } else {
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < cols; c++) {
                for (int k = 0; k < 3; k++) {
                    M[r][c] += inv3.m[r][k] * B[k][c];
                }
            }
        }
    }

    cout << "\nDecoded matrix (M):\n";
    for (int r = 0; r < m; r++) {
        cout << "{ ";
        for (int c = 0; c < cols; c++) {
            cout << setw(6) << fixed << setprecision(2) << M[r][c] << " ";
        }
        cout << "}\n";
    }

    cout << "\nDecoded message: ";
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < cols; c++) {
            int val = int(M[r][c] + 0.5);
            if (val == 0)
                cout << "_";
            else if (val >= 1 && val <= 26)
                cout << char(val + 64);
            else if (val >= 27 && val <= 52)
                cout << char(val - 26 + 96);
        }
    }

    cout << "\n";
} 


#endif // _CRYPYTO_H_