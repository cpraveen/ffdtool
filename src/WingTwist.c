#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "decl.h"
#include "type.h"

void WingTwist(MESH *mesh, TWIST *twist){

    UINT i,j;
    REAL r[3],s[3];
    REAL *a, *point, *point1, disp[3];
    REAL t,t1,theta;
    REAL length;

    for(i=0;i<mesh->np;i++){
        point = rvector(3);
        point1 = rvector(3);
        a = rvector(3);
        a[0]=mesh->x[i];
        a[1]=mesh->y[i];
        a[2]=mesh->z[i];
     
        //point of intersection on the line of centers    
        for(j=0;j<=2;j++){
            r[j] = twist->n[j]*(a[j]-twist->x1[j]);
            s[j] = twist->n[j]*(twist->x2[j]-twist->x1[j]);
        }
        t = (r[0]+r[1]+r[2])/(s[0]+s[1]+s[2]);

        // point of intersection on the axis of rotation
        for(j=0;j<=2;j++){
            r[j] = twist->n[j]*(a[j]-twist->x1[j]);
            s[j] = twist->n[j]*twist->n[j]*twist->wing_len;
        }
        t1 = (r[0]+r[1]+r[2])/(s[0]+s[1]+s[2]);

        length = t1*twist->wing_len;

        // calculation of displacement after rotation using the cut off function        
        if(length<=twist->wing_len){
                for(j=0;j<=2;j++){
                    point[j]=twist->x1[j]+t*(twist->x2[j]-twist->x1[j]);
                }
                theta = twist->theta0+twist->theta1*t;
                point1 = RotAxis(point,twist->n,a,theta);

                for(j=0;j<=2;j++){
                    disp[j] = point1[j]-a[j];            
                }
                free(a);
                free(point);
                free(point1);
            }

        else if(length>twist->wing_len){
                for(j=0;j<=2;j++){
                    point[j]=twist->x2[j]+(t1-1)*twist->n[j]*(length-twist->wing_len);
                }
                theta = twist->theta0+twist->theta1*t1;
                point1 = RotAxis(point,twist->n,a,theta);

                for(j=0;j<=2;j++){
                    disp[j] = point1[j]-a[j];            
                }
                free(a);
                free(point);
                free(point1);
            }

        //Final position of the rotated mesh point
        mesh->x[i] += disp[0];
        mesh->y[i] += disp[1];
        mesh->z[i] += disp[2];
             
    }
}




        
        
