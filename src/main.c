#include "mesh.h"
#include "ffd.h"
#include "decl.h"

int main(){
   MESH mesh;
   FFD ffd;

   // Read reference mesh
   ReadMesh(&mesh);

   // Read shape parameterization
   ReadFFD(&ffd);

   // Find min/max range of FFD variables
   MinMaxRangeFFD(&ffd.box);

   // Write FFD box into a file for visualization
   WriteFFDBox(&ffd);

   // Check orientation of FFD box
   CheckFFDBox(&ffd.box);

   // Count number of non-zero FFD variables
   CountFFDVar(&ffd);

   // Read FFD variables from file
   ReadFFDVar(&ffd);

   // Apply FFD deformation to mesh
   DeformMesh(&mesh, &ffd);

   // Write deformed mesh into file
   WriteMesh(&mesh);

   return 0;
}
