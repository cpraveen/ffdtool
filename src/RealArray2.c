#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "type.h"
#include "decl.h"

REAL** RealArray2(UINT nx, UINT ny){
   REAL **x;
   UINT i;

   assert(nx > 0 && ny > 0);

   x = (REAL**)malloc(nx*sizeof(REAL*));
   if(x==NULL){
      printf("RealArray2: Could not allocate x\n");
      exit(0);
   }
   for(i=0; i<nx; i++){
      x[i] = (REAL*)malloc(ny*sizeof(REAL));
      if(x[i]==NULL){
         printf("RealArray2: Could not allocate x[%d]\n",i);
         exit(0);
      }
   }

   return x;
}
