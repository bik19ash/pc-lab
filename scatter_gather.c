#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data[4], recv;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize data in root process
    if (rank == 0) {
        for (int i = 0; i < 4; i++) {
            data[i] = i + 1;
        }
    }

    // Scatter data to all processes
    MPI_Scatter(data, 1, MPI_INT,
                &recv, 1, MPI_INT,
                0, MPI_COMM_WORLD);

    printf("Process %d received %d\n", rank, recv);

    // Process the received data
    recv = recv * 2;

    // Gather results back to root
    MPI_Gather(&recv, 1, MPI_INT,
               data, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    // Display gathered values
    if (rank == 0) {
        printf("Gathered values: ");

        for (int i = 0; i < 4; i++) {
            printf("%d ", data[i]);
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}