/* Finds min/max range of FFD coordinates */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"

void MinMaxRangeFFD(FFD_BOX *box){
   UINT i, j, k;

   box->xmin = box->ymin = box->zmin = +1.0e20;
   box->xmax = box->ymax = box->zmax = -1.0e20;

   for(k=0; k<=box->kdim; k++)
      for(j=0; j<=box->jdim; j++)
         for(i=0; i<=box->idim; i++){
            box->xmin = min(box->xmin, box->x[i][j][k]);
            box->ymin = min(box->ymin, box->y[i][j][k]);
            box->zmin = min(box->zmin, box->z[i][j][k]);

            box->xmax = max(box->xmax, box->x[i][j][k]);
            box->ymax = max(box->ymax, box->y[i][j][k]);
            box->zmax = max(box->zmax, box->z[i][j][k]);
         }
}
