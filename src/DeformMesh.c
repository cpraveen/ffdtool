/* Deform the mesh nodes using FFD */
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "ffd.h"
#include "mesh.h"
#include "decl.h"

void DeformMesh(MESH *mesh, FFD *ffd){
   UINT i;
   REAL x, y, z, t[3], dr[3];
   UINT inside;
   UINT ix, iy, iz, ninside=0;

   printf("Applying FFD deformation ...\n");

   for(i=0; i<mesh->np; i++){ //Loop over each grid point

      x = mesh->x[i];
      y = mesh->y[i];
      z = mesh->z[i];

      //Is this mesh point inside the ffd box
      ix = iy = iz = -1;
      inside = IsInside(x, y, z, &ffd->box, &ix, &iy, &iz);

      //If yes, find its local coordinate and apply deformation
      if(inside){
         ninside++;
         //printf("point = %d is inside\n", i);
         //printf("ix iy iz = %d %d %d\n", ix, iy, iz);
         //printf("x y z = %e %e %e\n", x, y, z);
         FFDCoord(x, y, z, &ffd->box, ix, iy, iz, t);

         //convert local FFD coordinate to global
         t[0] = (t[0] + ix)/ffd->box.idim;
         t[1] = (t[1] + iy)/ffd->box.jdim;
         t[2] = (t[2] + iz)/ffd->box.kdim;

         //compute node movement
         NodeMove(ffd, t, dr);

         //move nodes
         mesh->x[i] += dr[0];
         mesh->y[i] += dr[1];
         mesh->z[i] += dr[2];
      }
   }

   printf("Number of points deformed = %d\n", ninside);
}
