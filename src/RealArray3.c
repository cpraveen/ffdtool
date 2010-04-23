#include <stdlib.h>
#include "type.h"

REAL*** RealArray3(UINT nx, UINT ny, UINT nz){
   REAL ***x;
   UINT i, j;

   x = (REAL***)malloc(nx*sizeof(REAL**));
   for(i=0; i<nx; i++){
      x[i] = (REAL**)malloc(ny*sizeof(REAL*));
      for(j=0; j<ny; j++)
         x[i][j] = (REAL*)malloc(nz*sizeof(REAL));
   }

   return x;
}
