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
    }else{
        printf("ReadMesh: Unknown mesh type\n");
        exit(0);
    }
        
}
