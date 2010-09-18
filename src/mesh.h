#ifndef _MESH_H_
#define _MESH_H_

#include "type.h"

typedef struct mesh{
   char meshfile[80];

   UINT nblk, np;
   UINT *idim, *jdim, *kdim;
   REAL *x, *y, *z;

   // These are needed for unstructured grids
   UINT n_elem, n_face;
   UINT *elem_type;
   UINT **tag, **enodes;
   UINT id;
   UINT neighbour_id;
   UINT *node_type;
   UINT *node_global_id;

} MESH;

#endif
