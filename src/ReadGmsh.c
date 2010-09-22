/* Read Gmsh mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void ReadGmsh(MESH *mesh){
   FILE *fpt;
   UINT n,i,j;
   UINT index,nnodes=0;
   UINT ntags;
   char a[100];
   char meshfile[100];

   strcpy(meshfile, mesh->meshfile);
   strcat(meshfile, ".0");

   printf("Reading Gmsh mesh file from %s ...\n", meshfile);
   fpt = fopen(meshfile, "r");
   if(fpt==NULL){
      printf("ReadGmsh: Could not read mesh file\n");
      exit(0);
   }
   for(i=0;i<=5;i++) {
       fscanf(fpt,"%s",a);
   }
   fscanf(fpt,"%d",&mesh->np);
   mesh->x = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->y = (REAL*)calloc(mesh->np, sizeof(REAL));
   mesh->z = (REAL*)calloc(mesh->np, sizeof(REAL));

   for(n=0; n<mesh->np; n++){ //loop over nodes

      //read x,y and z coordinates
      fscanf(fpt, "%d %lf %lf %lf", &index, 
                  &mesh->x[n], &mesh->y[n], &mesh->z[n]);
   }

   if(index!=mesh->np){
       printf("Error reading the mesh file\n");
       exit(0);
   }

   for(i=0;i<=1;i++){
       fscanf(fpt,"%s",a);
   }
   fscanf(fpt,"%d",&mesh->n_elem);

   mesh->tag = IntegerArray2(mesh->n_elem, 3);

   mesh->enodes = (UINT**)malloc(mesh->n_elem*sizeof(UINT*));
   mesh->elem_type = (UINT*)malloc(mesh->n_elem*sizeof(UINT));

   for(n=0;n<mesh->n_elem;n++){

       fscanf(fpt,"%d%d%d",&index,&mesh->elem_type[n],&ntags);

       if(ntags!=3){
           printf("Error in the mesh file\n");
           printf("ntags is not equal to 3; n =%d\n",n);
           exit(0);
       }
       if(mesh->elem_type[n] == 2){
   	mesh->enodes[n] = (UINT*)malloc(3*sizeof(UINT));
        nnodes = 3;
       }
       else if(mesh->elem_type[n] == 4){
   	mesh->enodes[n] = (UINT*)malloc(4*sizeof(UINT));
        nnodes = 4;
       }else{
        printf("Unknown element type = %d\n", mesh->elem_type[n]);
        exit(0);
       }

       //read tags
       fscanf(fpt,"%d%d%d",&mesh->tag[n][0],&mesh->tag[n][1],&mesh->tag[n][2]);
       
       //read nodes
       for(j=0; j<nnodes; j++)
       	  fscanf(fpt,"%d",&mesh->enodes[n][j]);
   }

   if (index!=mesh->n_elem){
       printf("Error while reading the file");
       exit(0);
   }
   fclose(fpt);

   printf("Finished reading mesh file\n");
}
