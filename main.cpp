/**
 * @file main.cpp
 * @author Cui Cu
 *
 * @brief Learn MPI, also test doxygen
 *
 * test \f$ \LaTeX \f$ : \n
 * \f$ \alpha + \beta \f$ \n
 *
 *  test list :
 *  - 1st;
 *  - 2nd;
 *  - 3rd;
 */





#include <iostream>
#include "mpi.h"

using namespace std;

int main()
{
    int my_rank, comm_sz;
    int buffer[10];
    MPI_Status status;

    MPI_Init(nullptr, nullptr);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        for (int i = 0; i < 10; i++) {
            buffer[i] = i;
        }
        cout << "proc " << my_rank << " sending..." << endl;
        MPI_Ssend(buffer, 10, MPI_INT, 1, 123, MPI_COMM_WORLD);
    }

    if (my_rank == 1){
        for (int i = 0; i < 10; i++) {
            buffer[i] = -1;
        }
        cout << "proc " << my_rank << " receiving..." << endl;
        MPI_Recv(buffer, 10, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
        for (int i = 0; i < 10; i++){
            if (buffer[i] != i)
                cout << "Error: " << buffer[i] << "=" << i << endl;
        }
    }

    MPI_Finalize();
    return 0;
}
