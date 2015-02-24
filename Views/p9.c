#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void printArray (int *row, int nElements) {
    int i;
	printf("\n");
    for (i=0; i<nElements; i++) {
        printf("%d ", row[i]);
    }
    
}
void main(int argc , char* argv[])
{
	int size , rank;
	MPI_Status status;
	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD , &size);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	
	time_t t;
	int i , j;
	srand((unsigned) time(&t));

	int *vector = (int *)malloc(sizeof(int) * size);
	int *recv = (int *)malloc(sizeof(int) * size);
	int *matrix = (int *)malloc(size * size * sizeof(int));
	
	if(rank == 0)
	{
		for(i = 0; i < size * size; i++)
		{
			
			matrix[i] = rand() % 100;
		}
		
		for(i = 0; i < size; i++)
		{
			vector[i] = rand() % 100;
		}
		printf("The vector is:\n");
		printArray(vector , size);
		printf("The matrix is:\n");
		printArray(matrix , size * size);
	}
	MPI_Bcast(vector , size , MPI_INT , 0 , MPI_COMM_WORLD);
	MPI_Scatter(matrix , size , MPI_INT, recv , size , MPI_INT , 0 , MPI_COMM_WORLD);
	
	for(i = 0; i < size; i++)
	{
		printf("%d, ",recv[i]);
	}
	//printArray(recv , size);
	
	int *sum= (int *)malloc(sizeof(int) );
	//int sum= 0;	
	*sum=0;
	i = 0;
	int s=0;
	for(; i < size; i++)
	{
		(*sum) = (*sum) + vector[i] * recv[i];
		//sum = sum + vector[i]*recv[i];		
		s = *sum ;
		//s = sum;
		
	}
	
	//printf("\n Process %d sending %d", rank, s);

	int *tsum= (int *)malloc(sizeof(int) * size);
	//int tsum[3];	
	MPI_Gather(sum,1,MPI_INT,tsum,1/*size*/,MPI_INT,0,MPI_COMM_WORLD);
	if(rank ==0)
	{
		printf("The Final ans %d %d %d , ",tsum[0],tsum[1],tsum[1]);
		printf("\n\n");
		//printArray(tsum,size);
	}
	
	MPI_Finalize();
}
