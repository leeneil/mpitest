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

	cout << "Hello world!" << endl;
	cout << "-- greeting from the node " << world_rank << endl;
	return 0;
}