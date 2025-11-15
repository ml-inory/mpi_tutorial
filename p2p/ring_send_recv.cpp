/*

多个进程间构成环形发送数据，从进程0开始回到进程0

由于Recv是阻塞的，每次Send都只发给了邻居进程，保证了发送顺序和打印顺序是保序的

*/
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
        
    if (world_rank != 0) {
        MPI_Recv(&number, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processor %d received %d from processor %d\n", world_rank, number, world_rank - 1);
    } else {
        number = 666;
    }

    MPI_Send(&number, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        MPI_Recv(&number, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Processor 0 received %d from processor %d\n", number, world_size - 1);
    }

    // 释放MPI的资源
    MPI_Finalize();

    return 0;
}