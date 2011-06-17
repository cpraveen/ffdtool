/* Write PLOT3D mesh file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void WriteMesh(MESH *mesh, char *meshtype){

    if(strcmp(meshtype,"gmsh")==0){
        WriteGmsh(mesh);
    }else if(strcmp(meshtype,"plot3d")==0){
        WritePlot3D(mesh);
    }else if(strcmp(meshtype,"num3sis")==0){
        WriteNum3sis(mesh);
    }else if(strcmp(meshtype,"hyena")==0){
        WriteHyena(mesh);
    }else if(strcmp(meshtype,"visp3d")==0){
        WriteVisp3d(mesh);
    }else{
       printf("WriteMesh: Dont know how to write this mesh !!!\n");
       exit(0);
    }
}
