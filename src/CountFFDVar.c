/* Count number of FFD variables which have non-zero variation */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"

void CountFFDVar(FFD *ffd){
   UINT nvar=0, i, j, k;

   for(k=0; k<=ffd->var.nk; k++)
      for(j=0; j<=ffd->var.nj; j++)
         for(i=0; i<=ffd->var.ni; i++){
             if(ffd->var.Xmax[i][j][k] - ffd->var.Xmin[i][j][k] > FFDTOL ||
                ffd->var.Ymax[i][j][k] - ffd->var.Ymin[i][j][k] > FFDTOL ||
                ffd->var.Zmax[i][j][k] - ffd->var.Zmin[i][j][k] > FFDTOL)
                  ++nvar;
         }
   printf("Number of FFD variables = %d\n", nvar);
   if(nvar==0){
      printf("ERROR: All FFD variables are fixed\n");
      exit(0);
   }
   ffd->nvar = nvar;
}
