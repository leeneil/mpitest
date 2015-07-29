// ping_pong.cpp

#define N 7

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
using namespace std;


int main(int argc, char const *argv[])
{	
	if (argc > 1)
		cout << argv[1] << endl;
	srand(time(NULL));
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int i, j;
	int M = N * N;

	int round = ceil((N*1.0)/world_size);
	int N2 = round * world_size;
	int M2 = N * N2;

	double *mat0 = NULL, *mat_tmp = NULL;
	if (world_rank == 0) {
		mat0 = new double[M];
		mat_tmp = new double[M2];
	} 

	int sub_size = (int)(N2 / world_size);
	double *mat_sub = new double[N];

	for (int t = 0; t < round; t++) {
		for (i = 0; i < N; i++)
			mat_sub[i] = rand() % 100;
		MPI_Gather(mat_sub, N, MPI_DOUBLE, 
			&(mat_tmp[t*sub_size*N]), N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}

	if (world_rank == 0)
	{
		for (i = 0; i < M; i++)
			mat0[i] = mat_tmp[i];
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++)
				cout << mat0[i+j*N] << "\t";
			cout << endl;
		}
	}

	MPI_Finalize();

	return 0;
}

