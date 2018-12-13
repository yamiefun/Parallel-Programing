#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

int isprime(int n) {
	int i,squareroot;
	if (n>10) {
		squareroot = (int) sqrt(n);
		for (i=3; i<=squareroot; i=i+2)
			if ((n%i)==0)
				return 0;
		return 1;
	}
	else
		return 0;
}

int main(int argc, char *argv[])
{
	int pc;					/* prime counter */
	long long int foundone = 0 ; /* most recent prime found */
	long long int n, limit;

	int pc_sum = 0 ;
	long long int foundone_glb = 0 ;


	int rank ; 		// rank of process
	int p ;       	// number of processes
	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &p) ;

	sscanf(argv[1],"%llu",&limit);	
	if ( rank == 0 )
		printf("Starting. Numbers to be scanned= %llu\n",limit);


	long long int stride ;
	stride = p * 2 ;
	//pc=4;     /* Assume (2,3,5,7) are counted here */
	pc = 0 ;
	foundone_glb = 0 ;
	for ( n = 11 + rank * 2 ; n <= limit ; n += stride ){
		if (isprime(n)) {
			pc++;
			foundone = n;
		}
	}
	MPI_Reduce(&pc, &pc_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD) ;
	MPI_Reduce(&foundone, &foundone_glb, 1, MPI_LONG_LONG, MPI_MAX, 0, MPI_COMM_WORLD) ;
	
	MPI_Finalize();
	pc_sum += 4 ;
	if ( rank == 0 )
		printf("Done. Largest prime is %llu Total primes %d\n", foundone_glb, pc_sum);

	return 0;
} 
