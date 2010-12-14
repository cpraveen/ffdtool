#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "decl.h"

void ReadMesh(MESH *mesh, char *meshtype){

    if(strcmp(meshtype,"gmsh")==0){
        ReadGmsh(mesh);
    }else if(strcmp(meshtype,"plot3d")==0){
        ReadPlot3D(mesh);
    }else if(strcmp(meshtype,"num3sis")==0){
        ReadNum3sis(mesh);
    }else if(strcmp(meshtype,"hyena")==0){
        ReadHyena(mesh);
    }else{
        printf("ReadMesh: Unknown mesh type %s\n", meshtype);
        printf("          Valid types are:\n");
        printf("             gmsh, plot3d, num3sis, hyena\n");
        exit(0);
    }
        
}
