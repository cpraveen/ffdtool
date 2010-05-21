// Matrix Multiplication of a vector with a 4x4 matrix

#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "decl.h"


REAL* MatMul(REAL *vector1, REAL **vector2, UINT i, UINT j){
    
    REAL *multi;
    REAL sum;
    UINT k,l;
    multi = rvector(4);
    for(k=0;k<j;k++){
        sum=0;
        for(l=0;l<i;l++){
            sum += vector2[k][l]*vector1[l];
        }
        multi[k] = sum;
    }
    return multi;
}
    
