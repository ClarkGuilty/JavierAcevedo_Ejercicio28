#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
#include <time.h>

double func(double x)
{
    return 1.0 - x*x + x;
}

double inMC(int N, double xmin, double xmax)
{
    int i;
    double total;
    double x;
    for(i=0;i<N;i++){
        x = drand48();
        //printf("%d %f\n", N,x);
        total += func(xmin + (xmax-xmin)*x);
    }
    return total*(xmax-xmin)/(N*1.0);
}

int main(int argc, char *argv[])
{
int true=1; /* to force the loop */
int rank, /* rank of the MPI process */
size, /* number of processes */
i, /* variable for the loop */
len, /* name of the process */
N;
double PI_VALUE = 3.141592653589793238462643;
/* reference value of pi */
double mypi, /* value for each process */
pi, /* value of pi calculated */
h,
sum, /*sum of the area */
x,
total,
integral;

char name[80]; 

if( argc != 2 ) {
    printf("La entrada debe ser de la forma %s N\n", argv[0]);
    exit(0);
}
N = atoi(argv[1]);

/*Initialization */
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
srand48(rank+time(NULL));
/* We ask for the name of the node */
MPI_Get_processor_name(name, &len);
total = inMC(N/size, 0, 1);

//printf("This is my integral: %.16f from rank: %d\n", total,rank);
MPI_Reduce(&total, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
if (rank == 0){
//printf("The integral is approximately %.16f\n", integral/size);
  printf("%.16f\n",integral/size);
}
MPI_Finalize();
return 0;
}





