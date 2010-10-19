#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "decl.h"
#include "type.h"

void WingTwist(MESH *mesh, TWIST *twist){

    UINT i, j;
    UINT isec;
    REAL r1[3], r2[3];
    REAL *a, *center, *point1;
    REAL d, s, t, theta;
    REAL *d_x_sym;

   printf("Applying twist deformation ...\n");

    center = rvector(3);
    point1 = rvector(3);
    a      = rvector(3);
    d_x_sym= rvector(twist->num_sect+1);

    // We assume twist->x[0] lies on symmetry plane
    // Distance of twist->x[i] to symmetry plane
    for(i=0; i<twist->num_sect+1; i++)
      d_x_sym[i] = distToPlane(twist->n, twist->x[0], twist->x[i]);

    // Loop over mesh points
    for(i=0;i<mesh->np;i++){
        a[0]=mesh->x[i];
        a[1]=mesh->y[i];
        a[2]=mesh->z[i];

        // find distance of point "a" to symmetry plane
        d = distToPlane(twist->n, twist->x[0], a);

        // find section in which this point lies
        isec = -1;
        for(j=0; j<twist->num_sect; j++)
           if(d >= d_x_sym[j] && d < d_x_sym[j+1])
              isec = j;


        if(isec >= 0){
     
            //point of intersection on the line of centers    
            for(j=0; j<=2; j++){
               r1[j] = twist->n[j] * (a[j] - twist->x[isec][j]);
               r2[j] = twist->n[j] * (twist->x[isec+1][j] - twist->x[isec][j]);
            }
            t = (r1[0] + r1[1] + r1[2]) / (r2[0] + r2[1] + r2[2]);

            assert(t <= 1.0);

            // center of rotation
            for(j=0; j<=2; j++)
               center[j] = twist->x[isec][j] + 
                           t * (twist->x[isec+1][j] - twist->x[isec][j]);

            s     = d/d_x_sym[twist->num_sect];
         }
         else{

           // point "a" is beyond last section
           // find center by moving along axis of rotation
           // center of rotation
           for(j=0; j<=2; j++)
              center[j] = twist->x[twist->num_sect][j] + 
                          twist->n[j]*(d - d_x_sym[twist->num_sect]);
           s = 1.0;

         }

        theta = twist->theta[0] * (1.0 - s) + twist->theta[1] * s;
        point1 = RotAxis(center, twist->n, a, theta);

        //Final position of the rotated mesh point
        mesh->x[i] = point1[0];
        mesh->y[i] = point1[1];
        mesh->z[i] = point1[2];
             
    }

   free(a);
   free(center);
   free(point1);
   free(d_x_sym);
}
