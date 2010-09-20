/* Find all surface triangles inside FFD box and set new
 * flag for them. THIS IS NOT A GENERAL FUNCTION. YOU NEED
 * TO BE CAREFUL WHEN USING THIS. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "type.h"
#include "ffd.h"
#include "mesh.h"
#include "decl.h"

void FlagInsideTri(MESH *mesh, FFD *ffd){
   UINT i, j;
   REAL x, y, z;
   UINT ix, iy, iz;
   UINT n0, n1, n2;
   UINT this_type;
   UINT new_flag=10;
   UINT nbtypes;
   UINT *btype;
   UINT *insideflag;
   UINT nchanged=0;

   if(strcmp(ffd->exist,"no")==0){
      printf("FlagInsideTri: FFD does not exist !!!");
      return;
   }

   printf("How many boundary types ? ");
   scanf("%d", &nbtypes);
   assert(nbtypes>0);
   btype = IntegerArray(nbtypes);
   printf("Enter types which must be changed\n");
   for(i=0; i<nbtypes; i++){
      printf("%5d ", i);
      scanf("%d", &btype[i]);
   }

   printf("Enter new type : ");
   scanf("%d", &new_flag);
   assert(new_flag>0);

   insideflag = IntegerArray(mesh->np);

   // Find points inside FFD box
   for(i=0; i<mesh->np; i++){ //Loop over each grid point

      x = mesh->x[i];
      y = mesh->y[i];
      z = mesh->z[i];

      //Is this mesh point inside the ffd box
      ix = iy = iz = -1;
      insideflag[i] = IsInside(x, y, z, &ffd->box, &ix, &iy, &iz);

   }

   // Find triangles inside FFD box
   for(i=mesh->n_elem; i<mesh->n_elem+mesh->n_face; i++){
      n0 = mesh->enodes[i][0] - 1;
      n1 = mesh->enodes[i][1] - 1;
      n2 = mesh->enodes[i][2] - 1;

      this_type = 0;
      for(j=0; j<nbtypes; j++) 
         if(mesh->elem_type[i] == btype[j])
            this_type = 1;

      if((insideflag[n0]==1 || insideflag[n1]==1 || insideflag[n2]==1) &&
         this_type==1){
            mesh->elem_type[i] = new_flag;
            ++nchanged;
      }
   }

   printf("Changed flags for %d triangles\n", nchanged);

   // Free local memory
   free(btype);
   free(insideflag);

}
