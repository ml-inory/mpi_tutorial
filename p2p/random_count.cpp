/*

通过MPI_Status和MPI_Get_count可以接收任意数量的数据

MPI_Get_count(
    MPI_Status* status,
    MPI_Datatype datatype,
    int* count)

MPI_Recv的count参数可以大于MPI_Send的，实际数量通过MPI_Get_count的count指针获取

*/
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    // 初始化 MPI 环境, 两个参数实际上要使用argc和argv，这里不传
    MPI_Init(NULL, NULL);

    // 获取可以工作的进程数量world_size
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // 得到当前进程的秩 world_rank
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int MAX_NUM = 100;
    int numbers[MAX_NUM];
    int send_count;

    if (world_rank == 0) {
        srand((unsigned int)time(NULL));

        send_count = rand() % MAX_NUM + 1;
        MPI_Send(numbers, send_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        int receive_nums[MAX_NUM];
        int receive_count;
        MPI_Status status;

        MPI_Recv(receive_nums, MAX_NUM, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &receive_count);

        printf("Processor 1 receive %d integer from processor %d of tag %d\n", receive_count, status.MPI_SOURCE, status.MPI_TAG);
    }

    // 释放MPI的资源
    MPI_Finalize();

    return 0;
}