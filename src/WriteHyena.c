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
      printf("ReadHyena: Could not open mesh file\n");
      exit(0);
   }

   fwrite(&mesh->nblk, sizeof(int), 1, fpt);

   npx = npy = npz = 0;

   for(n=0; n<mesh->nblk; n++){ //loop over mesh blocks

      fwrite(&mesh->idim[n], sizeof(int), 1, fpt);
      fwrite(&mesh->jdim[n], sizeof(int), 1, fpt);
      fwrite(&mesh->kdim[n], sizeof(int), 1, fpt);

      //read xyz coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++){
               fwrite(&mesh->x[npx++], sizeof(double), 1, fpt);
               fwrite(&mesh->y[npy++], sizeof(double), 1, fpt);
               fwrite(&mesh->z[npz++], sizeof(double), 1, fpt);
            }

   }
   fclose(fpt);

   printf("Finished writing mesh file\n");
}
