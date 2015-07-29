// ping_pong.cpp

#define PING_PONG_LIMIT 5

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

	int token;
	if (world_rank != 0) {
		MPI_Recv(&token, 1, MPI_INT, world_rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << world_rank << " receives token " << token << " from process "
		<< world_rank - 1 << endl; 
	} else {
		token = -1;
	}
	MPI_Send(&token, 1, MPI_INT, (world_rank+1) % world_size, 0, MPI_COMM_WORLD);
	if (world_rank == 0) {
		MPI_Recv(&token, 1, MPI_INT, world_size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << "Process " << world_rank << " receives token " << token << " from process"
		<< world_size - 1 << endl;
	}

	return 0;
}