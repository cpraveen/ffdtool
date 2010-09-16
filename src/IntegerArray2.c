#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "decl.h"

UINT** IntegerArray2(UINT nx, UINT ny){
   UINT **x;
   UINT i;

   x = (UINT**)malloc(nx*sizeof(UINT*));
   if(x==NULL){
      printf("IntegerArray2: could not allocate x\n");
      exit(0);
   }
   for(i=0; i<nx; i++){
      x[i] = (UINT*)malloc(ny*sizeof(UINT));
      if(x[i]==NULL){
         printf("IntegerArray2: could not allocate x[%d]\n",i);
         exit(0);
      }
   }

   return x;
}
