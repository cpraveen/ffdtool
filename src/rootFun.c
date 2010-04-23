#include "type.h"
#include "decl.h"

void rootFun(REAL xp, REAL yp, REAL zp, REAL *x, REAL *y, REAL *z, 
             REAL *t, REAL *f){
   REAL xi, eta, zeta;

   xi   = t[0];
   eta  = t[1];
   zeta = t[2];

   f[0] = (1.0-xi) * (1.0-eta) * (1.0-zeta) * x[0] +
          xi       * (1.0-eta) * (1.0-zeta) * x[1] +
          (1.0-xi) * eta       * (1.0-zeta) * x[2] +
          xi       * eta       * (1.0-zeta) * x[3] +
          (1.0-xi) * (1.0-eta) * zeta       * x[4] +
          xi       * (1.0-eta) * zeta       * x[5] +
          (1.0-xi) * eta       * zeta       * x[6] +
          xi       * eta       * zeta       * x[7] -
          xp;

   f[1] = (1.0-xi) * (1.0-eta) * (1.0-zeta) * y[0] +
          xi       * (1.0-eta) * (1.0-zeta) * y[1] +
          (1.0-xi) * eta       * (1.0-zeta) * y[2] +
          xi       * eta       * (1.0-zeta) * y[3] +
          (1.0-xi) * (1.0-eta) * zeta       * y[4] +
          xi       * (1.0-eta) * zeta       * y[5] +
          (1.0-xi) * eta       * zeta       * y[6] +
          xi       * eta       * zeta       * y[7] -
          yp;

   f[2] = (1.0-xi) * (1.0-eta) * (1.0-zeta) * z[0] +
          xi       * (1.0-eta) * (1.0-zeta) * z[1] +
          (1.0-xi) * eta       * (1.0-zeta) * z[2] +
          xi       * eta       * (1.0-zeta) * z[3] +
          (1.0-xi) * (1.0-eta) * zeta       * z[4] +
          xi       * (1.0-eta) * zeta       * z[5] +
          (1.0-xi) * eta       * zeta       * z[6] +
          xi       * eta       * zeta       * z[7] -
          zp;

}
