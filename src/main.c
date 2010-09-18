#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesh.h"
#include "ffd.h"
#include "decl.h"

int main(int argc, char *argv[]){
   MESH mesh;
   FFD ffd; 
   TWIST twist;

   if(argc >= 3){
      printf("ffdtool: Specify <mesh type> and <filename>\n");
      printf("         mesh type = plot3d or gmsh or num3sis\n");
      exit(0);
   }

   // Copy mesh file name
   strcpy(mesh.meshfile, argv[2]);

   // Read reference mesh
   ReadMesh(&mesh, argv[1]);

   // Read shape parameterization
   ReadFFD(&ffd, &twist);

   if(strcmp(ffd.exist, "yes")==0){

      // Find min/max range of FFD variables
      MinMaxRangeFFD(&ffd.box);

      // Write FFD box into a .plt file for visualization
      WriteFFDBox(&ffd);

      // Write FFD Box with the axis of Wing Twist in .vtk file 
      // for visualization
      //WriteFFDBox_vtk(&ffd, &twist);

      // Check orientation of FFD box
      CheckFFDBox(&ffd.box);

      // Count number of non-zero FFD variables
      CountFFDVar(&ffd);
   }

   // Variable list requested
   if(argc==4 && strcmp(argv[3],"varlist")==0){
      PrintVars(&ffd, &twist);
      exit(0);
   }

   // Read FFD/twist variables from file
   ReadFFDVar(&ffd, &twist);

   // Apply FFD deformation to mesh
   if(strcmp(ffd.exist,"yes")==0)
      DeformMesh(&mesh, &ffd);

   // Apply twist deformation to mesh
   if(strcmp(twist.exist,"yes")==0)
       WingTwist(&mesh, &twist);

   // Write deformed mesh into file
   WriteMesh(&mesh, argv[1]); 

   return 0;
}
