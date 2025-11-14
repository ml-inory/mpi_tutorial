/*

MPI乒乓程序

进程0和1以某个数字开始互相发送接收，每次接收数字减1，直到数字小于0

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

    int inital_number = 10;

    // 来回收发
    int number;
    if (world_rank == 0) {
        // 发送第一个数字
        MPI_Send(&inital_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        while (1) {
            MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            if (number > 0) {
                printf("Processor 0 receive number: %d\n", number);
                number--;
                MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("Processor 0 send number: %d\n", number);
            }  
            else {
                MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf("Processor 0 end\n");
                break;
            }
        }
        
    } else if (world_rank == 1) {
        while (1) {
            MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            if (number > 0) {
                printf("Processor 1 receive number: %d\n", number);
                number--;
                MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                printf("Processor 1 send number: %d\n", number);
            }
            else {
                MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                printf("Processor 1 end\n");
                break;
            }
        }
    }
    
    // 释放MPI的资源
    MPI_Finalize();

    return 0;
}