#include <stdlib.h>
#define SWAP(a,b)   {temp=(a); (a)=(b); (b)=temp;}

int *ivector(int);

int *ivector(int nl)
{
	int *v;

	v = (int*)malloc( nl*sizeof(int) ) ;
	if(!v){
		printf("Allocation failure in ivector.\n");
		exit(0);
	}
	return v;
}
