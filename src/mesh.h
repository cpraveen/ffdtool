#ifndef _MESH_H_
#define _MESH_H_

#include "type.h"

typedef struct mesh{
   UINT nblk, np;
   UINT n_elem, tet_num;
   UINT *idim, *jdim, *kdim;
   REAL *x, *y, *z;
   UINT *elem_type;
   UINT **tag, **enodes;
} MESH;

#endif
