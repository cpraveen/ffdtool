/* Write twist parameterization into file for visualization in vtk format */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"

void WriteTwist(TWIST *twist){
   FILE *fpt;
   UINT i;

   printf("Writing twist into file twist.vtk ...\n");
   fpt = fopen("twist.vtk", "w");
   if(fpt==NULL){
      printf("ERROR: Could not open twist.vtk file\n");
      exit(0);
   }

   fprintf(fpt, "# vtk DataFile Version 2.0\n");
   fprintf(fpt, "Twist parameterization\n");
   fprintf(fpt, "ASCII\n");
   fprintf(fpt, "DATASET POLYDATA\n");

   fprintf(fpt, "POINTS  %d  float\n", twist->num_sect+1);
   for(i=0; i<twist->num_sect+1; i++)
      fprintf(fpt,"%e %e %e\n", twist->x[i][0], twist->x[i][1], twist->x[i][2]);

   fprintf(fpt, "LINES  %d  %d\n", twist->num_sect, 3*twist->num_sect);
   for(i=0; i<twist->num_sect; i++)
      fprintf(fpt,"%d %d %d\n", 2, i, i+1);

   printf("Finished writing twist.vtk file\n");
}
