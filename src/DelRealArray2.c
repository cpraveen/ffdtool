#include <stdlib.h>
#include "type.h"
#include "decl.h"

void DelRealArray2(UINT nx, REAL **x){
   UINT i;

   for(i=0; i<nx; i++){
      free(x[i]);
   }
   free(x);
}
