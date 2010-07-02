/* Read definition of FFD from file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ffd.h"
#include "decl.h"

void ReadFFD(FFD *ffd, TWIST *twist){
   FILE *fpt;
   UINT i, j, k, ii, jj, kk;
   char type[48];

   printf("Reading ffd file ffd.in ...\n");
   fpt = fopen("ffd.in", "r");
   if(fpt==NULL){
      printf("ERROR: Could not open ffd.in file\n");
      exit(0);
   }

   fscanf(fpt, "%s", type);
   printf("Type of parameterization = %s\n", type);
   if(strcmp(type,"bezier")==0){
      ffd->type = BEZIER;
   }else{
      printf("Unknown parameterization type %s\n", type);
      exit(0);
   }

   //Read FFD box
   fscanf(fpt, "%d%d%d", &ffd->box.idim, &ffd->box.jdim, &ffd->box.kdim);
   printf("Dimensions of FFD box: ");
   printf("%d %d %d\n", ffd->box.idim, ffd->box.jdim, ffd->box.kdim);
   assert(ffd->box.idim >=1);
   assert(ffd->box.jdim >=1);
   assert(ffd->box.kdim >=1);

   ffd->box.x = RealArray3(1+ffd->box.idim, 1+ffd->box.jdim, 1+ffd->box.kdim);
   ffd->box.y = RealArray3(1+ffd->box.idim, 1+ffd->box.jdim, 1+ffd->box.kdim);
   ffd->box.z = RealArray3(1+ffd->box.idim, 1+ffd->box.jdim, 1+ffd->box.kdim);

   printf("Coordinates of FFD box:\n");
   for(k=0; k<=ffd->box.kdim; k++)
      for(j=0; j<=ffd->box.jdim; j++)
         for(i=0; i<=ffd->box.idim; i++){
            fscanf(fpt, "%d%d%d%lf%lf%lf", &ii, &jj, &kk, 
                                           &ffd->box.x[i][j][k],
                                           &ffd->box.y[i][j][k],
                                           &ffd->box.z[i][j][k]);
            printf("%5d %5d %5d %15.6e %15.6e %15.6e\n", ii, jj, kk, 
                                           ffd->box.x[i][j][k],
                                           ffd->box.y[i][j][k],
                                           ffd->box.z[i][j][k]);
            assert(i==ii && j==jj && k==kk);
         }

   //FFD move cutoff parameters
   fscanf(fpt, "%lf%lf", &ffd->cut.lx1, &ffd->cut.lx2);
   fscanf(fpt, "%lf%lf", &ffd->cut.ly1, &ffd->cut.ly2);
   fscanf(fpt, "%lf%lf", &ffd->cut.lz1, &ffd->cut.lz2);
   printf("Parameters for FFD cutoff:\n");
   printf("     xi  : %15.3e%15.3e\n", ffd->cut.lx1, ffd->cut.lx2);
   printf("     eta : %15.3e%15.3e\n", ffd->cut.ly1, ffd->cut.ly2);
   printf("     zeta: %15.3e%15.3e\n", ffd->cut.lz1, ffd->cut.lz2);
   assert(ffd->cut.lx1 >= 0.0 && ffd->cut.lx1 < 0.5);
   assert(ffd->cut.lx2 >= 0.0 && ffd->cut.lx2 < 0.5);
   assert(ffd->cut.ly1 >= 0.0 && ffd->cut.ly1 < 0.5);
   assert(ffd->cut.ly2 >= 0.0 && ffd->cut.ly2 < 0.5);
   assert(ffd->cut.lz1 >= 0.0 && ffd->cut.lz1 < 0.5);
   assert(ffd->cut.lz2 >= 0.0 && ffd->cut.lz2 < 0.5);

   //Read parameterization
   fscanf(fpt, "%d%d%d", &ffd->var.ni, &ffd->var.nj, &ffd->var.nk);
   printf("Degree of Bezier polynomial: ");
   printf("%d %d %d\n", ffd->var.ni, ffd->var.nj, ffd->var.nk);
   assert(ffd->var.ni >= 1);
   assert(ffd->var.nj >= 1);
   assert(ffd->var.nk >= 1);
   ffd->var.Xmin = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Ymin = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Zmin = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Xmax = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Ymax = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   ffd->var.Zmax = RealArray3(1+ffd->var.ni, 1+ffd->var.nj, 1+ffd->var.nk);
   for(k=0; k<=ffd->var.nk; k++)
      for(j=0; j<=ffd->var.nj; j++)
         for(i=0; i<=ffd->var.ni; i++){
            fscanf(fpt, "%d%d%d%lf%lf%lf%lf%lf%lf", &ii, &jj, &kk, 
                                           &ffd->var.Xmin[i][j][k],
                                           &ffd->var.Ymin[i][j][k],
                                           &ffd->var.Zmin[i][j][k],
                                           &ffd->var.Xmax[i][j][k],
                                           &ffd->var.Ymax[i][j][k],
                                           &ffd->var.Zmax[i][j][k]);
            printf("%3d%3d%3d%11.3e%11.3e%11.3e%11.3e%11.3e%11.3e\n",
                                           ii, jj, kk, 
                                           ffd->var.Xmin[i][j][k],
                                           ffd->var.Ymin[i][j][k],
                                           ffd->var.Zmin[i][j][k],
                                           ffd->var.Xmax[i][j][k],
                                           ffd->var.Ymax[i][j][k],
                                           ffd->var.Zmax[i][j][k]);
            assert(i==ii && j==jj && k==kk);
         }

   //Read Twist parameters
   fscanf(fpt,"%s",twist->exist);
   if(strcmp(twist->exist,"yes")==0){
       fscanf(fpt,"%lf",&twist->wing_len);
       printf("Length of the wing = %lf\n",twist->wing_len);
   
       fscanf(fpt,"%lf%lf%lf",&twist->n[0],&twist->n[1],&twist->n[2]);
       printf("Axis of Wing Twist, n : (%lf, %lf, %lf)\n",
              twist->n[0],twist->n[1],twist->n[2]);

       fscanf(fpt,"%d",&twist->deg);
       printf("Degree of spanwise variation of Wing Twist: %d\n",twist->deg);    

       fscanf(fpt,"%d",&twist->num_sect);
       printf("Number of spanwise sections of Wing = %d\n",twist->num_sect);
       if(twist->num_sect==1){
           fscanf(fpt,"%lf%lf%lf",&twist->x1[0],&twist->x1[1],&twist->x1[2]);
           printf("Center of the wing root : (%lf, %lf, %lf)\n",
                  twist->x1[0],twist->x1[1],twist->x1[2]);
           fscanf(fpt,"%lf%lf%lf",&twist->x2[0],&twist->x2[1],&twist->x2[2]);
           printf("Center of last Crossection of the wing: (%lf, %lf, %lf)\n",
                  twist->x2[0],twist->x2[1],twist->x2[2]);
       } 
       else if(twist->num_sect==2){    
           printf("Twist for num_sect=2 not implemented\n");
           exit(0);
           fscanf(fpt,"%lf%lf%lf",&twist->x1[0],&twist->x1[1],&twist->x1[2]);
           printf("Center of the wing root : (%lf, %lf, %lf)\n",
                  twist->x1[0],twist->x1[1],twist->x1[2]);
           fscanf(fpt,"%lf%lf%lf",&twist->x2[0],&twist->x2[1],&twist->x2[2]);
           printf("Center of Middle section of the wing: (%lf, %lf, %lf)\n",
                  twist->x2[0],twist->x2[1],twist->x2[2]);
           fscanf(fpt,"%lf%lf%lf",&twist->x3[0],&twist->x3[1],&twist->x3[2]);
           printf("Center of last Crossection of the wing: (%lf, %lf, %lf)\n",
                  twist->x3[0],twist->x3[1],twist->x3[2]);
       }       
   }
   else if(strcmp(twist->exist,"no")==0)
      printf("No twist variable\n");
   else{
      printf("Unknown twist option\n");
      exit(0);
   }
              

    
   fclose(fpt);
   printf("Finished reading ffd file ffd.in\n");
}
