#ifndef _MESH_H_
#define _MESH_H_

#include "type.h"

typedef struct mesh{
   UINT nblk, np;
   UINT *idim, *jdim, *kdim;
   REAL *x, *y, *z;
} MESH;

#endif
