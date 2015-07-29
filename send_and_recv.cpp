#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char const *argv[])
{
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int number;
	if (world_rank == 0) {
		number = -1;
		MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << world_rank << " gets the number " << number << endl;
	}

	return 0;
}