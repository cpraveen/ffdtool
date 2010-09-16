/* Write PLOT3D mesh file */
#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"
#include "decl.h"

void WriteGmsh(MESH *mesh){
   FILE *fpt;
   UINT n,b;

   printf("Writing Gmsh mesh file into grid.msh ...\n ");

   fpt = fopen("grid.msh", "w");
   if(fpt==NULL){
      printf("ERROR: Could open file grid.msh for writing\n");
      exit(0);
   }

   fprintf(fpt,"%s\n","$MeshFormat");
   fprintf(fpt,"%s\n","2.0   0    8");
   fprintf(fpt,"%s\n","$EndMeshFormat");
   fprintf(fpt,"%s\n","$Nodes");
  
   fprintf(fpt,"%d\n",mesh->np);
  
   for(n=0;n<mesh->np;n++){
       fprintf(fpt,"%d %lf %lf %lf\n",n+1,mesh->x[n],mesh->y[n],mesh->z[n]);
   }
  
   fprintf(fpt,"%s\n","$EndNodes");
   fprintf(fpt,"%s\n","$Elements");
   fprintf(fpt,"%d\n",mesh->n_elem);
   
   for(n=0; n<mesh->n_elem; n++){
      fprintf(fpt,"%d %d %d ",n+1,mesh->elem_type[n],3);
      for(b=0;b<=2;b++){
          fprintf(fpt,"%d ",mesh->tag[n][b]);
      }
      if(mesh->elem_type[n]==2){
          for(b=0;b<=2;b++){
              fprintf(fpt,"%d ",mesh->enodes[n][b]);
          }
      }else if(mesh->elem_type[n]==4){
          for(b=0;b<=3;b++){
              fprintf(fpt,"%d ",mesh->enodes[n][b]);
          }
      }
      fprintf(fpt,"\n");
   }
      
   fprintf(fpt,"%s\n","$EndElements");
   fclose(fpt);

   printf("DONE with writing the Mesh file\n");
}
