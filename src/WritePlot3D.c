/* Write PLOT3D mesh file */
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "decl.h"

void WritePlot3D(MESH *mesh){
   FILE *fpt;
   UINT n, i, j, k, npx, npy, npz;

   printf("Writing PLOT3D mesh file into grid.fmt ... ");

   fpt = fopen("grid.fmt", "w");
   if(fpt==NULL){
      printf("ERROR: Could open file grid.fmt for writing\n");
      exit(0);
   }

   if(mesh->nblk <= 0){
      printf("ERROR: There are no blocks in the grid\n");
      exit(0);
   }
            
   // write number of blocks only if it is > 1, needed by nuwtun
   if(mesh->nblk > 1) fprintf(fpt, "%d\n", mesh->nblk);

   for(n=0; n<mesh->nblk; n++)
      fprintf(fpt, "%d %d %d\n", mesh->idim[n],
                                 mesh->jdim[n],
                                 mesh->kdim[n]);
   npx = npy = npz = 0;
   for(n=0; n<mesh->nblk; n++){ //loop over mesh blocks

      //write x coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fprintf(fpt, "%24.14e\n", mesh->x[npx++]);

      //write y coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fprintf(fpt, "%24.14e\n", mesh->y[npy++]);

      //write z coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fprintf(fpt, "%24.14e\n", mesh->z[npz++]);
   }
   fclose(fpt);

   printf("DONE\n");
}
