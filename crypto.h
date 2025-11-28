

//
//
// Author:  Haytham Ashraf

#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include "LA.h"

namespace Crypto {

    /*
        Encode a message using matrix A.

        Parameters:
            A: The encoding matrix.
            M: The message to be encoded.

        Return Value is the encoded matrix.
    */
    Matrix Encode(Matrix& A, Matrix& M);

    /*
        Decode a message using matrix A.

        Parameters:
            A: The encoding matrix.
            M: The message to be decoded.

        Return Value is the decoded matrix.
    */
    Matrix Decode(Matrix& A, Matrix& M);
};


#endif // _CRYPTO_H_