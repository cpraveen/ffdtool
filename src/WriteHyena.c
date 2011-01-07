/* Write Hyena mesh file in binary format */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void WriteHyena(MESH *mesh){
   FILE *fpt;
   UINT n, i, j, k;
   UINT npx, npy, npz;

   printf("Writing Hyena mesh file into %s ...\n", mesh->meshfile);

   fpt = fopen(mesh->meshfile, "wb");
   if(fpt==NULL){
      printf("WriteHyena: Could not open mesh file\n");
      exit(0);
   }

   fprintf(fpt, "%d\n", mesh->nblk);

   npx = npy = npz = 0;

   for(n=0; n<mesh->nblk; n++){ //loop over mesh blocks

      fprintf(fpt, "%d %d %d\n", mesh->idim[n], mesh->jdim[n], mesh->kdim[n]);

      //read xyz coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++){
               fprintf(fpt, "%24.14e %24.14e %24.14e\n", mesh->x[npx++],
                                                         mesh->y[npy++],
                                                         mesh->z[npz++]);
            }

   }
   fclose(fpt);

   printf("Finished writing mesh file\n");
}
