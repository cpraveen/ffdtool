/* Read FFD variables from file */
#include <stdio.h>
#include <stdlib.h>
#include "ffd.h"
#include "decl.h"
#include <math.h>

void ReadFFDVar(FFD *ffd, TWIST *twist){
   FILE *fpt;
   UINT i, j, k;

   printf("Reading ffd variables file ffd.dat ...\n");
   fpt = fopen("ffd.dat", "r");
   if(fpt==NULL){
      printf("ERROR: Could not open ffd.dat file\n");
      exit(0);
   }

   ffd->var.X = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Y = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Z = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);

   printf("Coefficients of Bezier polynomial:\n");
   for(k=0; k<=ffd->var.nk; k++)
      for(j=0; j<=ffd->var.nj; j++)
         for(i=0; i<=ffd->var.ni; i++){
            ffd->var.X[i][j][k] = 0.0;
            ffd->var.Y[i][j][k] = 0.0;
            ffd->var.Z[i][j][k] = 0.0;
            if(ffd->var.Xmax[i][j][k] - ffd->var.Xmin[i][j][k] > FFDTOL)
               fscanf(fpt,"%lf", &ffd->var.X[i][j][k]);
            if(ffd->var.Ymax[i][j][k] - ffd->var.Ymin[i][j][k] > FFDTOL)
               fscanf(fpt,"%lf", &ffd->var.Y[i][j][k]);
            if(ffd->var.Zmax[i][j][k] - ffd->var.Zmin[i][j][k] > FFDTOL)
               fscanf(fpt,"%lf", &ffd->var.Z[i][j][k]);
            printf("%5d %5d %5d %15.6e %15.6e %15.6e\n", i, j, k, 
                                           ffd->var.X[i][j][k],
                                           ffd->var.Y[i][j][k],
                                           ffd->var.Z[i][j][k]);
         }
   printf("Reading twist variables:\n");

   fscanf(fpt,"%lf",&twist->theta0);
   fscanf(fpt,"%lf",&twist->theta1);
   printf("Coefficients of Quadratic Variation of Twist:\n Theta0=%lf,\nTheta1=%lf",twist->theta0,twist->theta1);
   twist->theta0 = twist->theta0*M_PI/180.0;
   twist->theta1 = twist->theta1*M_PI/180.0;

   fclose(fpt);
   printf("Finished reading file ffd.dat\n");
}
