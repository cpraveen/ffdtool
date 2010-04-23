#include<math.h>
#include<stdio.h>
#include "gauss.h"


/* ---------------------------------------------------------------------- */
void Gaussj(double **a, int n, double *b)
{
/* ---------------------------------------------------------------------- */

   int *indxc, *indxr, *ipiv;
   int i, icol=0, irow=0, j, k, l, ll;
   double big, dum, pivinv, temp;

   indxc = ivector(n);
   indxr = ivector(n);
   ipiv = ivector(n);
   for(j = 0; j < n; j++)
      ipiv[j] = 0;
   for(i = 0; i < n; i++) {
      big = 0.0;
      for(j = 0; j < n; j++)
         if(ipiv[j] != 1)
            for(k = 0; k < n; k++) {
               if(ipiv[k] == 0) {
                  if(fabs(a[j][k]) >= big) {
                     big = fabs(a[j][k]);
                     irow = j;
                     icol = k;
                  }
               }
               else if(ipiv[k] > 1) {
                  printf("gaussj: Singular matrix - 1\n");
                  exit(0);
               }
            }
      ++(ipiv[icol]);

      //if(irow != icol){
      // for(l=0;l<n;l++) SWAP(a[irow][l],a[icol][l]);
      // SWAP(b[irow],b[icol]);
      //}
      indxr[i] = irow;
      indxc[i] = icol;
      if(a[icol][icol] == 0.0) {
         printf("gaussj: Singular matrix - 2\n");
         printf("        Matrix size = %d\n", n);
         printf("        Diag location = %d\n", icol);
         exit(0);
      }
      pivinv = 1.0 / a[icol][icol];
      a[icol][icol] = 1.0;
      for(l = 0; l < n; l++)
         a[icol][l] *= pivinv;
      b[icol] *= pivinv;

      for(ll = 0; ll < n; ll++)
         if(ll != icol) {
            dum = a[ll][icol];
            a[ll][icol] = 0.0;
            for(l = 0; l < n; l++)
               a[ll][l] -= a[icol][l] * dum;
            b[ll] -= b[icol] * dum;
         }
   }

   for(l = n - 1; l >= 0; l--) {
      if(indxr[l] != indxc[l])
         for(k = 0; k < n; k++)
            SWAP(a[k][indxr[l]], a[k][indxc[l]]);
   }
   free(ipiv);
   free(indxr);
   free(indxc);
}

/* ---------------------------------------------------------------------- */
