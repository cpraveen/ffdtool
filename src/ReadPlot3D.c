/* Read PLOT3D mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mesh.h"
#include "decl.h"

void ReadPlot3D(MESH *mesh){
   FILE *fpt;
   UINT n, i, j, k;
   UINT npx, npy, npz;
   char meshfile[100];

   strcpy(meshfile, mesh->meshfile);
   strcat(meshfile, ".0");

   printf("Reading PLOT3D mesh file from %s ...\n", meshfile);

   fpt = fopen(meshfile, "r");
   if(fpt==NULL){
      printf("ReadMesh: Could not open mesh file\n");
      exit(0);
   }

   fscanf(fpt, "%d", &mesh->nblk);
   assert(mesh->nblk > 0);
   printf("Number of blocks = %d\n", mesh->nblk);
   mesh->idim = (UINT*)calloc(mesh->nblk, sizeof(UINT));
   mesh->jdim = (UINT*)calloc(mesh->nblk, sizeof(UINT));
   mesh->kdim = (UINT*)calloc(mesh->nblk, sizeof(UINT));

   mesh->np = 0;
   for(n=0; n<mesh->nblk; n++){
      fscanf(fpt, "%d%d%d", &mesh->idim[n], &mesh->jdim[n], &mesh->kdim[n]);
      printf("%d %d %d %d\n", n+1, mesh->idim[n], mesh->jdim[n], mesh->kdim[n]);
      assert(mesh->idim[n] > 0);
      assert(mesh->jdim[n] > 0);
      assert(mesh->kdim[n] > 0);
      mesh->np += mesh->idim[n] * mesh->jdim[n] * mesh->kdim[n];
   }
   printf("Total number of mesh points = %d\n", mesh->np);
   mesh->x = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->y = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->z = (REAL*)calloc(mesh->np, sizeof(REAL));

   npx = npy = npz = 0;

   for(n=0; n<mesh->nblk; n++){ //loop over mesh blocks

      //read x coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fscanf(fpt, "%lf", &mesh->x[npx++]);

      //read y coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fscanf(fpt, "%lf", &mesh->y[npy++]);

      //read z coordinates
      for(k=0; k<mesh->kdim[n]; k++)
         for(j=0; j<mesh->jdim[n]; j++)
            for(i=0; i<mesh->idim[n]; i++)
               fscanf(fpt, "%lf", &mesh->z[npz++]);

   }
   fclose(fpt);

   printf("Finished reading mesh file\n");
}
