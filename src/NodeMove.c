/* Find node movement by calling appropriate parameterization. Also applies 
 * cutoff to the movement. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ffd.h"
#include "decl.h"

void NodeMove(FFD *ffd, REAL *t, REAL *dr){
   REAL cutoff;
   UINT i;

   if(ffd->type == BEZIER){
      Bezier3D(&ffd->var, t, dr);
   }
   else{
      printf("NodeMove: Unknown parameterization type\n");
      exit(0);
   }

   //Apply cutoff for node movement
   //Along xi
   cutoff = 1.0;
   if(t[0] < ffd->cut.lx1 && ffd->cut.lx1 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.lx1/(ffd->cut.lx1 - t[0]) - 
                                0.5*ffd->cut.lx1/t[0] ));
   }
   if(1.0 - t[0] < ffd->cut.lx2 && ffd->cut.lx2 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.lx2/(ffd->cut.lx2 - 1.0 + t[0]) - 
                                0.5*ffd->cut.lx2/(1.0 - t[0]) ));
   }
   for(i=0; i<3; i++) dr[i] = cutoff*dr[i];

   //Along eta
   cutoff = 1.0;
   if(t[1] < ffd->cut.ly1 && ffd->cut.ly1 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.ly1/(ffd->cut.ly1 - t[1]) - 
                                0.5*ffd->cut.ly1/t[1] ));
   }
   if(1.0 - t[1] < ffd->cut.ly2 && ffd->cut.ly2 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.ly2/(ffd->cut.ly2 - 1.0 + t[1]) - 
                                0.5*ffd->cut.ly2/(1.0 - t[1]) ));
   }
   for(i=0; i<3; i++) dr[i] = cutoff*dr[i];

   //Along zeta
   cutoff = 1.0;
   if(t[2] < ffd->cut.lz1 && ffd->cut.lz1 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.lz1/(ffd->cut.lz1 - t[2]) - 
                                0.5*ffd->cut.lz1/t[2] ));
   }
   if(1.0 - t[2] < ffd->cut.lz2 && ffd->cut.lz2 > 0.0){
      cutoff = 0.5*(1.0 + tanh( 0.5*ffd->cut.lz2/(ffd->cut.lz2 - 1.0 + t[2]) - 
                                0.5*ffd->cut.lz2/(1.0 - t[2]) ));
   }
   for(i=0; i<3; i++) dr[i] = cutoff*dr[i];


}
