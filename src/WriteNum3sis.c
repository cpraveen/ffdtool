/* Write num3sis submesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void WriteNum3sis(MESH *mesh){
   FILE *fpt;
   UINT n, j;

   printf("Writing Num3sis mesh file into %s ...", mesh->meshfile);
   fpt = fopen(mesh->meshfile, "w");
   if(fpt==NULL){
      printf("ReadNum3sis: Could not open mesh file\n");
      exit(0);
   }

   fprintf(fpt,"%d\n", mesh->id);
   fprintf(fpt,"%d %d %d\n", mesh->np, mesh->n_elem, mesh->n_face);
   fprintf(fpt,"%d\n", mesh->neighbour_id);

   // Read coordinates
   for(n=0; n<mesh->np; n++){
      fprintf(fpt, "%lf %lf %lf\n", mesh->x[n], mesh->y[n], mesh->z[n]);
   }

   // Read tetrahedra
   for(n=0;n<mesh->n_elem;n++){
      for(j=0; j<4; j++) fprintf(fpt,"%d ", mesh->enodes[n][j]);
      fprintf(fpt,"\n");
   }

   // Read boundary triangles
   for(n=mesh->n_elem; n<mesh->n_elem+mesh->n_face; n++){
      fprintf(fpt,"%d ", mesh->elem_type[n]);
      for(j=0; j<3; j++) fprintf(fpt,"%d ", mesh->enodes[n][j]);
      fprintf(fpt,"\n");
   }

   // Flag to indicate if node is shared or not
   for(n=0; n<mesh->np; n++)
      fprintf(fpt, "%d\n", mesh->node_type[n]);

   // Global id of each node
   for(n=0; n<mesh->np; n++)
      fprintf(fpt, "%d\n", mesh->node_global_id[n]);

   fclose(fpt);

   printf("DONE\n");
}
