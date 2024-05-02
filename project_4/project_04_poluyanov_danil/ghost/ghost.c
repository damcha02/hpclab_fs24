/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School     *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: Exchange ghost cell in 2 directions using a topology*
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/

/* Use only 16 processes for this exercise
 * Send the ghost cell in two directions: left<->right and top<->bottom
 * ranks are connected in a cyclic manner, for instance, rank 0 and 12 are connected
 *
 * process decomposition on 4*4 grid
 *
 * |-----------|
 * | 0| 1| 2| 3|
 * |-----------|
 * | 4| 5| 6| 7|
 * |-----------|
 * | 8| 9|10|11|
 * |-----------|
 * |12|13|14|15|
 * |-----------|
 *
 * Each process works on a 6*6 (SUBDOMAIN) block of data
 * the D corresponds to data, g corresponds to "ghost cells"
 * xggggggggggx
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * gDDDDDDDDDDg
 * xggggggggggx
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //imagine initializing an 'int' and setting it to true or false 
#include <mpi.h>

#define SUBDOMAIN 6
#define DOMAINSIZE (SUBDOMAIN+2)

int main(int argc, char *argv[])
{
    int rank, size, i, j, dims[2], periods[2], rank_top, rank_bottom, rank_left, rank_right;
    double data[DOMAINSIZE*DOMAINSIZE];
    MPI_Request requests[8]; // array of requests to make my life better
    int req_count = 0; //request counter;
    MPI_Status status;
    MPI_Comm comm_cart;
    MPI_Datatype data_ghost;

    // Initialize MPI
    // saw this if statement somewhere and thought maybe this is nice to have
    // not neccessary though
    // if (MPI_Init(&argc, &argv) == MPI_SUCCESS)
    //     printf("The MPI routine MPI_Init succeeded.\n");
    
    // else    
    //     printf("The MPI routinge MPI_Init failed :( ... fix ur code. \n");
    MPI_Init(&argc, &argv);
    // we could do the if statement for all the other MPI functions aswell comparing them to MPI_SUCCESS

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size!=16) {
        printf("please run this with 16 processors\n");
        MPI_Finalize();
        exit(1);
    }

    // initialize the domain
    for (i=0; i<DOMAINSIZE*DOMAINSIZE; i++) {
        data[i]=rank;
    }

    // TODO: set the dimensions of the processor grid and periodic boundaries in both dimensions
    dims[0]=4; // y dim
    dims[1]=4; // x dim
    periods[0]=true;
    periods[1]=true;

    // TODO: Create a Cartesian communicator (4*4) with periodic boundaries (we do not allow
    // the reordering of ranks) and use it to find your neighboring
    // ranks in all dimensions in a cyclic manner.

    // Let MPI assign arbitrary ranks if it deems it necessary
    int reorder = false; // what in the black magic is going on

    // create a cartesian 2d communicator 
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods,reorder,&comm_cart);

    // there are differen MPI functions for MPI_Cart (cartesian)
    // MPI_Cart_coords -> gets the coordinate of a process in a communicator that has a cartesian topology

    // MPI_Cart_get retrieves the information about the cartesian topology of a communicator.

    // MPI_Cart_shift 

    // MPI_Cart_sub allows to partition a cartesian topology created with MPI_Cart_create. 
    // It works by selecting dimensions along which the subgrids created will be arranged. 
    // For each subgrid, it creates a group and a communicator.
    // ------------------------------------------------------------------
    // TODO: find your top/bottom/left/right neighbor using the new communicator, see MPI_Cart_shift()
    // rank_top, rank_bottom
    // rank_left, rank_right
    // ---------------------------------------------------------------
    // we will now find the neighbours
    // lets get ready to use MPI_Cart_shift
    // int direction -> index of the dimension, so either x -> 0 or y -> 1
    // left and right should be x and up and down should be y
    // lets do displacement equal to 1, as 1 step
    int displacement = 1;
    // source
    // destination 
    
    MPI_Cart_shift(comm_cart, 0, displacement, &rank_bottom, &rank_top);
    MPI_Cart_shift(comm_cart, 1, displacement, &rank_left, &rank_right);
    



    //  TODO: create derived datatype data_ghost, create a datatype for sending the column, see MPI_Type_vector() and MPI_Type_commit()
    // data_ghost
    // MPI_Type_vector creates an MPI datatype by replicating an existing MPI_Datatype a certain number 
    // of times into a block. The MPI_Datatype created will contain a certain number of such blocks separated
    // with the constant displacement specified. Other ways to create a datatype are MPI_Type_contiguous, 
    // MPI_Type_create_hvector, MPI_Type_indexed, MPI_Type_create_hindexed, MPI_Type_create_indexed_block, 
    // MPI_Type_create_hindexed_block, MPI_Type_create_struct, MPI_Type_create_subarray, MPI_Type_create_darray.

    // columns
    MPI_Type_vector(SUBDOMAIN, 1, DOMAINSIZE, MPI_DOUBLE, &data_ghost);
    MPI_Type_commit(&data_ghost);

    // rows
    MPI_Datatype data_rows;
    MPI_Type_contiguous(SUBDOMAIN, MPI_DOUBLE, &data_rows);
    MPI_Type_commit(&data_rows);
    //  TODO: ghost cell exchange with the neighbouring cells in all directions
    //  use MPI_Irecv(), MPI_Send(), MPI_Wait() or other viable alternatives
    
    int received; // received data
    //  send data to left and to right first
    // MPI_Send(&data[DOMAINSIZE], 1, data_ghost, rank_right, 0, MPI_COMM_WORLD);
    MPI_Isend(&data[DOMAINSIZE], 1, data_ghost, rank_right, 0, MPI_COMM_WORLD, &requests[req_count++]);
    MPI_Isend(&data[2 * DOMAINSIZE - 1], 1, data_ghost, rank_left, 0, MPI_COMM_WORLD, &requests[req_count++]);
    // receive data after
    MPI_Irecv(&data[DOMAINSIZE], 1, data_ghost, rank_left, 0, MPI_COMM_WORLD, &requests[req_count++]);
    MPI_Irecv(&data[2 * DOMAINSIZE - 1], 1, data_ghost, rank_right,  0, MPI_COMM_WORLD, &requests[req_count++]);
    // MPI_Isend(&data[1 + SUBDOMAIN], 1, data_ghost, rank_left, 0, MPI_COMM_WORLD, &requests[req_count++]);

    
    //  send to the top and bottom first
    // MPI_Irecv(&data[1], 1, data_rows, rank_bottom, 0, MPI_COMM_WORLD, &requests[req_count++]);
    MPI_Isend(&data[1 + DOMAINSIZE * (DOMAINSIZE - 1)], 1, data_rows, rank_top, 0, MPI_COMM_WORLD, &requests[req_count++]);
    MPI_Isend(&data[1], 1, data_rows, rank_bottom, 0, MPI_COMM_WORLD, &requests[req_count++]);
    // receive from bottm and top
    MPI_Irecv(&data[1], 1, data_rows, rank_bottom, 0, MPI_COMM_WORLD, &requests[req_count++]);
    MPI_Irecv(&data[1 + DOMAINSIZE * (DOMAINSIZE - 1)], 1, data_rows, rank_top, 0, MPI_COMM_WORLD, &requests[req_count++]);

    MPI_Waitall(req_count, requests, MPI_STATUSES_IGNORE);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==3) {
        printf("data of rank 3 after communication\n");
        for (j=0; j<DOMAINSIZE; j++) {
            for (i=0; i<DOMAINSIZE; i++) {
                printf("%.1f ", data[i+j*DOMAINSIZE]);
                // printf("%4.1f ", data[i+j*DOMAINSIZE]);
            }
            printf("\n");
        }
    }

    // Free MPI resources (e.g., types and communicators)
    // TODO
    MPI_Comm_free(&comm_cart);
    MPI_Type_free(&data_ghost);
    MPI_Type_free(&data_rows);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
