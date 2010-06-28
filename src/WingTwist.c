#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "decl.h"
#include "type.h"

void WingTwist(MESH *mesh, TWIST *twist){

    UINT i,j;
    REAL r1[3],r2[3];
    REAL *a, *center, *point1;
    REAL d2,d,s,t,theta;

    center = rvector(3);
    point1 = rvector(3);
    a      = rvector(3);

    // We assume twist->x1 lies on symmetry plane
    // Distance of twist->x2 from symmetry plane
    d2 = distToPlane(twist->n, twist->x1, twist->x2);

    for(i=0;i<mesh->np;i++){
        a[0]=mesh->x[i];
        a[1]=mesh->y[i];
        a[2]=mesh->z[i];

        // find distance of point to symmetry plane
        d = distToPlane(twist->n, twist->x1, a);
        s = d/d2;

        if(d <= d2){
     
        //point of intersection on the line of centers    
        for(j=0;j<=2;j++){
            r1[j] = twist->n[j]*(a[j]-twist->x1[j]);
            r2[j] = twist->n[j]*(twist->x2[j]-twist->x1[j]);
        }
        t = (r1[0]+r1[1]+r1[2])/(r2[0]+r2[1]+r2[2]);

        assert(t <= 1.0);

        // center of rotation
        for(j=0;j<=2;j++)
           center[j] = twist->x1[j] + t*(twist->x2[j]-twist->x1[j]);
        }

        else{

           // center of rotation
           for(j=0;j<=2;j++)
              center[j] = twist->x2[j] + twist->n[j]*(d2 - d);

        }

        theta = twist->theta0 * (1.0 - s) + twist->theta1 * s;
        point1 = RotAxis(center,twist->n,a,theta);

        //Final position of the rotated mesh point
        mesh->x[i] = point1[0];
        mesh->y[i] = point1[1];
        mesh->z[i] = point1[2];
             
    }

   free(a);
   free(center);
   free(point1);
}
