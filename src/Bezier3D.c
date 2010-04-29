/* Compute node movement using Bezier volume */
#include <assert.h>
#include "ffd.h"
#include "decl.h"

void Bezier3D(SHAPE_PARAM *var, REAL *t, REAL *dr){
   UINT i, j, k;
   REAL coeffx[100];
   REAL coeffy[100];
   REAL coeffz[100];
   REAL varij[100][100][3];
   REAL vari[100][3];

   /* Check array sizes */
   assert(var->ni < 100);
   assert(var->nj < 100);
   assert(var->nk < 100);

   /* First do the innermost loop: k loop */
   for(i=0; i<=var->ni; i++)
      for(j=0; j<=var->nj; j++){

         for(k=0; k<=var->nk; k++){
            coeffx[k] = var->X[i][j][k];
            coeffy[k] = var->Y[i][j][k];
            coeffz[k] = var->Z[i][j][k];
         }

         varij[i][j][0] = decas(var->nk, coeffx, t[2]);
         varij[i][j][1] = decas(var->nk, coeffy, t[2]);
         varij[i][j][2] = decas(var->nk, coeffz, t[2]);

      }

   /* Now do the j-loop */
   for(i=0; i<=var->ni; i++){

      for(j=0; j<=var->nj; j++){
         coeffx[j] = varij[i][j][0];
         coeffy[j] = varij[i][j][1];
         coeffz[j] = varij[i][j][2];
      }

      vari[i][0] = decas(var->nj, coeffx, t[1]);
      vari[i][1] = decas(var->nj, coeffy, t[1]);
      vari[i][2] = decas(var->nj, coeffz, t[1]);

   }

   /* Finally the i-loop */
   for(i=0; i<=var->ni; i++){
      coeffx[i] = vari[i][0];
      coeffy[i] = vari[i][1];
      coeffz[i] = vari[i][2];
   }

   dr[0] = decas(var->ni, coeffx, t[0]);
   dr[1] = decas(var->ni, coeffy, t[0]);
   dr[2] = decas(var->ni, coeffz, t[0]);

}
