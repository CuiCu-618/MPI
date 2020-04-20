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
 *    + sub;
 *  - 2nd;
 *  - 3rd;
 */





#include <iostream>
#include "mpi.h"

using namespace std;

/**
 * @brief build mpi datatype with 3 element
 *
 * @param a_p input data. double
 * @param b_p input data. double
 * @param n_p input data. int
 * @param[in, out] input_mpi_type my new mpi Datatype
 */
void Build_mpi_type(double a_p, double b_p, int n_p, MPI_Datatype * input_mpi_type)
{
    int array_of_blocklengths[3] = {1, 1, 1};
    MPI_Datatype array_of_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
    MPI_Aint a_addr, b_addr, n_addr;
    MPI_Aint array_of_displacemetns[3] = {0};

    MPI_Get_address(&a_p, &a_addr);
    MPI_Get_address(&b_p, &b_addr);
    MPI_Get_address(&n_p, &n_addr);

    array_of_displacemetns[1] = b_addr - a_addr;
    array_of_displacemetns[2] = n_addr - b_addr;

    MPI_Type_create_struct(3, array_of_blocklengths, array_of_displacemetns,
                            array_of_types, input_mpi_type);
    MPI_Type_commit(input_mpi_type);
}
/**
 * @brief my new datatype
 */
class New_data{
public:
    New_data(){}
    double a, b;
    int n;
};


int main()
{
    int my_rank, comm_sz;
    int buffer[10];
    MPI_Status status;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    New_data new_data;
    MPI_Datatype  input_mpi_type;
    double a, b;
    int n;
    Build_mpi_type(a, b, n, &input_mpi_type);
    if (my_rank == 0){
        new_data.a = 1.1;
        new_data.b = 2.2;
        new_data.n = 3;
    }
    MPI_Bcast(&new_data, 3, input_mpi_type, 0, MPI_COMM_WORLD);

    if (my_rank != 0){
        cout << "Output from: " << my_rank << endl;
            cout << new_data.a << " " << new_data.b << " " << new_data.n << endl;
    }
    MPI_Type_free(&input_mpi_type);

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
