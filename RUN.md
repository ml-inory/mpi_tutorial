# 程序运行方式

先保证能运行mpirun，如果是自行编译的mpi，请把mpirun可执行放在环境变量

hello_wolrd:  
```mpirun -n 4 ./install/hello_world```

simple_send_recv:  
```mpirun -n 2 ./install/simple_send_recv```