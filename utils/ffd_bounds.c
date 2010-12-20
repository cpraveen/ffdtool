/* Generates lower/upper bounds. You can specify control points that
 * must be fixed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
   int i, j, k;
   int idim, jdim, kdim;
   int nvar;
   int izero[1000], jzero[1000], kzero[1000];
   double ilow, jlow, klow, iup, jup, kup;
   int dir;
   FILE* fpt;


   printf("Enter idim, jdim, kdim: ");
   scanf("%d %d %d", &idim, &jdim, &kdim);

   printf("Enter direction (0,1,2): ");
   scanf("%d", &dir);
   assert(dir==0 || dir==1 || dir==2);

   if(dir==0){
      printf("Enter ilow, iup: ");
      scanf("%lf %lf", &ilow, &iup);
      jlow = jup = klow = kup = 0.0;
   }else if(dir==1){
      printf("Enter jlow, jup: ");
      scanf("%lf %lf", &jlow, &jup);
      ilow = iup = klow = kup = 0.0;
   }else if(dir==2){
      printf("Enter klow, kup: ");
      scanf("%lf %lf", &klow, &kup);
      ilow = iup = jlow = jup = 0.0;
   }

   for(k=0; k<=kdim; k++)
       kzero[k] = 1;

   for(j=0; j<=jdim; j++)
       jzero[j] = 1;

   for(i=0; i<=idim; i++)
       izero[i] = 1;

   printf("Zeros for i direction:\n");
   i = 0;
   while(i != -1)
   {
      printf("Enter -1 to end: ");
      printf("Min=%d, max=%d, -1 to end: ", 0, idim);
      scanf("%d", &i);
      if(i >= 0) izero[i] = 0;
   }

   printf("Zeros for j direction:\n");
   j = 0;
   while(j != -1)
   {
      printf("Enter -1 to end: ");
      printf("Min=%d, max=%d, -1 to end: ", 0, jdim);
      scanf("%d", &j);
      if(j >= 0) jzero[j] = 0;
   }

   printf("Zeros for k direction:\n");
   k = 0;
   while(k != -1)
   {
      printf("Enter -1 to end: ");
      printf("Min=%d, max=%d, -1 to end: ", 0, kdim);
      scanf("%d", &k);
      if(k >= 0) kzero[k] = 0;
   }

   printf("\n");

   nvar = 0;

   fpt = fopen("bounds.dat", "w");

   printf("%d %d %d\n\n", idim, jdim, kdim);
   for(k=0; k<=kdim; k++)
      for(j=0; j<=jdim; j++)
         for(i=0; i<=idim; i++)
         {
            if(izero[i]==0 || jzero[j]==0 || kzero[k]==0)
               printf("%d %d %d %10.3e %10.3e %10.3e %10.3e %10.3e %10.3e\n",
                     i, j, k, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            else
            {
               printf("%d %d %d %10.3e %10.3e %10.3e %10.3e %10.3e %10.3e\n",
                     i, j, k, ilow, jlow, klow, iup, jup, kup);
               ++nvar;
               if(dir==0)fprintf(fpt,"x%d  %e  %e  0.0\n", nvar, ilow, iup);
               if(dir==1)fprintf(fpt,"x%d  %e  %e  0.0\n", nvar, jlow, jup);
               if(dir==2)fprintf(fpt,"x%d  %e  %e  0.0\n", nvar, klow, kup);
            }
         }

   fclose(fpt);

   printf("Number of variables = %d\n", nvar);
   printf("Bounds written into bounds.dat, use it in opt.in\n");
}
