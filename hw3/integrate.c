#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define PI 3.1415926535

int main(int argc, char **argv) 
{
    long long i, num_intervals;
    double rect_width, area, sum, x_middle; 
    double sum_glb ;

    int rank ;      // rank of process
    int p ;         // number of processes
    MPI_Init(&argc, &argv) ;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
    MPI_Comm_size(MPI_COMM_WORLD, &p) ;
    if ( rank == 0 )
        sscanf(argv[1],"%llu",&num_intervals);

    MPI_Bcast(&num_intervals, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    rect_width = PI / num_intervals;

    sum = 0 ;
    sum_glb = 0 ;
    for( i = 1 + rank ; i < num_intervals + 1; i += p ) {

        /* find the middle of the interval on the X-axis. */ 

        x_middle = (i - 0.5) * rect_width;
        area = sin(x_middle) * rect_width; 
        sum = sum + area;
    } 

    MPI_Reduce(&sum, &sum_glb, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if ( rank == 0 )
        printf("The total area is: %f\n", (float)sum_glb);
    MPI_Finalize();
    return 0;
}   
