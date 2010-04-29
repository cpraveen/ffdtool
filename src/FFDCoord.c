/* For a given point, find its FFD coordinates */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "type.h"
#include "ffd.h"
#include "decl.h"

#define RESTOL 1.0e-14

void FFDCoord(REAL xp, REAL yp, REAL zp, FFD_BOX *box, UINT i, UINT j, UINT k,
              REAL *t){
   REAL x[8], y[8], z[8];
   UINT iter, maxiter=100;
   REAL res, fun[3], **jac;

   void newton(REAL*, REAL**, REAL*);

   jac = RealArray2(3,3);

   x[0] = box->x[i][j][k];
   x[1] = box->x[i+1][j][k];
   x[2] = box->x[i][j+1][k];
   x[3] = box->x[i+1][j+1][k];
   x[4] = box->x[i][j][k+1];
   x[5] = box->x[i+1][j][k+1];
   x[6] = box->x[i][j+1][k+1];
   x[7] = box->x[i+1][j+1][k+1];

   y[0] = box->y[i][j][k];
   y[1] = box->y[i+1][j][k];
   y[2] = box->y[i][j+1][k];
   y[3] = box->y[i+1][j+1][k];
   y[4] = box->y[i][j][k+1];
   y[5] = box->y[i+1][j][k+1];
   y[6] = box->y[i][j+1][k+1];
   y[7] = box->y[i+1][j+1][k+1];

   z[0] = box->z[i][j][k];
   z[1] = box->z[i+1][j][k];
   z[2] = box->z[i][j+1][k];
   z[3] = box->z[i+1][j+1][k];
   z[4] = box->z[i][j][k+1];
   z[5] = box->z[i+1][j][k+1];
   z[6] = box->z[i][j+1][k+1];
   z[7] = box->z[i+1][j+1][k+1];

   //initial guess
   t[0] = t[1] = t[2] = 0.5;

   iter = 0;
   res  = 1.0;
   while(res > RESTOL && iter <= maxiter){//TODO: Conv criterion is good ???
      rootFun(xp, yp, zp, x, y, z, t, fun);
      res = sqrt(fun[0]*fun[0] + fun[1]*fun[1] + fun[2]*fun[2]);
      rootFunJac(x, y, z, t, jac);
      newton(fun, jac, t);
      iter++;
   }

   // check convergence
   if(res > RESTOL){
      printf("FFDCoord: Failed to converge :-(\n");
      exit(0);
   }

   assert(t[0] >= 0.0);
   assert(t[1] >= 0.0);
   assert(t[2] >= 0.0);

   // free memory
   DelRealArray2(3, jac);

}

/* One step of newton */
void newton(REAL *f, REAL **jac, REAL *t){
   UINT i;

   Gaussj(jac, 3, f);
   for(i=0; i<3; i++) t[i] = t[i] - f[i];
   
}
