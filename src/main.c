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

   MinMaxRangeFFD(&ffd.box);

   WriteFFDBox(&ffd);

   CheckFFDBox(&ffd.box);

   CountFFDVar(&ffd);

   ReadFFDVar(&ffd);

   DeformMesh(&mesh, &ffd);

   WriteMesh(&mesh);

   return 0;
}
