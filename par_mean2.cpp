// ping_pong.cpp

#define N 7

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
using namespace std;

	int jobs(int, int, int);

int main(int argc, char *argv[])
{	

	


	MPI_Init(&argc, &argv);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int t1 = (double)MPI_Wtime();
	int i, j, t;
	long int M = N * N;

	int todo = jobs(N, world_rank, world_size);	
	int N2 = todo * world_size;
	long int M2 = N * N2;

	// cout << rounds << " rounds" << endl;

	double *data = NULL;
	double *data_tmp = NULL;
	if (world_rank == 0) {
		data = new double[M];
		data_tmp = new double[M2];
		for (i = 0; i < N; i++)
			for (j = 0; j < N; j++)
				data[i+N*j] = i + 10*j;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++)
				cout << data[i+j*N] << "\t";
			cout << endl;
		}
	} 

	double *mat_sub = new double[N*todo];

	int *disp = new int[world_size];
	int *count = new int[world_size];

	for (t = 0; t < world_size; t++) {
		if (t == 0)
			disp[t] = 0;
		else 
			disp[t] = disp[t-1] + count[t-1];
		count[t] = jobs(N, t, world_size) * N;
		if (world_rank == 1)
			cout << "Node " << t << ": disp " << disp[t] << ", count " << count[t] << endl;
	}

	MPI_Scatterv(data, count, disp, MPI_DOUBLE, 
		mat_sub, count[world_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	double sum = 0;
	for (i = 0; i < count[world_rank]; i++)
		sum += mat_sub[i];
	// sum /= (N*sub_size);

	cout << "Node " << world_rank << " says: " 
		<< todo << " jobs to do..." << endl;

	cout << "Node " << world_rank << " says: sum=" 
		<< sum << endl;

	double *sums = NULL;
	if (world_rank == 0) 
		sums = new double[N2];

	MPI_Gather(&sum, 1, MPI_DOUBLE, 
		sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	int t2 = (double)MPI_Wtime();
	if (world_rank == 0)
	{
		double mean = 0;
		for (t = 0; i < world_size; i++)
			mean += sums[i];
		cout << endl;
		mean /= M;
		cout << "Over all mean: " << mean << endl;
		cout << "Time elasped: " << t2 - t1 << endl;
	}
	


	MPI_Finalize();

	return 0;
}

int jobs(int NN, int myrank, int worldsize) {
	int num = floor((NN*1.0)/worldsize);
	int remaining = NN - num * worldsize;
	if (myrank >= worldsize - remaining)
		num++;
	return num;
}
