/* Check the orientation of the indices of ffd box. They must form a right 
 * handed system. Otherwise, the test to check if point is inside/outside
 * the box will fail 
 */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"

void CheckFFDBox(FFD_BOX *box){
   REAL dx[3], dy[3], dz[3], vol;

   dx[0] = box->x[1][0][0] - box->x[0][0][0];
   dx[1] = box->x[0][1][0] - box->x[0][0][0];
   dx[2] = box->x[0][0][1] - box->x[0][0][0];

   dy[0] = box->y[1][0][0] - box->y[0][0][0];
   dy[1] = box->y[0][1][0] - box->y[0][0][0];
   dy[2] = box->y[0][0][1] - box->y[0][0][0];

   dz[0] = box->z[1][0][0] - box->z[0][0][0];
   dz[1] = box->z[0][1][0] - box->z[0][0][0];
   dz[2] = box->z[0][0][1] - box->z[0][0][0];

   vol   = dx[0] * ( dy[1] * dz[2] - dy[2] * dz[1] ) +
           dx[1] * ( dy[2] * dz[0] - dy[0] * dz[2] ) +
           dx[2] * ( dy[0] * dz[1] - dy[1] * dz[0] );

   if(vol <= 0.0){
      printf("********************************************************\n");
      printf("ERROR: FFD box indices are not correctly oriented\n");
      printf("********************************************************\n");
      exit(0);
   }
}
