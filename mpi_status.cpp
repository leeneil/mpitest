// ping_pong.cpp

#define MAX_NUMBERS 1000

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <mpi.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int numbers[MAX_NUMBERS] = {0};
	int number_amount;
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	if (world_rank  == 0)
	{
		srand(time(NULL));
		number_amount = (rand() / (float)RAND_MAX) * (float)MAX_NUMBERS * 1.0;
		MPI_Send(&numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
		cout << "Node 0 sends " << number_amount << " numbers to node 1" << endl;
	} else {
		MPI_Status status;

		MPI_Recv(&numbers, MAX_NUMBERS, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &number_amount);

		cout << "Node 1 receives " << number_amount << " numbers from node 0." << endl;
		cout << "Message source = " << status.MPI_SOURCE << ", tag = "
		<< status.MPI_TAG << endl;
	}

	return 0;
}