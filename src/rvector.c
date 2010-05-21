// Creating a real vector 
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#define SWAP(a,b)   {temp=(a); (a)=(b); (b)=temp;}

REAL *rvector(UINT);

REAL *rvector(UINT nl)
{
	REAL *v;

	v = (REAL*)malloc( nl*sizeof(REAL) ) ;
	if(!v){
		printf("Allocation failure in rvector.\n");
		exit(0);
	}
	return v;
}
