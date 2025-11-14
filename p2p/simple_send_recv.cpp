#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // 初始化 MPI 环境, 两个参数实际上要使用argc和argv，这里不传
    MPI_Init(NULL, NULL);

    // 获取可以工作的进程数量world_size
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 得到当前进程的秩 world_rank
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int number;
    int tag = 0;
    if (world_rank == 0) {
        number = 666;
        MPI_Send(&number, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
        printf("Processor 0 send data %d to processor 1 of tag %d\n", number, tag);
    } else if (world_rank == 1) {
        MPI_Recv(&number, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processor 1 received data %d from processor 0 of tag %d\n", number, tag);
    }

    // 释放MPI的资源
    MPI_Finalize();

    return 0;
}