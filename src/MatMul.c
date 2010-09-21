// Matrix Multiplication
// result = matrix*vector

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "decl.h"


REAL* MatMul(REAL *vector, REAL **matrix, UINT nrow, UINT ncol){
    
    REAL *result;
    UINT k, l;

    result = rvector(nrow);

    for(k=0; k<nrow; k++){
        result[k] = 0.0;
        for(l=0; l<ncol; l++)
           result[k] += matrix[k][l]*vector[l];
    }

    return result;
}
    
