//Rotation of a point about an arbitrary axis

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "type.h"
#include "decl.h"


REAL* RotAxis(REAL *center_rot,REAL *axis_rot,REAL* p1,REAL theta){
    UINT i,j, k=3;
    REAL p[3],*Final_point;
    REAL *p_new;
    REAL **Rx, **Rx_inv, **Ry, **Ry_inv, **Rz;
    REAL *Rot_x, *Rot_y, *Rot_y_inv, *Rot;
    REAL sum, sum1, cos_alpha, sin_alpha, cos_beta, sin_beta;
    REAL cos_theta, sin_theta, d, e;        

    Rx = RealArray2(k,k);
    Rx_inv = RealArray2(k,k);
    Ry = RealArray2(k,k);
    Ry_inv = RealArray2(k,k);
    Rz = RealArray2(k,k);
    Rot_x = rvector(k);
    Rot_y = rvector(k);
    Rot_y_inv = rvector(k);
    Rot = rvector(k);
    p_new= rvector(k);
    Final_point = rvector(3);
    
    // Initializing all the pointers as Identity Matrices   
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(j==i){
                Rx[i][j] = 1;
                Rx_inv[i][j] = 1;
                Ry[i][j] = 1;
                Ry_inv[i][j] = 1;
                Rz[i][j] = 1;
            }
            else{
                Rx[i][j] = 0;
                Rx_inv[i][j] = 0;
                Ry[i][j] = 0;
                Ry_inv[i][j] = 0;
                Rz[i][j] = 0;
            }
        } 
    }
   
    // Translating center of rotation to origin.
    for(i=0;i<=2;i++){
            p[i] = p1[i] - center_rot[i];
    }
    
    //Rotation of space about x axis
    sum = pow(axis_rot[1],2)+pow(axis_rot[2],2);
    d = sqrt(sum);

    if(d < 1.0e-10){ 
    //Axis of rotation lies on x axis.
        cos_alpha = 1.;
        sin_alpha = 0.;
    }else{
    //cos_alpha = (dot((0,0,axis[2]),(0,axis[1],axis[2]),3))/(axis[2]*d);
    cos_alpha = axis_rot[2]/d;
    //sin_alpha = (cross((0,0,axis[2]),(0,axis[1],axis[2]),3))/(axis[2]*d);
    sin_alpha = axis_rot[1]/d;
    }

    for(i=1;i<=2;i++){
        for(j=1;j<=2;j++){
            if(j==i){
                Rx[i][j] = cos_alpha;
                Rx_inv[i][j] = cos_alpha;
            }
            else if(j>i){
                Rx[i][j] = (-1)*sin_alpha;
                Rx_inv[i][j] = sin_alpha;
            }
            else{ 
                Rx[i][j] = sin_alpha;
                Rx_inv[i][j] = (-1)*sin_alpha;
            }
        }
    }
    
    //Rotation of space about y axis

    sum1 = pow(axis_rot[0],2)+pow(d,2);
    e = sqrt(sum1);
    cos_beta = d/e;
    sin_beta = axis_rot[0]/e;

    for(i=0;i<=2;i++){
        for(j=0;j<=2;j++){
            if(j!=1 && i!=1){
                if(j==i){
                    Ry[i][j] = cos_beta;
                    Ry_inv[i][j] = cos_beta;
                }
                else if(j>i){
                    Ry[i][j] = (-1)*sin_beta;
                    Ry_inv[i][j] = sin_beta;
                }
                else{ 
                    Ry[i][j] = sin_beta;
                    Ry_inv[i][j] = (-1)*sin_beta;
                }
            }
        }
    
    }
    //Rotation of space about z axis
    
    cos_theta = cos(theta);
    sin_theta = sin(theta);

    for(i=0;i<=1;i++){
        for(j=0;j<=1;j++){
            if(j==i){
                Rz[i][j] = cos_theta;
            }
            else if(j>i){
                Rz[i][j] = (-1)*sin_theta;
            }
            else{ 
                Rz[i][j] = sin_theta;
            }
        }
    }
    
    // Matrix Multiplication to obtain the rotated point
    Rot_x = MatMul(p,Rx,3,3);
    Rot_y = MatMul(Rot_x,Ry,3,3);
    Rot   = MatMul(Rot_y,Rz,3,3);
    Rot_y_inv = MatMul(Rot,Ry_inv,3,3);
    p_new = MatMul(Rot_y_inv,Rx_inv,3,3);
  
    
  
    for(i=0;i<=2;i++){
        Final_point[i] = p_new[i] + center_rot[i];
    }
  
    free(Rx);
    free(Rx_inv);
    free(Ry);
    free(Ry_inv);
    free(Rz);
    free(Rot_x);
    free(Rot_y);
    free(Rot_y_inv);
    free(Rot);
    free(p_new);
    
    return Final_point;
}
