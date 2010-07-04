/* Count number of FFD variables which have non-zero variation */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ffd.h"
#include "decl.h"

void PrintVars(FFD *ffd, TWIST *twist){
   UINT nvar=0, i, j, k;

   for(k=0; k<=ffd->var.nk; k++)
      for(j=0; j<=ffd->var.nj; j++)
         for(i=0; i<=ffd->var.ni; i++){

            if(ffd->var.Xmax[i][j][k] - ffd->var.Xmin[i][j][k] > FFDTOL){
               printf("x%d   %e   %e   %e\n", nvar, ffd->var.Xmin[i][j][k],
                      ffd->var.Xmax[i][j][k], 0.0);
               ++nvar;
            }

            if(ffd->var.Ymax[i][j][k] - ffd->var.Ymin[i][j][k] > FFDTOL){
               printf("x%d   %e   %e   %e\n", nvar, ffd->var.Ymin[i][j][k],
                      ffd->var.Ymax[i][j][k], 0.0);
               ++nvar;
            }

            if(ffd->var.Zmax[i][j][k] - ffd->var.Zmin[i][j][k] > FFDTOL){
               printf("x%d   %e   %e   %e\n", nvar, ffd->var.Zmin[i][j][k],
                      ffd->var.Zmax[i][j][k], 0.0);
               ++nvar;
            }
         }

   if(strcmp(twist->exist,"yes")==0){
      printf("theta0  %e   %e   %e\n", 0.0, 0.0, 0.0);
      printf("theta1  %e   %e   %e\n", 0.0, 0.0, 0.0);
   }
}
