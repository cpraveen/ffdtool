/* Read num3sis submesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void ReadNum3sis(MESH *mesh){
   FILE *fpt;
   UINT n, j;
   UINT n_elem_all;
   char meshfile[100];

   strcpy(meshfile, mesh->meshfile);
   strcat(meshfile, ".0");

   printf("Reading Num3sis mesh file from %s ...\n", meshfile);
   fpt = fopen(meshfile, "r");
   if(fpt==NULL){
      printf("ReadNum3sis: Could not open mesh file\n");
      exit(0);
   }

   fscanf(fpt,"%d", &mesh->id);
   fscanf(fpt,"%d%d%d", &mesh->np, &mesh->n_elem, &mesh->n_face);
   fscanf(fpt,"%d", &mesh->neighbour_id);

   n_elem_all = mesh->n_elem + mesh->n_face;

   mesh->x = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->y = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->z = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->node_type = (UINT*)calloc(mesh->np, sizeof(UINT));
   mesh->node_global_id = (UINT*)calloc(mesh->np, sizeof(UINT));

   mesh->elem_type = (UINT*)calloc(n_elem_all, sizeof(UINT));
   mesh->enodes = (UINT**)calloc(n_elem_all, sizeof(UINT*));

   // Read coordinates
   for(n=0; n<mesh->np; n++){
      fscanf(fpt, "%lf%lf%lf", &mesh->x[n], &mesh->y[n], &mesh->z[n]);
   }

   // Read tetrahedra
   for(n=0;n<mesh->n_elem;n++){
   	mesh->enodes[n] = (UINT*)malloc(4*sizeof(UINT));
      for(j=0; j<4; j++) fscanf(fpt,"%d",&mesh->enodes[n][j]);
   }

   // Read boundary triangles
   for(n=mesh->n_elem; n<mesh->n_elem+mesh->n_face; n++){
   	mesh->enodes[n] = (UINT*)malloc(3*sizeof(UINT));
      fscanf(fpt,"%d",&mesh->elem_type[n]);
      for(j=0; j<3; j++) fscanf(fpt,"%d",&mesh->enodes[n][j]);
   }

   // Flag to indicate if node is shared or not
   for(n=0; n<mesh->np; n++)
      fscanf(fpt, "%d", &mesh->node_type[n]);

   // Global id of each node
   for(n=0; n<mesh->np; n++)
      fscanf(fpt, "%d", &mesh->node_global_id[n]);

   fclose(fpt);

   printf("Finished reading mesh file\n");
}
