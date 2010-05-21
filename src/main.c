#include <string.h>
#include "mesh.h"
#include "ffd.h"
#include "decl.h"

int main(){
   MESH mesh;
   FFD ffd; 
   TWIST twist;

   // Read reference mesh
   ReadMesh(&mesh);

   // Read shape parameterization
   ReadFFD(&ffd, &twist);

   // Find min/max range of FFD variables
   MinMaxRangeFFD(&ffd.box);

   // Write FFD box into a .plt file for visualization
   WriteFFDBox(&ffd);

   // Write FFD Box with the axis of Wing Twist in .vtk file for visualization
   //WriteFFDBox_vtk(&ffd, &twist);

   // Check orientation of FFD box
   CheckFFDBox(&ffd.box);

   // Count number of non-zero FFD variables
   CountFFDVar(&ffd);

   // Read FFD variables from file
   ReadFFDVar(&ffd, &twist);

   // Apply FFD deformation to mesh
   DeformMesh(&mesh, &ffd);

   if(strcmp(twist.exis,"yes")==0){
       //Apply Wing Twist
       WingTwist(&mesh, &twist);
   }

   // Write deformed mesh into file
   WriteMesh(&mesh);

   return 0;
}
