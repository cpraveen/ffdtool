#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "type.h"

#define FFDTOL  1.0e-10

// Type of parameterizations
#define BEZIER  1

typedef struct ffd_box{
   UINT idim, jdim, kdim;
   REAL xmin, ymin, zmin;
   REAL xmax, ymax, zmax;
   REAL ***x;
   REAL ***y;
   REAL ***z;
} FFD_BOX;

typedef struct shape_param{
   UINT ni, nj, nk;
   REAL ***Xmin;
   REAL ***Ymin;
   REAL ***Zmin;
   REAL ***Xmax;
   REAL ***Ymax;
   REAL ***Zmax;
   REAL ***X;
   REAL ***Y;
   REAL ***Z;
} SHAPE_PARAM;

typedef struct cutoff{
   REAL lx1, lx2;
   REAL ly1, ly2;
   REAL lz1, lz2;
} CUTOFF;

typedef struct ffd{
   UINT        nvar;
   UINT        type;
   FFD_BOX     box;
   SHAPE_PARAM var;
   CUTOFF      cut;
} FFD;

typedef struct twist{
   UINT    deg;
   UINT    num_sect;
   REAL    n[3];
   REAL    x1[3],x2[3],x3[3];
   REAL    wing_len;
   REAL    theta0, theta1, theta2;
   char    exist[24];    
} TWIST; 

#endif
