// ping_pong.cpp

#define N 13

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <mpi.h>
using namespace std;

int toDo (int, int, int);

int main(int argc, char const *argv[])
{

	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int round = toDo(N, world_size, world_rank);
	cout << "Node " << world_rank << " says: I need to run " << round << " rounds..." << endl;

	return 0;
}

int toDo(int n, int world_size, int world_rank) {
	int round = floor((float)N / world_size);
	int remaining = n - round * world_size;
	if (world_rank >= world_size - remaining)
		round++;
	return round;
}