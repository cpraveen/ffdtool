#include <stdlib.h>
#include "type.h"
#include "decl.h"

REAL** RealArray2(UINT nx, UINT ny){
   REAL **x;
   UINT i;

   x = (REAL**)malloc(nx*sizeof(REAL*));
   for(i=0; i<nx; i++){
      x[i] = (REAL*)malloc(ny*sizeof(REAL));
   }

   return x;
}
