//Rotation of a point about an arbitrary axis

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "type.h"
#include "decl.h"


REAL* RotAxis(REAL *center_rot,REAL *axis_rot,REAL* p1,REAL theta){
    UINT i,j, k=4;
    REAL **trans_mat, **trans_mat_inv;
    REAL p[4],*Final_point;
    REAL *p_new;
    REAL **Rx, **Rx_inv, **Ry, **Ry_inv, **Rz;
    REAL *Rot_x, *Rot_x_inv, *Rot_y, *Rot_y_inv, *Rot, *trans;
    REAL sum, sum1, cos_alpha, sin_alpha, cos_beta, sin_beta;
    REAL cos_theta, sin_theta, d, e;        

    trans_mat = RealArray2(k,k);
    trans_mat_inv = RealArray2(k,k);
    Rx = RealArray2(k,k);
    Rx_inv = RealArray2(k,k);
    Ry = RealArray2(k,k);
    Ry_inv = RealArray2(k,k);
    Rz = RealArray2(k,k);
    Rot_x = rvector(k);
    Rot_x_inv = rvector(k);
    Rot_y = rvector(k);
    Rot_y_inv = rvector(k);
    Rot = rvector(k);
    trans = rvector(k);
    p_new= rvector(k);
    Final_point = rvector(3);
    
    // Initializing all the pointers as Identity Matrices   
    for(i=0;i<=3;i++){
        for(j=0;j<=3;j++){
            if(j==i){
                trans_mat[i][j] = 1;
                trans_mat_inv[i][j] = 1;
                Rx[i][j] = 1;
                Rx_inv[i][j] = 1;
                Ry[i][j] = 1;
                Ry_inv[i][j] = 1;
                Rz[i][j] = 1;
            }
            else{
                trans_mat[i][j] = 0;
                trans_mat_inv[i][j] = 0;
                Rx[i][j] = 0;
                Rx_inv[i][j] = 0;
                Ry[i][j] = 0;
                Ry_inv[i][j] = 0;
                Rz[i][j] = 0;
            }
        } 
    }
   
    // Creating a 4 component vector from the 3 component center of Rotation
    for(i=0;i<=3;i++){
        if(i==3){
            p[i]=1;
        }
        else{
            p[i] = p1[i];
        }
    }

    //Translation matrix
    i= 3;
    for(j=0;j<=2;j++){
        trans_mat[j][i] = (-1)*center_rot[j];            
        trans_mat_inv[j][i] = center_rot[j];
    }

    //Rotation of space about x axis
    sum = pow(axis_rot[1],2)+pow(axis_rot[2],2);
    d = sqrt(sum);
    //cos_alpha = (dot((0,0,axis[2]),(0,axis[1],axis[2]),3))/(axis[2]*d);
    cos_alpha = axis_rot[2]/d;
    //sin_alpha = (cross((0,0,axis[2]),(0,axis[1],axis[2]),3))/(axis[2]*d);
    sin_alpha = axis_rot[1]/d;

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

    sum1 = pow(axis_rot[0],2)+pow((pow(axis_rot[1],2)+pow(axis_rot[2],2)),2)/pow(d,2);
    e = sqrt(sum1);
    cos_beta = sum/(d*e);
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
    trans = MatMul(p,trans_mat,4,4);
    Rot_x = MatMul(trans,Rx,4,4);
    Rot_y = MatMul(Rot_x,Ry,4,4);
    Rot   = MatMul(Rot_y,Rz,4,4);
    Rot_y_inv = MatMul(Rot,Ry_inv,4,4);
    Rot_x_inv = MatMul(Rot_y_inv,Rx_inv,4,4);
    p_new = MatMul(Rot_x_inv,trans_mat_inv,4,4);
    
    for(i=0;i<=2;i++){
        Final_point[i] = p_new[i];
    }
  
    free(trans_mat);
    free(trans_mat_inv);
    free(Rx);
    free(Rx_inv);
    free(Ry);
    free(Ry_inv);
    free(Rz);
    free(Rot_x);
    free(Rot_x_inv);
    free(Rot_y);
    free(Rot_y_inv);
    free(Rot);
    free(trans);
    free(p_new);
    
    return Final_point;
}
