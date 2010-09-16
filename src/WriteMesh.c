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
    }
}
