/* Read Gmsh mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mesh.h"
#include "decl.h"

void WriteVisp3d(MESH *mesh){
   FILE *fpt;
   UINT n;

   printf("Writing Visp3d xyz file into %s ...\n", mesh->meshfile);
   fpt = fopen(mesh->meshfile, "w");
   if(fpt==NULL){
      printf("WriteVisp3d: Could not open file %s\n", mesh->meshfile);
      exit(0);
   }

   for(n=0; n<mesh->np; n++){ //loop over nodes
      fprintf(fpt, "%lf %lf %lf",
                  mesh->x[n], mesh->y[n], mesh->z[n]);
   }

   fclose(fpt);

   printf("Finished writing Visp3d mesh file\n");
}
