#include <mpi.h> // MPI
#include <stdio.h>

int main(int argc, char *argv[]) {

  // Initialize MPI, get size and rank
  int size, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // IMPLEMENT: Ring sum algorithm
  int sum = 0; // initialize sum
  int token;   // Token to Send/Receive  

  // calculate the previous and the next
  int prev = (rank - 1 + size) % size;
  int next = (rank + 1) % size;

  // print initial status
  // printf("Process %i: Sum = %i\n", rank, sum);
  token = rank;
  for(int i = 0; i < size; i++){
    
    // we send the token/rank to the next node
    MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    // we receive the token that was sent to us by the previous node
    MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // update sum by the token that we received
    sum += token;
    // print final rank, and sum
    printf("Process %i: received token %i in round %i, current Sum = %i\n", rank, token, i,sum);

  }
  fflush(stdout);
  // wait for all processes to finish
  MPI_Barrier(MPI_COMM_WORLD);

  printf("Final sum at process %i is %i\n", rank, sum);
  // printf("THIS IS JUST TO TEST, we will be printing size: %i\n", size);
  fflush(stdout);

  // Finalize MPI
  MPI_Finalize();

  return 0;
}

// there is a better solution which will work better for larger size rings, but for now we stick with this one
// could probably do it with Isend and Irecv  