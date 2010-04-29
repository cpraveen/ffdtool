/* Jacobian of rootFun required for Newton-Raphson method */
#include "type.h"
#include "decl.h"

REAL DFDXI  (REAL xi, REAL eta, REAL zeta, REAL *a);
REAL DFDETA (REAL xi, REAL eta, REAL zeta, REAL *a);
REAL DFDZETA(REAL xi, REAL eta, REAL zeta, REAL *a);

void rootFunJac(REAL *x, REAL *y, REAL *z, REAL *t, REAL **jac){
   REAL xi, eta, zeta;

   xi   = t[0];
   eta  = t[1];
   zeta = t[2];

   jac[0][0] = DFDXI  (xi, eta, zeta, x);
   jac[0][1] = DFDETA (xi, eta, zeta, x);
   jac[0][2] = DFDZETA(xi, eta, zeta, x);

   jac[1][0] = DFDXI  (xi, eta, zeta, y);
   jac[1][1] = DFDETA (xi, eta, zeta, y);
   jac[1][2] = DFDZETA(xi, eta, zeta, y);

   jac[2][0] = DFDXI  (xi, eta, zeta, z);
   jac[2][1] = DFDETA (xi, eta, zeta, z);
   jac[2][2] = DFDZETA(xi, eta, zeta, z);


}

// d(rootFun)/d(xi)
REAL DFDXI(REAL xi, REAL eta, REAL zeta, REAL *a){

   return      - (1.0-eta) * (1.0-zeta) * a[0]
               + (1.0-eta) * (1.0-zeta) * a[1]
               - eta       * (1.0-zeta) * a[2]
               + eta       * (1.0-zeta) * a[3]
               - (1.0-eta) * zeta       * a[4]
               + (1.0-eta) * zeta       * a[5]
               - eta       * zeta       * a[6]
               + eta       * zeta       * a[7];
}

// d(rootFun)/d(eta)
REAL DFDETA(REAL xi, REAL eta, REAL zeta, REAL *a){

   return      - (1.0-xi) * (1.0-zeta) * a[0]
               - xi       * (1.0-zeta) * a[1]
               + (1.0-xi) * (1.0-zeta) * a[2]
               + xi       * (1.0-zeta) * a[3]
               - (1.0-xi) * zeta       * a[4]
               - xi       * zeta       * a[5]
               + (1.0-xi) * zeta       * a[6]
               + xi       * zeta       * a[7];
}

// d(rootFun)/d(zeta)
REAL DFDZETA(REAL xi, REAL eta, REAL zeta, REAL *a){

   return      - (1.0-xi) * (1.0-eta) * a[0]
               - xi       * (1.0-eta) * a[1]
               - (1.0-xi) * eta       * a[2]
               - xi       * eta       * a[3]
               + (1.0-xi) * (1.0-eta) * a[4]
               + xi       * (1.0-eta) * a[5]
               + (1.0-xi) * eta       * a[6]
               + xi       * eta       * a[7];
}
