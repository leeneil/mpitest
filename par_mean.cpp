// ping_pong.cpp

#define N 10001

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
using namespace std;


int main(int argc, char const *argv[])
{	

	


	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int t1 = (double)MPI_Wtime();
	int i, j;
	long int M = N * N;

	
	int rounds = ceil((N*1.0)/world_size);
	int N2 = rounds * world_size;
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
		// for (i = 0; i < N; i++) {
		// 	for (j = 0; j < N; j++)
		// 		cout << data[i+j*N] << "\t";
		// 	cout << endl;
		// }
		for (i = 0; i < M2; i++) {
			if (i < M)
				data_tmp[i] = data[i];
			else
				data_tmp[i] = 0;
		}
	} 

	int sub_size = rounds;
	double *mat_sub = new double[N*sub_size];

	MPI_Scatter(data_tmp, N*sub_size, MPI_DOUBLE, 
		mat_sub, N*sub_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	double sum = 0;
	for (i = 0; i < N*sub_size; i++)
		sum += mat_sub[i];
	// sum /= (N*sub_size);

	// cout << "Node " << world_rank << " says: " << sum << endl;

	double *sums = NULL;
	if (world_rank == 0) 
		sums = new double[N2];

	MPI_Gather(&sum, 1, MPI_DOUBLE, 
		sums, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	int t2 = (double)MPI_Wtime();
	if (world_rank == 0)
	{
		double mean = 0;
		for (int i = 0; i < N; i++)
			mean += sums[i];
		mean /= M;
		cout << "Over all mean: " << mean << endl;
		cout << "Time elasped: " << t2 - t1 << endl;
	}
	


	MPI_Finalize();

	return 0;
}

