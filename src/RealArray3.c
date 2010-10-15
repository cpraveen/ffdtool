#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "type.h"

REAL*** RealArray3(UINT nx, UINT ny, UINT nz){
   REAL ***x;
   UINT i, j;

   assert(nx > 0 && ny > 0 && nz > 0);

   x = (REAL***)malloc(nx*sizeof(REAL**));
   if(x==NULL){
      printf("RealArray3: Could not allocate x\n");
      printf("            size %d x %d x %d\n", nx, ny, nz);
      exit(0);
   }
   for(i=0; i<nx; i++){
      x[i] = (REAL**)malloc(ny*sizeof(REAL*));
      if(x[i]==NULL){
         printf("RealArray3: Could not allocate x[%d]\n",i);
         printf("            size %d x %d x %d\n", nx, ny, nz);
         exit(0);
      }
      for(j=0; j<ny; j++){
         x[i][j] = (REAL*)malloc(nz*sizeof(REAL));
         if(x[i][j]==NULL){
            printf("RealArray3: Could not allocate x[%d][%d]\n",i,j);
            printf("            size %d x %d x %d\n", nx, ny, nz);
            exit(0);
         }
      }
   }

   return x;
}
