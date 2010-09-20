#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "decl.h"

UINT* IntegerArray(UINT nx){
   UINT *x;

   x = (UINT*)malloc(nx*sizeof(UINT));
   if(x==NULL){
      printf("IntegerArray: could not allocate integer array\n");
      exit(0);
   }
   return x;
}
