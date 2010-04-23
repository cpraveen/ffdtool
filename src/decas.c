#include "type.h"
#include "decl.h"

REAL decas(UINT degree, REAL coeff[], REAL t)
/*
     uses  de Casteljau to compute one coordinate
     value of a  Bezier curve. Has to be called 
     for each coordinate  (x,y, and/or z) of a control polygon.
     Input:   degree: degree of curve.
              coeff:  array with coefficients of curve.
              t:      parameter value.
      Output: coordinate value.
*/
{
	UINT r,i;
	REAL t1;
	REAL coeffa[30];  /* an auxiliary array. Change dim. if too small*/

	t1 = 1.0 - t;
	for(i=0; i<=degree; i++) coeffa[i]=coeff[i]; /* save input */

	for (r=1; r<= degree; r++)
		for (i=0; i<= degree - r; i++)
		{
			coeffa[i]= t1* coeffa[i]  +   t * coeffa[i+1] ;
		}

	return (coeffa[0]);
}
