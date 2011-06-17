/* Read Gmsh mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mesh.h"
#include "decl.h"

void ReadVisp3d(MESH *mesh){
   FILE *fpt;
   UINT n,i;
   char meshfile[100];

   // First read number of points in mesh
   printf("Reading Visp3d bunfc.dat file\n");
   fpt = fopen("bunfc.dat", "r");
   if(fpt==NULL){
      printf("ReadVisp3d: Could not open bunfc.dat file\n");
      exit(0);
   }
   fscanf(fpt,"%d%d%d",&i,&i,&mesh->np);
   fclose(fpt);

   printf("Number of points = %d\n", mesh->np);
   assert (mesh->np > 0);
   mesh->x = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->y = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->z = (REAL*)calloc(mesh->np, sizeof(REAL));

   // Now read xyz coordinates
   strcpy(meshfile, mesh->meshfile);
   strcat(meshfile, ".0");

   printf("Reading Visp3d xyz file from %s ...\n", meshfile);
   fpt = fopen(meshfile, "r");
   if(fpt==NULL){
      printf("ReadVisp3d: Could not read Visp3d xyz file\n");
      exit(0);
   }

   for(n=0; n<mesh->np; n++){ //loop over nodes
      //read x,y and z coordinates
      fscanf(fpt, "%lf%lf%lf",
                  &mesh->x[n], &mesh->y[n], &mesh->z[n]);
   }

   fclose(fpt);

   printf("Finished reading Visp3d mesh file\n");
}
