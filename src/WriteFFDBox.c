/* Write FFD box into file for visualization in plot3d format */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"

void WriteFFDBox(FFD *ffd){
   FILE *fpt;
   UINT i, j, k;

   printf("Writing ffd box into file ffdbox.plt ...\n");
   fpt = fopen("ffdbox.plt", "w");
   if(fpt==NULL){
      printf("ERROR: Could not open ffdbox.plt file\n");
      exit(0);
   }
   //fprintf(fpt, "TITLE = FFDBOX\n");
   //fprintf(fpt, "VARIABLES = X, Y, Z\n");
   //fprintf(fpt, "ZONE I=%d, J=%d, K=%d\n", ffd->box.idim+1, ffd->box.jdim+1,
                                             //ffd->box.kdim+1);
   fprintf(fpt, "1\n");
   fprintf(fpt, "%d %d %d\n", ffd->box.idim+1, ffd->box.jdim+1,
                                             ffd->box.kdim+1);

   for(k=0; k<=ffd->box.kdim; k++)
      for(j=0; j<=ffd->box.jdim; j++)
         for(i=0; i<=ffd->box.idim; i++){
            /*
            fprintf(fpt, "%15.6e %15.6e %15.6e\n",
                                           ffd->box.x[i][j][k],
                                           ffd->box.y[i][j][k],
                                           ffd->box.z[i][j][k]); */
            fprintf(fpt, "%15.6e ", ffd->box.x[i][j][k]);
         }

   fprintf(fpt, "\n");

   for(k=0; k<=ffd->box.kdim; k++)
      for(j=0; j<=ffd->box.jdim; j++)
         for(i=0; i<=ffd->box.idim; i++)
            fprintf(fpt, "%15.6e ", ffd->box.y[i][j][k]);

   fprintf(fpt, "\n");

   for(k=0; k<=ffd->box.kdim; k++)
      for(j=0; j<=ffd->box.jdim; j++)
         for(i=0; i<=ffd->box.idim; i++)
            fprintf(fpt, "%15.6e ", ffd->box.z[i][j][k]);
   fclose(fpt);
   printf("Finished writing ffdbox.plt file\n");
}
