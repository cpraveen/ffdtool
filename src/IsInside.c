/* We assume that the four vertices of facet lie exactly on the same plane */
#include "type.h"
#include "ffd.h"
#include "decl.h"

UINT IsInside(REAL xp, REAL yp, REAL zp, FFD_BOX *box, 
              UINT *ix, UINT *iy, UINT *iz){
   UINT inside;
   UINT i, j, k, f;
   UINT p0, p1, p2;
   REAL x[8], y[8], z[8], dot, n1, n2, n3;

   //simple check for outside condition
   if(xp < box->xmin) return 0;
   if(xp > box->xmax) return 0;
   if(yp < box->ymin) return 0;
   if(yp > box->ymax) return 0;
   if(zp < box->zmin) return 0;
   if(zp > box->zmax) return 0;

   for(i=0; i<box->idim; i++)
      for(j=0; j<box->jdim; j++)
         for(k=0; k<box->kdim; k++){

            inside = 1;

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

            for(f=1; f<=6; f++){ // Six faces of each sub-box

               // Set dummy values
               p0 = p1 = p2 = -1;

               if(f==1){       //perp to i
                  p0 = 0; p1 = 2; p2 = 4;
               }else if(f==2){ //perp to i
                  p0 = 1; p1 = 5; p2 = 3;
               }else if(f==3){ //perp to j
                  p0 = 0; p1 = 4; p2 = 1;
               }else if(f==4){ //perp to j
                  p0 = 2; p1 = 3; p2 = 6;
               }else if(f==5){ //perp to k
                  p0 = 0; p1 = 1; p2 = 2;
               }else if(f==6){ //perp to k
                  p0 = 4; p1 = 6; p2 = 5;
               }

               // normal vector to face
               n1 = (y[p1] - y[p0]) * (z[p2] - z[p0]) -
                    (y[p2] - y[p0]) * (z[p1] - z[p0]);
               n2 = (z[p1] - z[p0]) * (x[p2] - x[p0]) -
                    (z[p2] - z[p0]) * (x[p1] - x[p0]);
               n3 = (x[p1] - x[p0]) * (y[p2] - y[p0]) -
                    (x[p2] - x[p0]) * (y[p1] - y[p0]);

               // if dot product is negative, then point is not inside
               dot = n1 * (xp - x[p0]) + n2 * (yp - y[p0]) + n3 * (zp - z[p0]);
               if(dot < 0.0) inside = 0;

            }

            if(inside){
               *ix = i; *iy = j; *iz = k;
               return 1;
            }

         }

   return 0;
}
