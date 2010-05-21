// Creating a real vector 
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "decl.h"

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
