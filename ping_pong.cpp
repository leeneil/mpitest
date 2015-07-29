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

	int ping_pong_count = 0;
	int partner_rank = (world_rank + 1) % 2;

	while (ping_pong_count < PING_PONG_LIMIT) {
		if (world_rank == ping_pong_count % 2) {
			ping_pong_count++;
			MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
			cout << "Process " << world_rank << " sends and increases ping pong count "
			<<  ping_pong_count << " to process " << partner_rank << endl; 
		} else {
			MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, 
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			cout << "Process " << world_rank << "receives ping pong count " << ping_pong_count
			<< " from process " << partner_rank << endl;
		}
		MPI_Barrier(MPI_COMM_WORLD);

	}

	

	return 0;
}