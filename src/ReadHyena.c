/* Read Hyena mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void ReadHyena(MESH *mesh){
   FILE *fpt;
   UINT n, i, j, k;
   UINT npx, npy, npz;
   char meshfile[100];

   strcpy(meshfile, mesh->meshfile);
   strcat(meshfile, ".0");

   printf("Reading Hyena mesh file from %s ...\n", meshfile);

   fpt = fopen(meshfile, "r");
   if(fpt==NULL){
      printf("ReadHyena: Could not open mesh file\n");
      exit(0);
   }

   fscanf(fpt, "%d", &mesh->nblk);
   printf("Number of blocks = %d\n", mesh->nblk);
   mesh->idim = (UINT*)calloc(mesh->nblk, sizeof(UINT));
   mesh->jdim = (UINT*)calloc(mesh->nblk, sizeof(UINT));
   mesh->kdim = (UINT*)calloc(mesh->nblk, sizeof(UINT));

   mesh->np = 0;

   npx = npy = npz = 0;

   for(n=0; n<mesh->nblk; n++){ //loop over mesh blocks

      fscanf(fpt, "%d%d%d", &mesh->idim[n], &mesh->jdim[n], &mesh->kdim[n]);
      printf("%d %d %d %d\n", n+1, mesh->idim[n], mesh->jdim[n], mesh->kdim[n]);

      mesh->np += mesh->idim[n] * mesh->jdim[n] * mesh->kdim[n];

      if(n==0){
         mesh->x = (REAL*)malloc(mesh->np * sizeof(REAL));
         mesh->y = (REAL*)malloc(mesh->np * sizeof(REAL));
         mesh->z = (REAL*)malloc(mesh->np * sizeof(REAL));
      }else{
         mesh->x = realloc(mesh->x, mesh->np * sizeof(REAL));
         mesh->y = realloc(mesh->y, mesh->np * sizeof(REAL));
         mesh->z = realloc(mesh->z, mesh->np * sizeof(REAL));
      }

      //read xyz coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fscanf(fpt, "%lf%lf%lf", &mesh->x[npx++],
                                        &mesh->y[npy++],
                                        &mesh->z[npz++]);

   }
   fclose(fpt);

   printf("Finished reading mesh file\n");
}
